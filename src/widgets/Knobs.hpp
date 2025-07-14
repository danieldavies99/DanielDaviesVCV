#pragma once
#include <rack.hpp>
#include "DanielDavies.hpp"

struct RedKnob : rack::RoundKnob
{
	RedKnob()
	{
        setSvg(rack::Svg::load(rack::asset::plugin(pluginInstance,"res/RedKnob.svg")));
	}
};

struct SteppedRedKnob : rack::RoundKnob
{
	SteppedRedKnob()
	{
        setSvg(rack::Svg::load(rack::asset::plugin(pluginInstance,"res/RedKnob.svg")));
		snap = true;
	}
};