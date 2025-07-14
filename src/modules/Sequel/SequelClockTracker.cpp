#include "SequelClockTracker.hpp"

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