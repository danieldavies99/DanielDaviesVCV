#pragma once
#include <string>
#include <rack.hpp>

struct BendWavetable
{
	std::string debugName = "default";
	enum InterpolationMode
	{
		NONE,
		LINEAR,
		CUBIC_SPLINE
	};

	int resolution = 131072;
	float phaseShift = 0.f;
	float table[131072];

	rack::simd::float_4 getValue(rack::simd::float_4 phase, InterpolationMode interpolationMode);
	virtual void generate() {};
};

struct BendTriTable : BendWavetable
{
	BendTriTable()
	{
		generate();
	}
	void generate() override;
};

struct BendSinTable : BendWavetable
{
	BendSinTable()
	{
		phaseShift = -0.25;
		debugName = "sin";
		generate();
	}
	void generate() override;
};

struct BendAnalogSquareTable : BendWavetable
{
	float envelopeFactor;
	BendAnalogSquareTable()
	{
		envelopeFactor = 0.75;
		generate();
	}
	void generate() override;
};

struct BendPerfectSquareTable : BendWavetable
{
	BendPerfectSquareTable()
	{
		generate();
	}
	void generate() override;
};