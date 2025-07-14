#pragma once
#include <rack.hpp>
#include "DanielDavies.hpp"

struct DigitDisplay : rack::SvgWidget
{
	std::shared_ptr<rack::Svg> digit0 = rack::Svg::load(rack::asset::plugin(pluginInstance, "res/DigitDisplay0.svg")); //rack::Svg::load(rack::asset::system("res/DigitDisplay0.svg"));
	std::shared_ptr<rack::Svg> digit1 = rack::Svg::load(rack::asset::plugin(pluginInstance,"res/DigitDisplay1.svg"));
	std::shared_ptr<rack::Svg> digit2 = rack::Svg::load(rack::asset::plugin(pluginInstance,"res/DigitDisplay2.svg"));
	std::shared_ptr<rack::Svg> digit3 = rack::Svg::load(rack::asset::plugin(pluginInstance,"res/DigitDisplay3.svg"));
	std::shared_ptr<rack::Svg> digit4 = rack::Svg::load(rack::asset::plugin(pluginInstance,"res/DigitDisplay4.svg"));
	std::shared_ptr<rack::Svg> digit5 = rack::Svg::load(rack::asset::plugin(pluginInstance,"res/DigitDisplay5.svg"));
	std::shared_ptr<rack::Svg> digit6 = rack::Svg::load(rack::asset::plugin(pluginInstance,"res/DigitDisplay6.svg"));
	std::shared_ptr<rack::Svg> digit7 = rack::Svg::load(rack::asset::plugin(pluginInstance,"res/DigitDisplay7.svg"));
	std::shared_ptr<rack::Svg> digit8 = rack::Svg::load(rack::asset::plugin(pluginInstance,"res/DigitDisplay8.svg"));
	std::shared_ptr<rack::Svg> digit9 = rack::Svg::load(rack::asset::plugin(pluginInstance,"res/DigitDisplay9.svg"));
	std::shared_ptr<rack::Svg> digitDash = rack::Svg::load(rack::asset::plugin(pluginInstance,"res/DigitDisplayDash.svg"));
	std::shared_ptr<rack::Svg> digitOff = rack::Svg::load(rack::asset::plugin(pluginInstance,"res/DigitDisplayOff.svg"));

	int *value = 0;
	bool *showDashes = 0;

	int numDigits = 2;

	DigitDisplay() {}

	void draw(const DrawArgs &args) override;
private:
	std::string formatDigitValue(int value);
};

struct TwoDigitDisplay : DigitDisplay
{
	TwoDigitDisplay() { numDigits = 2; }
};

struct ThreeDigitDisplay : DigitDisplay
{
	ThreeDigitDisplay() { numDigits = 3; }
};
