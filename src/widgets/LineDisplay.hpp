#pragma once
#include "widgets/OledPixelDisplay.hpp"
#include "nanovg.h"

// TODO: abstract a new class that includes the specific draw functions
// for the switch module
struct LineDisplay : OledPixelDisplay
{
    // Knot* module;
	rack::ModuleWidget* moduleWidget;

    LineDisplay()
    {
        numPixelsX = 39;
        numPixelsY = 72;
    }

    void drawLine(int x1, int y1, int x2, int y2, NVGcolor color);
    void process() override;

    bool *in1connected;
    bool *in2connected;
    bool *in3connected;
    bool *in4connected;

    int *output1Index;
    int *output2Index;
    int *output3Index;
    int *output4Index;

    int input1portId;
    int input2portId;
    int input3portId;
    int input4portId;
};