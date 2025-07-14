#pragma once
#include <rack.hpp>
#include "DanielDavies.hpp"

struct RedSliderMedium : rack::app::SvgSlider
{
    RedSliderMedium()
    {
        setBackgroundSvg(rack::Svg::load(rack::asset::plugin(pluginInstance, "res/SliderBackgroundMedium.svg")));
        setHandleSvg(rack::Svg::load(rack::asset::plugin(pluginInstance, "res/RedSlideKnob.svg")));
        minHandlePos = rack::mm2px(rack::Vec(-1.f, 0.f));
        maxHandlePos = rack::mm2px(rack::Vec(20.5f, 0.f));
        horizontal = true;
    }
};