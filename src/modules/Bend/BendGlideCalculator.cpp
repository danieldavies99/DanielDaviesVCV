#include "BendGlideCalculator.hpp"

using namespace rack;

void GlideCalculator::initialize(simd::float_4 initialFreq)
{
    currentFreq = initialFreq;
    initialized = true;
}

void GlideCalculator::process(float deltaTime)
{
    if (glideAmount < 0.02)
    {
        currentFreq = targetFreq;
    }
    float inverseControl = 1.1f - glideAmount;
    simd::float_4 targetIsBelow = (targetFreq < currentFreq);
    simd::float_4 amount = ((currentFreq * inverseControl * 25.f) * deltaTime);
    currentFreq = simd::ifelse(targetIsBelow, currentFreq - amount, currentFreq + amount);
}
