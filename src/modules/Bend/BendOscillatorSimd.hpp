#pragma once
#include <rack.hpp>
#include "BendWavetables.hpp"
#include "BendMinBlep.hpp"

static const BendMinBlep<16, 16>& getBendMinBlep() {
    static BendMinBlep<16, 16> minBlep;
    return minBlep;
}

struct BendOscillatorSimd
{
    rack::simd::float_4 bend = 0.5f;
    rack::simd::float_4 amplitude = 1.f;
    rack::simd::float_4 phase = 0.f;
    rack::simd::float_4 freq = 0.f;

    BendWavetable::InterpolationMode interpolationMode = BendWavetable::InterpolationMode::LINEAR;

    bool syncEnabled = false;
    rack::simd::float_4 sync = 0.f;
    rack::simd::float_4 lastSync = 0.f;

    bool unipolar = false;
    bool usePerfectSquare = false;

    int channels = 0;

    rack::simd::float_4 sinOut = 0.f;
    rack::simd::float_4 squareOut = 0.f;
    rack::simd::float_4 triOut = 0.f;
    rack::simd::float_4 noiseOut = 0.f;

    void process(float deltaTime);
    void setSampleTime(float sampleTime);

    BendSinTable sinTable;
    BendTriTable triTable;
    BendAnalogSquareTable analogSquareTable;
    BendPerfectSquareTable perfectSquareTable;

    float generateNoise();

    // minBLEP correction buffers (kernel spans 2*Z = 32 samples)
    BendMinBlepBuffer<32, rack::simd::float_4> sqrMinBlep;
    BendMinBlepBuffer<32, rack::simd::float_4> triMinBlep;

    // One-pole DC blocker state and coefficient for sqr and tri
    rack::simd::float_4 sqrDCState = 0.f;
    rack::simd::float_4 triDCState = 0.f;
    float dcAlpha = 0.f;
};
