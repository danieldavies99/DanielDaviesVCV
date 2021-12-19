#pragma once
#include <rack.hpp>

using namespace rack;

// Declare the Plugin, defined in plugin.cpp
extern Plugin* pluginInstance;

// Declare each Model, defined in each module source file
extern Model* modelSequel8Module;
extern Model* modelSequel16Module;

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

struct CKD6InvisibleLatch : app::SvgSwitch {
	CKD6InvisibleLatch() {
		momentary = false;
        latch = true; // this is WEIRD seems to be reversed (value is latched but animation frame is as if it's momentary)
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


// Timing Utils
struct IgnoreClockAfterResetTimer {

	dsp::Timer timer;
	bool shouldIgnore = false;

	void resetTriggered();
	void process(float deltaTime);
};

struct ClockTracker {

    ClockTracker(short initializeNumSteps) {
        numSteps = initializeNumSteps;
    }

	short numSteps;

	short currentStepR0 = 0;
	short currentStepR1 = 0;
	short currentStepR2 = 0;

	int gatesSinceLastStepR0 = 0;
	int gatesSinceLastStepR1 = 0;
	int gatesSinceLastStepR2 = 0;

	bool hasPulsedThisStepR0 = false;
	bool hasPulsedThisStepR1 = false;
	bool hasPulsedThisStepR2 = false;

	int divideR0 = 1;
	int divideR1 = 1;
	int divideR2 = 1;

	void nextClock();

	void nextStepR0();

	void nextStepR1();

	void nextStepR2();

	int getCurrentStepForRow(short row);

	bool getHasPulsedThisStepForRow(short row);

	void setHasPulsedThisStepForRow(short row, bool val);
};
// End