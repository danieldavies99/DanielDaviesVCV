#pragma once
#include <rack.hpp>

struct CKD6Latch : rack::app::SvgSwitch
{
    CKD6Latch()
    {
        momentary = false;
        latch = false; // this is WEIRD seems to be reversed
        addFrame(rack::Svg::load(rack::asset::system("res/ComponentLibrary/CKD6_0.svg")));
        addFrame(rack::Svg::load(rack::asset::system("res/ComponentLibrary/CKD6_1.svg")));
    }
};

struct CKD6InvisibleLatch : rack::app::SvgSwitch
{
    CKD6InvisibleLatch()
    {
        momentary = false;
        latch = true; // this is WEIRD seems to be reversed (value is latched but animation frame is as if it's momentary)
        addFrame(rack::Svg::load(rack::asset::system("res/ComponentLibrary/CKD6_0.svg")));
        addFrame(rack::Svg::load(rack::asset::system("res/ComponentLibrary/CKD6_1.svg")));
    }
};