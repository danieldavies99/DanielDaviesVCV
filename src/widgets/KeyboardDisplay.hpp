#pragma once
#include <rack.hpp>
#include "DanielDavies.hpp"

// TODO, it doesn't really make sense for these values to live here
// I should abstract these values away from the widget
// Quantizer Values
static const double KEY_ON_C = 0;
static const double KEY_ON_C_SHARP = 0.0833;
static const double KEY_ON_D = 0.1666;
static const double KEY_ON_D_SHARP = 0.2500;
static const double KEY_ON_E = 0.3333;
static const double KEY_ON_F = 0.4166;
static const double KEY_ON_F_SHARP = 0.5000;
static const double KEY_ON_G = 0.5833;
static const double KEY_ON_G_SHARP = 0.6666;
static const double KEY_ON_A = 0.7500;
static const double KEY_ON_A_SHARP = 0.8333;
static const double KEY_ON_B = 0.9166;
// End

struct KeyboardDisplay : SvgWidget
{
	std::shared_ptr<rack::Svg> keyOnC = rack::Svg::load(rack::asset::plugin(pluginInstance, "res/KeyOnC.svg"));
	std::shared_ptr<rack::Svg> keyOnD = rack::Svg::load(rack::asset::plugin(pluginInstance, "res/KeyOnD.svg"));
	std::shared_ptr<rack::Svg> keyOnE = rack::Svg::load(rack::asset::plugin(pluginInstance, "res/KeyOnE.svg"));
	std::shared_ptr<rack::Svg> keyOnF = rack::Svg::load(rack::asset::plugin(pluginInstance, "res/KeyOnF.svg"));
	std::shared_ptr<rack::Svg> keyOnG = rack::Svg::load(rack::asset::plugin(pluginInstance, "res/KeyOnG.svg"));
	std::shared_ptr<rack::Svg> keyOnA = rack::Svg::load(rack::asset::plugin(pluginInstance, "res/KeyOnA.svg"));
	std::shared_ptr<rack::Svg> keyOnB = rack::Svg::load(rack::asset::plugin(pluginInstance, "res/KeyOnB.svg"));
	std::shared_ptr<rack::Svg> keyOnSharp = rack::Svg::load(rack::asset::plugin(pluginInstance, "res/KeyOnSharp.svg"));

	double *keyOnValue = 0;

	KeyboardDisplay() {}

	void draw(const DrawArgs &args) override;

private:
	std::string formatDigitValue(int value);
};