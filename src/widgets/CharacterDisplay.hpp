#pragma once

#include "widgets/OledPixelDisplay.hpp"

struct CharacterDisplay : OledPixelDisplay
{
    void drawLetter(char letter, int x, int y);
};