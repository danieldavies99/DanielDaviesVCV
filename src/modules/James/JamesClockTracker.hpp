#pragma once
#include <vector>
#include <cmath>

struct JamesClockTracker
{

    JamesClockTracker()
    {
        numSteps = 16;
        numRows = 6;
        initializeRows();
    }

    short numRows;
    short numSteps;
    short globalClockDivide = 16;

    short clocksSinceLastStart = 0;

    std::vector<int> rushTracker;

    void initializeRows();
    void reset();

    void nextClock();
    int getCurrentStep();
    int getNextStep();
    int getCurrentStepAccountingForRush(short row);
    int getClocksSinceStart();
    int getClocksSinceLastStep();
    int getRushForRow(short row);

    void setRushForRow(short row, short rush);
};