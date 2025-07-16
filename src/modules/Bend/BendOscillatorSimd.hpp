#pragma once
#include <rack.hpp>
#include "BendWavetables.hpp"

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

	// in LFO mode, we should use a perfect square
	// instead of the "analog" version
	bool usePerfectSquare = false;

	int channels = 0;

	rack::simd::float_4 sinOut = 0.f;
	rack::simd::float_4 squareOut = 0.f;
	rack::simd::float_4 triOut = 0.f;
	rack::simd::float_4 noiseOut = 0.f;

	void process(float deltaTime);

	BendSinTable sinTable;
	BendTriTable triTable;
	BendAnalogSquareTable analogSquareTable;
	BendPerfectSquareTable perfectSquareTable;

	float generateNoise();
};