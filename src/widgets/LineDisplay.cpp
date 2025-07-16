#include "LineDisplay.hpp"

using namespace rack;

void LineDisplay::process()
{
    darkenAll();

    PortWidget* input1Port = moduleWidget->getInput(input1portId);
    CableWidget* input1Cable =  APP->scene->rack->getTopCable(input1Port);
    NVGcolor input1Color = input1Cable ? input1Cable->color : nvgRGBA(233, 79, 61, 0);

    PortWidget* input2Port = moduleWidget->getInput(input2portId);
    CableWidget* input2Cable =  APP->scene->rack->getTopCable(input2Port);
    NVGcolor input2Color = input2Cable ? input2Cable->color : nvgRGBA(233, 79, 61, 0);


    PortWidget* input3Port = moduleWidget->getInput(input3portId);
    CableWidget* input3Cable =  APP->scene->rack->getTopCable(input3Port);
    NVGcolor input3Color = input3Cable ? input3Cable->color : nvgRGBA(233, 79, 61, 0);

    PortWidget* input4Port = moduleWidget->getInput(input4portId);
    CableWidget* input4Cable =  APP->scene->rack->getTopCable(input4Port);
    NVGcolor input4Color = input4Cable ? input4Cable->color : nvgRGBA(233, 79, 61, 0);

    if (!*matchCableColors) {
        input1Color = nvgRGBA(233, 79, 61, 255);
        input2Color = nvgRGBA(233, 79, 61, 255);
        input3Color = nvgRGBA(233, 79, 61, 255);
        input4Color = nvgRGBA(233, 79, 61, 255);
    }

    // TODO: there has to be a way to write this that doesn't use 4 switch statements
    switch (*output1Index)
    {
    case 0:
        if (*in1connected)
        {
            drawLine(0, 5, numPixelsX, 5, input1Color);
        }
        break;
    case 1:
        if (*in2connected)
        {
            drawLine(0, 25, numPixelsX, 5, input2Color);
        }
        break;
    case 2:
        if (*in3connected)
        {
            drawLine(0, 45, numPixelsX, 5, input3Color);
        }
        break;
    case 3:
        if (*in4connected)
        {
            drawLine(0, 65, numPixelsX, 5, input4Color);
        }
        break;
    }

    switch (*output2Index)
    {
    case 0:
        if (*in1connected)
        {
            drawLine(0, 5, numPixelsX, 25, input1Color);
        }
        break;
    case 1:
        if (*in2connected)
        {
            drawLine(0, 25, numPixelsX, 25, input2Color);
        }
        break;
    case 2:
        if (*in3connected)
        {
            drawLine(0, 45, numPixelsX, 25, input3Color);
        }
        break;
    case 3:
        if (*in4connected)
        {
            drawLine(0, 65, numPixelsX, 25, input4Color);
        }
        break;
    }

    switch (*output3Index)
    {
    case 0:
        if (*in1connected)
        {
            drawLine(0, 5, numPixelsX, 45, input1Color);
        }
        break;
    case 1:
        if (*in2connected)
        {
            drawLine(0, 25, numPixelsX, 45, input2Color);
        }
        break;
    case 2:
        if (*in3connected)
        {
            drawLine(0, 45, numPixelsX, 45, input3Color);
        }
        break;
    case 3:
        if (*in4connected)
        {
            drawLine(0, 65, numPixelsX, 45, input4Color);
        }
        break;
    }

    switch (*output4Index)
    {
    case 0:
        if (*in1connected)
        {
            drawLine(0, 5, numPixelsX, 65, input1Color);
        }
        break;
    case 1:
        if (*in2connected)
        {
            drawLine(0, 25, numPixelsX, 65, input2Color);
        }
        break;
    case 2:
        if (*in3connected)
        {
            drawLine(0, 45, numPixelsX, 65, input3Color);
        }
        break;
    case 3:
        if (*in4connected)
        {
            drawLine(0, 65, numPixelsX, 65, input4Color);
        }
        break;
    }
}

void LineDisplay::drawLine(int x1, int y1, int x2, int y2, NVGcolor color)
{   
    // uses EEFLA, based off https://stackoverflow.com/questions/10060046/drawing-lines-with-bresenhams-line-algorithm
    bool yLonger = false;
    int shortLen = y2 - y1;
    int longLen = x2 - x1;
    if (abs(shortLen) > abs(longLen))
    {
        std::swap(shortLen, longLen);
        yLonger = true;
    }

    int decInc = (longLen == 0) ? 0 : ((shortLen << 16) / longLen);

    std::string debugString = "";

    if (yLonger)
    {
        y1 *= numPixelsY;
        y2 *= numPixelsY;
        if (longLen >= 0)
            for (int j = 0x8000 + (x1 << 16); y1 <= y2; y1 += numPixelsY, j += decInc) {
                int x = (j >> 16);
                if (x >= 0 && x < numPixelsX)
                    lightPixel(x, y1 / numPixelsY, 0, 0, color);
            }


        else
            for (int j = 0x8000 + (x1 << 16); y1 >= y2; y1 -= numPixelsY, j -= decInc) {
                int x = (j >> 16);
                if (x >= 0 && x < numPixelsX)
                    lightPixel(x, y1 / numPixelsY, 0, 0, color);
            }

    }
    else
    {
        if (longLen >= 0)
            for (int j = 0x8000 + (y1 << 16); x1 <= x2; ++x1, j += decInc) {
                int y = (j >> 16);
                if (y >= 0 && y < numPixelsY)
                     lightPixel(x1, y, 0, 0, color);

            }
        else
            for (int j = 0x8000 + (y1 << 16); x1 >= x2; --x1, j -= decInc){
                int y = (j >> 16);
                if (y >= 0 && y < numPixelsY)
                     lightPixel(x1, y, 0, 0, color);

            }
    }
}
