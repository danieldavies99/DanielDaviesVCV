#pragma once
#include <rack.hpp>

struct GlideCalculator
{
    bool initialized = false;

    rack::simd::float_4 targetFreq = 0.f;
    rack::simd::float_4 currentFreq = 0.f;

    float glideAmount = 0.f; // should range from 0 - 1

    void initialize(rack::simd::float_4 initialFreq);
    void process(float deltaTime);
};
