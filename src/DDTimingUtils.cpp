#include "plugin.hpp"

using namespace rack;

void IgnoreClockAfterResetTimer::resetTriggered() {
	timer.reset();
	shouldIgnore = true;
};

void IgnoreClockAfterResetTimer::process(float deltaTime) {
	timer.process(deltaTime);
	if(timer.time > 0.001) {
		shouldIgnore = false;
	}
};

void ClockTracker::nextClock() {
	gatesSinceLastStepR0++;
	gatesSinceLastStepR1++;
	gatesSinceLastStepR2++;
	if(gatesSinceLastStepR0 >= divideR0) {
		nextStepR0();
		gatesSinceLastStepR0 = 0;
		setHasPulsedThisStepForRow(0, false);
	}
	if(gatesSinceLastStepR1 >= divideR1) {
		nextStepR1();
		gatesSinceLastStepR1 = 0;
		setHasPulsedThisStepForRow(1, false);
	}
	if(gatesSinceLastStepR2 >= divideR2) {
		nextStepR2();
		gatesSinceLastStepR2 = 0;
		setHasPulsedThisStepForRow(2, false);
	}
};

void ClockTracker::nextStepR0() {
	currentStepR0 += 1;
	if (currentStepR0 >= numSteps) {
		currentStepR0 = 0;
	}
};

void ClockTracker::nextStepR1() {
	currentStepR1 += 1;
	if (currentStepR1 >= numSteps) {
		currentStepR1 = 0;
	}
};

void ClockTracker::nextStepR2() {
	currentStepR2 += 1;
	if (currentStepR2 >= numSteps) {
		currentStepR2 = 0;
	}
};

int ClockTracker::getCurrentStepForRow(short row) {
	switch (row)
	{
		case 0:
			return currentStepR0;
		case 1:
			return currentStepR1;
		case 2:
			return currentStepR2;
	}
	return 0;
};

bool ClockTracker::getHasPulsedThisStepForRow(short row) {
	switch (row)
	{
		case 0:
			return hasPulsedThisStepR0;
		case 1:
			return hasPulsedThisStepR1;
		case 2:
			return hasPulsedThisStepR2;
	}
	return false;
};

void ClockTracker::setHasPulsedThisStepForRow(short row, bool val) {
	switch (row)
	{
		case 0:
			hasPulsedThisStepR0 = val;
			break;
		case 1:
			hasPulsedThisStepR1 = val;
			break;
		case 2:
			hasPulsedThisStepR2 = val;
			break;
	}
};