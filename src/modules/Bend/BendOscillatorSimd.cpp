#include "BendOscillatorSimd.hpp"

using namespace rack;

void BendOscillatorSimd::process(float deltaTime)
{
    simd::float_4 deltaPhase = simd::clamp(freq * deltaTime, 0.f, 0.35f);
    phase += deltaPhase;

    // sync
    if (syncEnabled)
    {
        simd::float_4 crossingZero = (sync > 0.f);
        crossingZero &= (lastSync < 0.f);
        phase = simd::ifelse(crossingZero, 0.f, phase);
        lastSync = sync;
    }

    // wrap phase
    phase -= simd::floor(phase);

    // phase modulation (bend)
    // given input 0 -> 1
    // will output a skewed 0 -> 1
    // can this be done better with simd maths? probably
    simd::float_4 bentPhase = phase;
    for (int i = 0; i < 4; i++)
    {
        float currentPhase = phase[i];
        float bendAmount = bend[i];
        if (currentPhase < bendAmount)
        {
            float percentageThrough = currentPhase / bendAmount;
            bentPhase[i] = percentageThrough * 0.5;
        }
        else
        {
            float percentageThrough = (currentPhase - bendAmount) / (1 - bendAmount);
            bentPhase[i] = 0.5 + (percentageThrough * 0.5);
        }
    }
    bentPhase = simd::clamp(bentPhase, 0.f, 1.f); // defensive programming or something

    // sin out
    sinOut = sinTable.getValue(bentPhase, interpolationMode);
    if (unipolar)
    {
        sinOut = (sinOut + 1) * amplitude;
    }
    else
    {
        sinOut = sinOut * amplitude;
    }

    triOut = triTable.getValue(bentPhase, interpolationMode);
    if (unipolar)
    {
        triOut = (triOut + 1) * amplitude;
    }
    else
    {
        triOut = triOut * amplitude;
    }

    // square out
    if (!usePerfectSquare)
    {
        squareOut = analogSquareTable.getValue(bentPhase, interpolationMode);
    }
    else
    {
        squareOut = perfectSquareTable.getValue(bentPhase, interpolationMode);
    }

    if (unipolar)
    {
        squareOut = (squareOut + 1) * amplitude;
    }
    else
    {
        squareOut = squareOut * amplitude;
    }

    // noise out
    for (int i = 0; i < channels; i++)
    {
        noiseOut[i] = generateNoise();
    }
    noiseOut = noiseOut * amplitude;
}

float BendOscillatorSimd::generateNoise()
{
    float random = random::uniform();
    return random * 2.f - 1.f;
}