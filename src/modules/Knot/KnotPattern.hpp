#pragma once
#include <string>

enum KnotControl
{
    ShiftDown,
    ShiftUp,
    Reset,
    Swap12,
    Swap34,
    Swap23,
    Swap14,
    Swap13,
    Swap24,
    Swap1234,
    Swap1423,
    Swap1324,
    Random,
    Undo,
    Redo,
};

struct KnotPattern
{
    KnotControl pattern[64];
    int patternLength = 0;
    int patternIndex = 0;

    KnotPattern(std::string patternString);
    KnotControl getNextControl();
    void reset();

private:
    KnotControl charToControl(char c);
};