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

void SequelClockTracker::initializeRows() {
	for(int i = 0; i < numRows; i++) {
		currentStepTracker.push_back(0);
		gatesSinceLastStepTracker.push_back(0);
		divideTracker.push_back(1);
		hasPulsedThisStepTracker.push_back(false);
	}
};

void SequelClockTracker::nextClock() {
	for(int i = 0; i < numRows; i++) {
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

void JamesClockTracker::initializeRows() {
	for(int i = 0; i < numRows; i++) {
		rushTracker.push_back(0);
	}
};

void JamesClockTracker::reset() {
	clocksSinceLastStart = 0;
};

void JamesClockTracker::nextClock() {
	clocksSinceLastStart++;
	if(clocksSinceLastStart >= globalClockDivide*numSteps) {
		clocksSinceLastStart = 0;
	}
};

void JamesClockTracker::setRushForRow(short row, short rush) {
	rushTracker[row] = rush;
};

int JamesClockTracker::getCurrentStep() {
	return floor(clocksSinceLastStart / globalClockDivide);
};

int JamesClockTracker::getNextStep() {
	int nextStep = getCurrentStep() + 1;
	if(nextStep > numSteps - 1) {
		return 0;
	}
	return nextStep;
};

int JamesClockTracker::getCurrentStepAccountingForRush(short row) {
	const int rush = getRushForRow(row);
    const int clocksSinceStartWithRush = clocksSinceLastStart - rush;
	if(clocksSinceStartWithRush < 0) {
		return numSteps - 1;
	}
	if(clocksSinceStartWithRush > numSteps * globalClockDivide) {
		return 0;
	}
	return floor(clocksSinceStartWithRush / globalClockDivide);
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
