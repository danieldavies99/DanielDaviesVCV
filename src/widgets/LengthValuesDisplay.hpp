#pragma once

#include "CharacterDisplay.hpp"


struct LengthValuesDisplay : CharacterDisplay
{
	char *val0;
	char *val1;
	char *val2;
	char *val3;

	LengthValuesDisplay()
	{
		numPixelsX = 71 - 14; // should be multiple of six minus one for letters
		numPixelsY = 7;		  // should be multiple of eight minus one for letters
	}
	void process() override;
};