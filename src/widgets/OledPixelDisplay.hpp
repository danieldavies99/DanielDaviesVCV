#pragma once

#include <rack.hpp>

struct OledPixel
{
    int x;
    int y;
    bool isLit;
};

struct OledPixelDisplay : rack::widget::Widget
{
    std::vector<std::vector<OledPixel>> pixels;
    int numPixelsX = 0;
    int numPixelsY = 0;
    NVGcolor pixelColor = nvgRGBA(233, 79, 61, 255);

    double pixelWidth = rack::mm2px(1.03);
    double pixelWidthWithGaps = rack::mm2px(1.04);
    double borderSize = rack::mm2px(2.0);

    void initialize();
    void lightPixel(int x, int y, int offsetX, int offsetY);
    void lightAll();
    void darkenAll();
    void drawGrid(const DrawArgs &args);
    void drawLayer(const DrawArgs &args, int layer) override;
    virtual void process() {};
};