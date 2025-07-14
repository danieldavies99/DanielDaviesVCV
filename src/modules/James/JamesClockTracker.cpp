#include "JamesClockTracker.hpp"

void JamesClockTracker::initializeRows()
{
    for (int i = 0; i < numRows; i++)
    {
        rushTracker.push_back(0);
    }
};

void JamesClockTracker::reset()
{
    clocksSinceLastStart = 0;
};

void JamesClockTracker::nextClock()
{
    clocksSinceLastStart++;
    if (clocksSinceLastStart >= globalClockDivide * numSteps)
    {
        clocksSinceLastStart = 0;
    }
};

void JamesClockTracker::setRushForRow(short row, short rush)
{
    rushTracker[row] = rush;
};

int JamesClockTracker::getCurrentStep()
{
    return std::floor(clocksSinceLastStart / globalClockDivide);
};

int JamesClockTracker::getNextStep()
{
    int nextStep = getCurrentStep() + 1;
    if (nextStep > numSteps - 1)
    {
        return 0;
    }
    return nextStep;
};

int JamesClockTracker::getCurrentStepAccountingForRush(short row)
{
    const int rush = getRushForRow(row);
    const int clocksSinceStartWithRush = clocksSinceLastStart - rush;
    if (clocksSinceStartWithRush < 0)
    {
        return numSteps - 1;
    }
    if (clocksSinceStartWithRush > numSteps * globalClockDivide)
    {
        return 0;
    }
    return floor(clocksSinceStartWithRush / globalClockDivide);
};

int JamesClockTracker::getClocksSinceStart()
{
    return clocksSinceLastStart;
};

int JamesClockTracker::getRushForRow(short row)
{
    return rushTracker[row];
};

int JamesClockTracker::getClocksSinceLastStep()
{
    return getClocksSinceStart() % globalClockDivide;
};