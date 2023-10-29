#include "plugin.hpp"

using namespace rack;

simd::float_4 BendWavetable::getFrame(
    simd::float_4 phase,
    InterpolationMode interpolationMode
) {

    simd::float_4 frames = simd::floor(phase * resolution);

    if (interpolationMode == BendWavetable::InterpolationMode::LINEAR)
    {
        // linear interpolation:
        simd::float_4 bottomFrameNums = simd::floor(frames);
        simd::float_4 topFrameNums = simd::ceil(frames);
        simd::float_4 bottomFrames = {
            table[(int)bottomFrameNums[0]],
            table[(int)bottomFrameNums[1]],
            table[(int)bottomFrameNums[2]],
            table[(int)bottomFrameNums[3]],
        };

        simd::float_4 topFrames = {
            table[(int)topFrameNums[0]],
            table[(int)topFrameNums[1]],
            table[(int)topFrameNums[2]],
            table[(int)topFrameNums[3]],
        };

        simd::float_4 interpolationValues = frames - bottomFrameNums; // i.e. 0.3, 0.6, etc
        simd::float_4 difference = simd::abs(topFrames - bottomFrames);
        simd::float_4 res = bottomFrames + (difference * interpolationValues);
        return res;
    }
    if (
        interpolationMode == BendWavetable::InterpolationMode::NONE
    ) {
        simd::float_4 truncatedFrames = simd::floor(frames);
        simd::float_4 res = {
            table[(int)truncatedFrames[0]],
            table[(int)truncatedFrames[1]],
            table[(int)truncatedFrames[2]],
            table[(int)truncatedFrames[3]],
        };
        return res;

    }
    simd::float_4 res = {0.f,0.f,0.f,0.f};
    return res;
}

void BendTriTable::generate()
{
    for (int i = 0; i < resolution; i++)
    {
        float normalizedIndex = static_cast<float>(i) / (resolution - 1);
        normalizedIndex = std::fmod(normalizedIndex + phaseShift, 1.0); // Apply phase shift
        float triangleValue = 2.0 * (0.5 - std::abs(normalizedIndex - 0.5));

        table[i] = 2 * (triangleValue - 0.5); // Scale to -1 to 1 range and start at 0
    }
}

void BendSinTable::generate()
{
    float stepSize = (2 * M_PI) / resolution;
    for (int i = 0; i < resolution; i++)
    {
        table[i] = std::sin(i * stepSize + (2 * M_PI * phaseShift));
    }
}

void BendAnalogSquareTable::generate()
{
    // "analog" square
    // Pre-calculate the envelope values with reversed effect on the troughs
    float envelope[resolution];
    for (int i = 0; i < resolution; i++)
    {
        float normalizedIndex = static_cast<float>(i) / (resolution - 1);
        float envelopeValue = (std::sin(2.0 * M_PI * normalizedIndex) < 0.0) ? std::pow(envelopeFactor, std::cos(2.0 * M_PI * normalizedIndex))
                                                                             : std::pow(envelopeFactor, -std::cos(2.0 * M_PI * normalizedIndex));
        envelope[i] = envelopeValue;
    }

    // Generate the square wave using the mixed envelope values
    for (int i = 0; i < resolution; i++)
    {
        float normalizedIndex = static_cast<float>(i) / (resolution - 1);
        float phaseAdjustedIndex = normalizedIndex + phaseShift;
        int indexInEnvelope = static_cast<int>(normalizedIndex * (resolution - 1));

        float envelopeValue = envelope[indexInEnvelope];
        float squareValue = (std::sin(2.0 * M_PI * phaseAdjustedIndex) >= 0.0) ? 1.0 : -1.0;

        table[i] = envelopeValue * squareValue * envelopeFactor;
    }
}

void BendPerfectSquareTable::generate()
{
    for (int i = 0; i < resolution; i++)
    {
        float normalizedIndex = static_cast<float>(i) / (resolution - 1);
        float phaseAdjustedIndex = normalizedIndex + phaseShift;
        float squareValue = (std::sin(2.0 * M_PI * phaseAdjustedIndex) >= 0.0) ? 1.0 : -1.0;

        table[i] = squareValue;
    }
}