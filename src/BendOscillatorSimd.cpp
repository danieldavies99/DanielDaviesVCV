#include "plugin.hpp"

using namespace rack;

void BendOscillatorSimd::process(float deltaTime) {
    simd::float_4 deltaPhase = simd::clamp(freq * deltaTime, 0.f, 0.35f);
    phase += deltaPhase;

    // wrap phase
    phase -= simd::floor(phase);

    float bendAmount = bendParam / 2;

    // phase modulation (bend)
    // given input 0 -> 1
    // will output a skewed 0 -> 1
    simd::float_4 bentPhase = phase;
    const float constant025 = 0.25f;
    const float constant05 = 0.5f;
    const float constant075 = 0.75f;
    const float constant1 = 1.f;
    for(int i = 0; i < 4; i++) {   
        float currentPhase = phase[i];
        
        if(currentPhase <= constant05) {
            if(currentPhase <= bendAmount) {
                float percentageToBend = currentPhase / bendAmount;
                bentPhase[i] = constant025 * percentageToBend;
            } else { 
                float percentageToHalfWayFromBend = (currentPhase - bendAmount) / (constant05 - bendAmount);
                bentPhase[i] = constant025+(constant025*percentageToHalfWayFromBend);
            }
        }  else {
            if(currentPhase >= constant1 - bendAmount) {
                float percentageToEnd = (currentPhase - (1-bendAmount)) / bendAmount;
                bentPhase[i] = constant075 + constant025 * percentageToEnd;
            } else {
                float percentageToPeak = (currentPhase - constant05) / (constant1 - bendAmount - constant05);
                bentPhase[i] = constant05+(constant025*percentageToPeak);
            }
        }
    }

    bentPhase = simd::clamp(bentPhase, 0.f, 1.f);
    simd::float_4 bentFrames = simd::floor(bentPhase*2048);

    // sin out
    sinOut[0] = sinTable[(int)bentFrames[0]];
    sinOut[1] = sinTable[(int)bentFrames[1]];
    sinOut[2] = sinTable[(int)bentFrames[2]];
    sinOut[3] = sinTable[(int)bentFrames[3]];

    // tri out
    triOut[0] = triTable[(int)bentFrames[0]];
    triOut[1] = triTable[(int)bentFrames[1]];
    triOut[2] = triTable[(int)bentFrames[2]];
    triOut[3] = triTable[(int)bentFrames[3]];

    // square out
    simd::float_4 frames = simd::floor(phase*2048);
    squareOut[0] = squareTable[(int)frames[0]];
    squareOut[1] = squareTable[(int)frames[1]];
    squareOut[2] = squareTable[(int)frames[2]];
    squareOut[3] = squareTable[(int)frames[3]];

    // noise out
    noiseOut[0] = generateNoise();
    noiseOut[1] = generateNoise();
    noiseOut[2] = generateNoise();
    noiseOut[3] = generateNoise();
}

float BendOscillatorSimd::generateNoise() {
    float random = random::uniform();
    return random*2.f - 1.f;
}

void BendOscillatorSimd::generateSinTable() {
    const int resolution = 2048;
    // M_PI
    float stepSize = (2*M_PI) / resolution;
    for (int i = 0; i < resolution; i++) {
        sinTable[i] = std::sin(i*stepSize);
    }
}

void BendOscillatorSimd::generateTriTable() {
    const int resolution = 2048;
    const float phaseShift = 0.25;

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