#pragma once

struct GateDetector
{
	float lastInput = 0.f;
	
	bool check(float input);
};