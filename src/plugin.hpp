#pragma once
#include <rack.hpp>

using namespace rack;

// Declare the Plugin, defined in plugin.cpp
extern Plugin* pluginInstance;

// Declare each Model, defined in each module source file
extern Model* modelSequel8Module;
// extern Model* modelSequel16Module;

/************************** KNOBS **************************/

struct RedKnob : RoundKnob {
    RedKnob() {
        setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/RedKnob.svg")));
    }
};

struct SteppedRedKnob : RoundKnob {
    SteppedRedKnob() {
        setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/RedKnob.svg")));
        snap = true;
    }
};

struct CKD6Latch : app::SvgSwitch {
	CKD6Latch() {
		momentary = false;
        latch = false; // this is WEIRD seems to be reversed
		addFrame(Svg::load(asset::system("res/ComponentLibrary/CKD6_0.svg")));
		addFrame(Svg::load(asset::system("res/ComponentLibrary/CKD6_1.svg")));
	}
};

struct DigitDisplay : SvgWidget {
    std::shared_ptr<rack::Svg> digit0 = APP->window->loadSvg(asset::plugin(pluginInstance, "res/DigitDisplay0.svg"));
    std::shared_ptr<rack::Svg> digit1 = APP->window->loadSvg(asset::plugin(pluginInstance, "res/DigitDisplay1.svg"));
    std::shared_ptr<rack::Svg> digit2 = APP->window->loadSvg(asset::plugin(pluginInstance, "res/DigitDisplay2.svg"));
    std::shared_ptr<rack::Svg> digit3 = APP->window->loadSvg(asset::plugin(pluginInstance, "res/DigitDisplay3.svg"));
    std::shared_ptr<rack::Svg> digit4 = APP->window->loadSvg(asset::plugin(pluginInstance, "res/DigitDisplay4.svg"));
    std::shared_ptr<rack::Svg> digit5 = APP->window->loadSvg(asset::plugin(pluginInstance, "res/DigitDisplay5.svg"));
    std::shared_ptr<rack::Svg> digit6 = APP->window->loadSvg(asset::plugin(pluginInstance, "res/DigitDisplay6.svg"));
    std::shared_ptr<rack::Svg> digit7 = APP->window->loadSvg(asset::plugin(pluginInstance, "res/DigitDisplay7.svg"));
    std::shared_ptr<rack::Svg> digit8 = APP->window->loadSvg(asset::plugin(pluginInstance, "res/DigitDisplay8.svg"));
    std::shared_ptr<rack::Svg> digit9 = APP->window->loadSvg(asset::plugin(pluginInstance, "res/DigitDisplay9.svg"));

    int *value = 0;

    DigitDisplay() {}

    void draw(const DrawArgs &args) override;

    private:
        std::string formatDigitValue(int value);
};