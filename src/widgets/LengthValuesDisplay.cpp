#include "LengthValuesDisplay.hpp"
#include <functional>

using namespace rack;

void LengthValuesDisplay::process()
{
    darkenAll();
    drawLetter(*val0, 0, 0);
    drawLetter(*val1, 17, 0);
    drawLetter(*val2, 34, 0);
    drawLetter(*val3, 51, 0);
}
