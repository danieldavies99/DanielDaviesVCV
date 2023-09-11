#include "plugin.hpp"

using namespace rack;

void BendOscillatorSimd::process(float deltaTime) {
    simd::float_4 deltaPhase = simd::clamp(freq * deltaTime, 0.f, 0.35f);
    phase += deltaPhase;


    // sync
    if(syncEnabled) {
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
    for(int i = 0; i < 4; i++) {   
        float currentPhase = phase[i];
        float bendAmount = bend[i];
        if(currentPhase < bendAmount) {
            float percentageThrough = currentPhase / bendAmount;
            bentPhase[i] = percentageThrough * 0.5;
        } else {
            float percentageThrough = (currentPhase - bendAmount) / (1 - bendAmount);
            bentPhase[i] = 0.5 + (percentageThrough * 0.5);
        }
    }
    bentPhase = simd::clamp(bentPhase, 0.f, 1.f); // defensive programming or something
    simd::float_4 bentFrames = simd::floor(bentPhase*2048);

    // sin out
    for(int i = 0; i < channels; i++) {
        sinOut[i] = sinTable[(int)bentFrames[i]];
    }
    if(unipolar) {
        sinOut = (sinOut + 1) * amplitude;
    } else {
        sinOut = sinOut * amplitude;
    }

    // tri out
    for(int i = 0; i < channels; i++) {
        triOut[i] = triTable[(int)bentFrames[i]];
    }
    if(unipolar) {
        triOut = (triOut + 1) * amplitude;
    } else {
        triOut = triOut * amplitude;
    }

    // square out
    for(int i = 0; i < channels; i++) {
        squareOut[i] = squareTable[(int)bentFrames[i]];
    }
        if(unipolar) {
        squareOut = (squareOut + 1) * amplitude;
    } else {
        squareOut = squareOut * amplitude;
    }

    // noise out
    for(int i = 0; i < channels; i++) {
        noiseOut[i] = generateNoise();
    }
    noiseOut = noiseOut * amplitude;
}

float BendOscillatorSimd::generateNoise() {
    float random = random::uniform();
    return random*2.f - 1.f;
}

void BendOscillatorSimd::generateSinTable() {
    const int resolution = 2048;
    const float phaseShift = -0.25;

    // M_PI
    float stepSize = (2*M_PI) / resolution;
    for (int i = 0; i < resolution; i++) {
        sinTable[i] = std::sin(i*stepSize + (2*M_PI*phaseShift));
    }
}

void BendOscillatorSimd::generateTriTable() {
    const int resolution = 2048;
    const float phaseShift = 0.0;

    for (int i = 0; i < resolution; i++) {
        float normalizedIndex = static_cast<float>(i) / (resolution - 1);
        normalizedIndex = std::fmod(normalizedIndex + phaseShift, 1.0); // Apply phase shift
        float triangleValue = 2.0 * (0.5 - std::abs(normalizedIndex - 0.5));

        triTable[i] = 2 * (triangleValue - 0.5); // Scale to -1 to 1 range and start at 0
    }
}

void BendOscillatorSimd::generateSquareTable() {
    const int resolution = 2048;
    const float phaseShift = 0.0;
    const float envelopeFactor = 0.75;

    // perfect square
    // for (int i = 0; i < resolution; i++) {
    //     float normalizedIndex = static_cast<float>(i) / (resolution - 1);
    //     float phaseAdjustedIndex = normalizedIndex + phaseShift;
    //     float squareValue = (std::sin(2.0 * M_PI * phaseAdjustedIndex) >= 0.0) ? 1.0 : -1.0;

    //     squareTable[i] = squareValue;
    // }

    // "analog" square
    // Pre-calculate the envelope values with reversed effect on the troughs
    float envelope[resolution];
    for (int i = 0; i < resolution; i++) {
        float normalizedIndex = static_cast<float>(i) / (resolution - 1);
        float envelopeValue = (std::sin(2.0 * M_PI * normalizedIndex) < 0.0) ?
            std::pow(envelopeFactor, std::cos(2.0 * M_PI * normalizedIndex))
            : std::pow(envelopeFactor, -std::cos(2.0 * M_PI * normalizedIndex));
        envelope[i] = envelopeValue;
    }

    // Generate the square wave using the mixed envelope values
    for (int i = 0; i < resolution; i++) {
        float normalizedIndex = static_cast<float>(i) / (resolution - 1);
        float phaseAdjustedIndex = normalizedIndex + phaseShift;
        int indexInEnvelope = static_cast<int>(normalizedIndex * (resolution - 1));

        float envelopeValue = envelope[indexInEnvelope];
        float squareValue = (std::sin(2.0 * M_PI * phaseAdjustedIndex) >= 0.0) ? 1.0 : -1.0;

        squareTable[i] = envelopeValue * squareValue * envelopeFactor;
    }
}