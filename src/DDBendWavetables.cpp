#include "plugin.hpp"

using namespace rack;

float BendWavetable::getFrame(int frameNum) {
    if(frameNum >= 0 && frameNum <= resolution)
    {
        return table[frameNum];
    }
    return 0;
}

void BendTriTable::generate() {
    for (int i = 0; i < resolution; i++) {
        float normalizedIndex = static_cast<float>(i) / (resolution - 1);
        normalizedIndex = std::fmod(normalizedIndex + phaseShift, 1.0); // Apply phase shift
        float triangleValue = 2.0 * (0.5 - std::abs(normalizedIndex - 0.5));

        table[i] = 2 * (triangleValue - 0.5); // Scale to -1 to 1 range and start at 0
    }
}

void BendSinTable::generate() {
    float stepSize = (2*M_PI) / resolution;
    for (int i = 0; i < resolution; i++) {
        table[i] = std::sin(i*stepSize + (2*M_PI*phaseShift));
    }
}

void BendAnalogSquareTable::generate() {
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

        table[i] = envelopeValue * squareValue * envelopeFactor;
    }
}

void BendPerfectSquareTable::generate() {
    for (int i = 0; i < resolution; i++) {
        float normalizedIndex = static_cast<float>(i) / (resolution - 1);
        float phaseAdjustedIndex = normalizedIndex + phaseShift;
        float squareValue = (std::sin(2.0 * M_PI * phaseAdjustedIndex) >= 0.0) ? 1.0 : -1.0;

        table[i] = squareValue;
    }
}