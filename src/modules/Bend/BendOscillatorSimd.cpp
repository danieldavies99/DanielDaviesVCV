#include "BendOscillatorSimd.hpp"

using namespace rack;

void BendOscillatorSimd::setSampleTime(float sampleTime)
{
    // One-pole highpass coefficient approximation (same formula as Fundamental/VCO)
    float w = float(2 * M_PI) * std::min(0.4f, 20.f * sampleTime);
    dcAlpha = w / (1.f + w);
}

void BendOscillatorSimd::process(float deltaTime)
{
    simd::float_4 deltaPhase = simd::clamp(freq * deltaTime, 0.f, 0.35f);

    simd::float_4 prevPhase = phase;
    phase += deltaPhase;

    // sync: hard reset to phase 0 on rising edge of sync input
    if (syncEnabled)
    {
        simd::float_4 crossingZero = (sync > 0.f) & (lastSync < 0.f);
        phase = simd::ifelse(crossingZero, 0.f, phase);
        lastSync = sync;
    }

    simd::float_4 endPhase = phase;

    // --- minBLEP / minBLAMP insertion ---
    // Detect per-channel crossings before wrapping and insert correction kernels.
    //
    // Square crossings (step discontinuities):
    //   At phase wrap (0): perfectSquare -1→+1, magnitude = +2
    //   At phase = bend:   perfectSquare +1→-1, magnitude = -2
    //   Analog square magnitudes are ±(1 + ef²) where ef = envelopeFactor.
    //
    // Triangle crossings (slope discontinuities, minBLAMP):
    //   Slope per sample in [0,bend]:    +2·Δφ/b
    //   Slope per sample in [bend,1]:    -2·Δφ/(1-b)
    //   Slope jump at wrap:  +2·Δφ / (b·(1-b))
    //   Slope jump at bend:  -2·Δφ / (b·(1-b))

    const float ef = analogSquareTable.envelopeFactor;
    const float analogMag = 1.f + ef * ef;   // ≈ 1.5625 for ef=0.75

    for (int i = 0; i < channels; i++)
    {
        float prev = prevPhase[i];
        float end  = endPhase[i];
        float dp   = deltaPhase[i];
        float b    = bend[i];

        if (dp <= 0.f)
            continue;

        float* sqrData = (float*)sqrMinBlep.startData();
        float* triData = (float*)triMinBlep.startData();

        // Apply minBLAMP only when b*(1-b) >= 0.05 (i.e. bend roughly in [0.055, 0.945]).
        // Below this the slope is so steep that the correction kernel overshoots and
        // pushes peaks above ±1. Let the waveform alias naturally at extreme bend instead.
        float bProduct = b * (1.f - b);
        float triSlopeMag = (bProduct >= 0.05f) ? (2.f * dp / bProduct) : 0.f;

        // Phase wrap: phase crossed 1
        if (end >= 1.f)
        {
            // Pre-wrap bend crossing: phase crossed b before crossing 1 (b-close-to-1 case).
            // Since b < 1 ≤ end, if prev < b the bend threshold was crossed before the wrap.
            if (prev < b)
            {
                float bendSub = (b - prev) / dp;
                float sqrBendMag = usePerfectSquare ? -2.f : -analogMag;
                getBendMinBlep().insertDiscontinuity(bendSub, sqrBendMag, &sqrData[i], 4);
                getBendMinBlep().insertSlopeDiscontinuity(bendSub, -triSlopeMag, &triData[i], 4);
            }

            float wrapSub = (1.f - prev) / dp;
            float sqrMag = usePerfectSquare ? 2.f : analogMag;
            getBendMinBlep().insertDiscontinuity(wrapSub, sqrMag, &sqrData[i], 4);
            getBendMinBlep().insertSlopeDiscontinuity(wrapSub, triSlopeMag, &triData[i], 4);

            // Post-wrap bend crossing: after the wrap the phase restarts from 0.
            // If it reaches b before the end of the frame, insert the bend correction too.
            // Without this check the bend crossing is silently missed on almost every wrap
            // when b is small, causing the BLAMP corrections to accumulate instead of cancel.
            float postWrapEnd = end - 1.f;
            if (b < postWrapEnd)
            {
                float bendSub = wrapSub + (b / postWrapEnd) * (1.f - wrapSub);
                float sqrBendMag = usePerfectSquare ? -2.f : -analogMag;
                getBendMinBlep().insertDiscontinuity(bendSub, sqrBendMag, &sqrData[i], 4);
                getBendMinBlep().insertSlopeDiscontinuity(bendSub, -triSlopeMag, &triData[i], 4);
            }
        }
        else if (prev < b && end >= b)
        {
            // Bend crossing with no wrap in this frame
            float bendSub = (b - prev) / dp;

            float sqrMag = usePerfectSquare ? -2.f : -analogMag;
            getBendMinBlep().insertDiscontinuity(bendSub, sqrMag, &sqrData[i], 4);
            getBendMinBlep().insertSlopeDiscontinuity(bendSub, -triSlopeMag, &triData[i], 4);
        }
    }

    // wrap phase to [0, 1)
    phase -= simd::floor(phase);

    // Apply bend: maps linear phase [0,1] to bentPhase [0,1] with the midpoint
    // at phase=bend instead of phase=0.5.
    simd::float_4 bentPhase = phase;
    for (int i = 0; i < 4; i++)
    {
        float currentPhase = phase[i];
        float bendAmount = bend[i];
        if (currentPhase < bendAmount)
        {
            float percentageThrough = currentPhase / bendAmount;
            bentPhase[i] = percentageThrough * 0.5f;
        }
        else
        {
            float percentageThrough = (currentPhase - bendAmount) / (1.f - bendAmount);
            bentPhase[i] = 0.5f + (percentageThrough * 0.5f);
        }
    }
    bentPhase = simd::clamp(bentPhase, 0.f, 1.f);

    // sin — no BLEP needed: sine has no discontinuities
    sinOut = sinTable.getValue(bentPhase, interpolationMode);
    if (unipolar)
        sinOut = (sinOut + 1.f) * amplitude;
    else
        sinOut = sinOut * amplitude;

    // tri — add minBLAMP correction, then DC block, then scale
    simd::float_4 rawTri = triTable.getValue(bentPhase, interpolationMode);
    rawTri += triMinBlep.shift();
    simd::float_4 triLP = triDCState + dcAlpha * (rawTri - triDCState);
    triDCState = triLP;
    rawTri = rawTri - triLP;
    if (unipolar)
        triOut = (rawTri + 1.f) * amplitude;
    else
        triOut = rawTri * amplitude;

    // square — add minBLEP correction, then DC block, then scale
    simd::float_4 rawSqr;
    if (!usePerfectSquare)
        rawSqr = analogSquareTable.getValue(bentPhase, interpolationMode);
    else
        rawSqr = perfectSquareTable.getValue(bentPhase, interpolationMode);
    rawSqr += sqrMinBlep.shift();
    simd::float_4 sqrLP = sqrDCState + dcAlpha * (rawSqr - sqrDCState);
    sqrDCState = sqrLP;
    rawSqr = rawSqr - sqrLP;
    if (unipolar)
        squareOut = (rawSqr + 1.f) * amplitude;
    else
        squareOut = rawSqr * amplitude;

    // noise — white noise, inherently band-limited
    for (int i = 0; i < channels; i++)
        noiseOut[i] = generateNoise();
    noiseOut = noiseOut * amplitude;
}

float BendOscillatorSimd::generateNoise()
{
    float random = random::uniform();
    return random * 2.f - 1.f;
}
