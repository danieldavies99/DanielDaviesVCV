#include "OledPixelDisplay.hpp"

using namespace rack;

void OledPixelDisplay::initialize()
{
    box.size.x = (numPixelsX * pixelWidthWithGaps) + (2 * borderSize);
    box.size.y = numPixelsY * pixelWidthWithGaps + (2 * borderSize);
    for (int i = 0; i < numPixelsX; i++)
    {
        std::vector<OledPixel> newPixelRow;
        for (int j = 0; j < numPixelsY; j++)
        {
            OledPixel newPixel;
            newPixel.x = i;
            newPixel.y = j;
            newPixel.isLit = false;
            newPixel.color = nvgRGBA(233, 79, 61, 255);
            newPixelRow.push_back(newPixel);
        }
        pixels.push_back(newPixelRow);
    }
}

void OledPixelDisplay::lightPixel(int x, int y, int offsetX, int offsetY, NVGcolor color)
{
    if (x + offsetX < numPixelsX && y + offsetY < numPixelsY)
    {
        pixels[x + offsetX][y + offsetY].isLit = true;
        pixels[x + offsetX][y + offsetY].color = color;
    }
}

void OledPixelDisplay::drawLayer(const DrawArgs &args, int layer)
{
    if (layer != 1)
        return;

    process();

    nvgBeginPath(args.vg);
    nvgRoundedRect(args.vg, 0, 0, pixelWidthWithGaps * numPixelsX + (borderSize * 2), pixelWidthWithGaps * numPixelsY + (borderSize * 2), 1);
    nvgFillColor(args.vg, nvgRGBA(0, 0, 0, 255));
    nvgFill(args.vg);

    drawGrid(args);
}


void OledPixelDisplay::lightAll()
{
    for (int i = 0; i < numPixelsX; i++)
    {
        for (int j = 0; j < numPixelsY; j++)
        {
            pixels[i][j].isLit = true;
        }
    }
}

void OledPixelDisplay::darkenAll()
{
    for (int i = 0; i < numPixelsX; i++)
    {
        for (int j = 0; j < numPixelsY; j++)
        {
            pixels[i][j].isLit = false;
        }
    }
}

void OledPixelDisplay::drawGrid(const DrawArgs &args)
{
    nvgTranslate(args.vg, borderSize, borderSize);
    if ((int)pixels[0].size() < numPixelsY || (int)pixels.size() < numPixelsX)
    {
        return;
    }
    for (int i = 0; i < numPixelsX; i++)
    {
        for (int j = 0; j < numPixelsY; j++)
        {
            if (pixels[i][j].isLit == true)
            {
                nvgBeginPath(args.vg);
                nvgRect(
                    args.vg,
                    pixelWidthWithGaps * i,
                    pixelWidthWithGaps * j,
                    pixelWidth,
                    pixelWidth);
                nvgFillColor(args.vg, pixels[i][j].color);
                nvgFill(args.vg);
            }
        }
    }
}
