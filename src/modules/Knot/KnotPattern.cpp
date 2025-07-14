#include "KnotPattern.hpp"

KnotPattern::KnotPattern(std::string patternString)
{
    patternLength = patternString.length();

    for (int i = 0; i < patternLength; i++)
    {
        this->pattern[i] = charToControl(patternString[i]);
    }

    this->patternLength = patternLength;
}

KnotControl KnotPattern::getNextControl()
{
    KnotControl currentStep = pattern[patternIndex];

    patternIndex += 1;
    if (patternIndex >= patternLength)
    {
        patternIndex = 0;
    }

    return currentStep;
}

void KnotPattern::reset()
{
    patternIndex = 0;
}

KnotControl KnotPattern::charToControl(char c)
{
    switch (c)
    {
    case 'S':
        return ShiftDown;
    case 's':
        return ShiftUp;
    case 'R':
        return Reset;
    case '1':
        return Swap12;
    case '2':
        return Swap23;
    case '3':
        return Swap34;
    case '4':
        return Swap14;
    case '5':
        return Swap13;
    case '6':
        return Swap24;
    case '7':
        return Swap1234;
    case '8':
        return Swap1423;
    case '9':
        return Swap1324;
    case 'U':
        return Undo;
    case 'u':
        return Redo;
    case 'X':
        return Random;
    default:
        return Reset;
    }
}