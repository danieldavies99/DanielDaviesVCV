#include "BendWavetables.hpp"

using namespace rack;

simd::float_4 BendWavetable::getValue(
    simd::float_4 phase,
    InterpolationMode interpolationMode)
{

    simd::float_4 frames = phase * resolution;

    if (interpolationMode == BendWavetable::InterpolationMode::LINEAR)
    {
        simd::float_4 bottomFrameNums = simd::floor(frames);
        simd::float_4 topFrameNums = simd::ceil(frames);
        simd::float_4 bottomFrames = {
            table[(int)bottomFrameNums[0]],
            table[(int)bottomFrameNums[1]],
            table[(int)bottomFrameNums[2]],
            table[(int)bottomFrameNums[3]],
        };

        simd::float_4 topFrames = {
            table[(int)topFrameNums[0] % resolution],
            table[(int)topFrameNums[1] % resolution],
            table[(int)topFrameNums[2] % resolution],
            table[(int)topFrameNums[3] % resolution],
        };

        simd::float_4 interpolationValues = frames - bottomFrameNums;
        simd::float_4 difference = topFrames - bottomFrames;
        simd::float_4 res = bottomFrames + (difference * interpolationValues);
        return res;
    }
    if (interpolationMode == BendWavetable::InterpolationMode::NONE)
    {
        simd::float_4 truncatedFrames = simd::floor(frames);
        simd::float_4 res = {
            table[(int)truncatedFrames[0]],
            table[(int)truncatedFrames[1]],
            table[(int)truncatedFrames[2]],
            table[(int)truncatedFrames[3]],
        };
        return res;
    }
    return {0.f, 0.f, 0.f, 0.f};
}

void BendTriTable::generate()
{
    for (int i = 0; i < resolution; i++)
    {
        // Use i/resolution (not i/(resolution-1)) so the table covers [0,1)
        // and wraps cleanly: table[0] and the virtual table[resolution] are both -1.
        float normalizedIndex = static_cast<float>(i) / resolution;
        normalizedIndex = std::fmod(normalizedIndex + phaseShift, 1.0);
        float triangleValue = 2.0 * (0.5 - std::abs(normalizedIndex - 0.5));

        table[i] = 2 * (triangleValue - 0.5);
    }
}

void BendSinTable::generate()
{
    float stepSize = (2 * M_PI) / (resolution);
    for (int i = 0; i < resolution; i++)
    {
        table[i] = std::sin(i * stepSize + (2 * M_PI * phaseShift));
    }
}

void BendAnalogSquareTable::generate()
{
    float envelope[resolution];
    for (int i = 0; i < resolution; i++)
    {
        // Use i/resolution so the last entry stays on the negative side,
        // keeping the only real discontinuity at the wrap boundary (index resolution-1 → 0).
        float normalizedIndex = static_cast<float>(i) / resolution;
        float envelopeValue = (std::sin(2.0 * M_PI * normalizedIndex) < 0.0)
            ? std::pow(envelopeFactor, std::cos(2.0 * M_PI * normalizedIndex))
            : std::pow(envelopeFactor, -std::cos(2.0 * M_PI * normalizedIndex));
        envelope[i] = envelopeValue;
    }

    for (int i = 0; i < resolution; i++)
    {
        float normalizedIndex = static_cast<float>(i) / resolution;
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
        // Use i/resolution so the last entry remains on the correct (negative) side.
        float normalizedIndex = static_cast<float>(i) / resolution;
        float phaseAdjustedIndex = normalizedIndex + phaseShift;
        float squareValue = (std::sin(2.0 * M_PI * phaseAdjustedIndex) >= 0.0) ? 1.0 : -1.0;

        table[i] = squareValue;
    }
}
