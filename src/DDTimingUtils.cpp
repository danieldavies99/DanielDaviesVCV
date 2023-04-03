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
	for(int i = 0; i < numSteps; i++) {
		gatesSinceLastStepTracker[i]++;
		if(gatesSinceLastStepTracker[i] >= divideTracker[i]) {
			nextStepForRow(i);
			gatesSinceLastStepTracker[i] = 0;
			setHasPulsedThisStepForRow(i, false);
		}
	}
};

void ClockTracker::nextStepForRow(short row) {
	currentStepTracker[row] += 1;
	if(currentStepTracker[row] >= numSteps) {
		currentStepTracker[row] = 0;
	}
}

void ClockTracker::resetStepTrackers() {
	for(int i = 0; i < numRows; i++){
		currentStepTracker[i] = 0;
	}
}

void ClockTracker::resetGatesSinceLastStepTrackers() {
	for(int i = 0; i < numRows; i++){
		gatesSinceLastStepTracker[i] = 0;
	}
}

void ClockTracker::resetHasPulsedThisStepTrackers() {
	for(int i = 0; i < numRows; i++) {
		hasPulsedThisStepTracker[i] = 0;
	}
}

int ClockTracker::getCurrentStepForRow(short row) {
	return currentStepTracker[row];
};

bool ClockTracker::getHasPulsedThisStepForRow(short row) {
	return hasPulsedThisStepTracker[row];
};

void ClockTracker::setHasPulsedThisStepForRow(short row, bool val) {
	hasPulsedThisStepTracker[row] = val;
};