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

void SequelClockTracker::nextClock() {
	for(int i = 0; i < numSteps; i++) {
		gatesSinceLastStepTracker[i]++;
		if(gatesSinceLastStepTracker[i] >= divideTracker[i]) {
			nextStepForRow(i);
			gatesSinceLastStepTracker[i] = 0;
			setHasPulsedThisStepForRow(i, false);
		}
	}
};

void SequelClockTracker::nextStepForRow(short row) {
	currentStepTracker[row] += 1;
	if(currentStepTracker[row] >= numSteps) {
		currentStepTracker[row] = 0;
	}
}

void SequelClockTracker::resetStepTrackers() {
	for(int i = 0; i < numRows; i++){
		currentStepTracker[i] = 0;
	}
}

void SequelClockTracker::resetGatesSinceLastStepTrackers() {
	for(int i = 0; i < numRows; i++){
		gatesSinceLastStepTracker[i] = 0;
	}
}

void SequelClockTracker::resetHasPulsedThisStepTrackers() {
	for(int i = 0; i < numRows; i++) {
		hasPulsedThisStepTracker[i] = 0;
	}
}

int SequelClockTracker::getCurrentStepForRow(short row) {
	return currentStepTracker[row];
};

bool SequelClockTracker::getHasPulsedThisStepForRow(short row) {
	return hasPulsedThisStepTracker[row];
};

void SequelClockTracker::setHasPulsedThisStepForRow(short row, bool val) {
	hasPulsedThisStepTracker[row] = val;
};


void JamesClockTracker::nextClock() {
	for(int i = 0; i < numRows; i++) {
		setHasPulsedThisStepForRow(i, false);
	}
	clocksSinceLastStart++;
	if(clocksSinceLastStart >= globalClockDivide*numSteps) {
		clocksSinceLastStart = 0;
	}
};

int JamesClockTracker::getCurrentStep() {
	return floor(clocksSinceLastStart / globalClockDivide);
};

int JamesClockTracker::getClocksSinceStart() {
	return clocksSinceLastStart;
};

int JamesClockTracker::getRushForRow(short row) {
	return rushTracker[row];
};

int JamesClockTracker::getClocksSinceLastStep() {
	return getClocksSinceStart() % globalClockDivide;
};

void JamesClockTracker::setHasPulsedThisStepForRow(int row, bool val) {
	hasPulsedThisClockTracker[row] = val;
};