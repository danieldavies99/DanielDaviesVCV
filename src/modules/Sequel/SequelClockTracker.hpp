#pragma once
#include <vector>

struct SequelClockTracker
{

	short numSteps;
	short numRows;

	std::vector<short> currentStepTracker;
	std::vector<short> gatesSinceLastStepTracker;
	std::vector<short> divideTracker;
	std::vector<bool> hasPulsedThisStepTracker;

	void initializeRows();

	void nextClock();

	void nextStepForRow(short row);

	int getCurrentStepForRow(short row);

	void resetStepTrackers();

	void resetGatesSinceLastStepTrackers();

	void resetHasPulsedThisStepTrackers();

	bool getHasPulsedThisStepForRow(short row);

	void setHasPulsedThisStepForRow(short row, bool val);
};

struct Sequel8ClockTracker : SequelClockTracker
{
	Sequel8ClockTracker()
	{
		numSteps = 8;
		numRows = 3;
		initializeRows();
	}
};

struct Sequel16ClockTracker : SequelClockTracker
{
	Sequel16ClockTracker()
	{
		numSteps = 16;
		numRows = 3;
		initializeRows();
	}
};