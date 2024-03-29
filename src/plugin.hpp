#pragma once
#include <array>
#include <rack.hpp>

using namespace rack;

// Declare the Plugin, defined in plugin.cpp
extern Plugin *pluginInstance;

// Declare each Model, defined in each module source file
extern Model *modelSequel8Module;
extern Model *modelSequel16Module;
extern Model *modelSequelSave;
extern Model *modelQuantify;
extern Model *modelSamuel;
extern Model *modelBlank3;
extern Model *modelBlank5;
extern Model *modelBend;
extern Model *modelJames;

/************************** KNOBS **************************/

struct RedKnob : RoundKnob
{
	RedKnob()
	{
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/RedKnob.svg")));
	}
};

struct SteppedRedKnob : RoundKnob
{
	SteppedRedKnob()
	{
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/RedKnob.svg")));
		snap = true;
	}
};

struct CKD6Latch : app::SvgSwitch
{
	CKD6Latch()
	{
		momentary = false;
		latch = false; // this is WEIRD seems to be reversed
		addFrame(Svg::load(asset::system("res/ComponentLibrary/CKD6_0.svg")));
		addFrame(Svg::load(asset::system("res/ComponentLibrary/CKD6_1.svg")));
	}
};

struct CKD6InvisibleLatch : app::SvgSwitch
{
	CKD6InvisibleLatch()
	{
		momentary = false;
		latch = true; // this is WEIRD seems to be reversed (value is latched but animation frame is as if it's momentary)
		addFrame(Svg::load(asset::system("res/ComponentLibrary/CKD6_0.svg")));
		addFrame(Svg::load(asset::system("res/ComponentLibrary/CKD6_1.svg")));
	}
};

struct RedSliderMedium : app::SvgSlider
{
	RedSliderMedium()
	{
		setBackgroundSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/SliderBackgroundMedium.svg")));
		setHandleSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/RedSlideKnob.svg")));
		minHandlePos = mm2px(Vec(-1.f, 0.f));
		maxHandlePos = mm2px(Vec(20.5f, 0.f));
		horizontal = true;
	}
};

// Custom Widgets
struct DigitDisplay : SvgWidget
{
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

struct KeyboardDisplay : SvgWidget
{
	std::shared_ptr<rack::Svg> keyOnC = APP->window->loadSvg(asset::plugin(pluginInstance, "res/KeyOnC.svg"));
	std::shared_ptr<rack::Svg> keyOnD = APP->window->loadSvg(asset::plugin(pluginInstance, "res/KeyOnD.svg"));
	std::shared_ptr<rack::Svg> keyOnE = APP->window->loadSvg(asset::plugin(pluginInstance, "res/KeyOnE.svg"));
	std::shared_ptr<rack::Svg> keyOnF = APP->window->loadSvg(asset::plugin(pluginInstance, "res/KeyOnF.svg"));
	std::shared_ptr<rack::Svg> keyOnG = APP->window->loadSvg(asset::plugin(pluginInstance, "res/KeyOnG.svg"));
	std::shared_ptr<rack::Svg> keyOnA = APP->window->loadSvg(asset::plugin(pluginInstance, "res/KeyOnA.svg"));
	std::shared_ptr<rack::Svg> keyOnB = APP->window->loadSvg(asset::plugin(pluginInstance, "res/KeyOnB.svg"));
	std::shared_ptr<rack::Svg> keyOnSharp = APP->window->loadSvg(asset::plugin(pluginInstance, "res/KeyOnSharp.svg"));

	double *keyOnValue = 0;

	KeyboardDisplay() {}

	void draw(const DrawArgs &args) override;

private:
	std::string formatDigitValue(int value);
};

struct OledPixel
{
	int x;
	int y;
	bool isLit;
};

struct OledPixelDisplay : widget::Widget
{
	std::vector<std::vector<OledPixel>> pixels;
	int numPixelsX = 0;
	int numPixelsY = 0;
	NVGcolor pixelColor = nvgRGBA(233, 79, 61, 255);

	double pixelWidth = mm2px(1.03);
	double pixelWidthWithGaps = mm2px(1.04);
	double borderSize = mm2px(2.0);

	void initialize();
	void lightPixel(int x, int y, int offsetX, int offsetY);
	void lightAll();
	void darkenAll();
	void drawGrid(const DrawArgs &args);
	void drawLayer(const DrawArgs &args, int layer) override;
	virtual void process(){};
};

struct CharacterDisplay : OledPixelDisplay
{
	void drawLetter(char letter, int x, int y);
};

struct TextInputDisplay : CharacterDisplay
{
	TextInputDisplay()
	{
		numPixelsX = 83; // should be multiple of six minus one for letters
		numPixelsY = 47; // should be multiple of eight minus one for letters
	}
	bool isSelected = false;
	bool shouldShowCursor = true;
	int framesSinceLastCursorChange = 0;
	std::string *message;

	void onButton(const ButtonEvent &e) override;
	void onSelectKey(const SelectKeyEvent &e) override;
	void onSelect(const SelectEvent &e) override;
	void onDeselect(const DeselectEvent &e) override;

	void drawCursor(int x, int y);
	void drawMessage();
	void process() override;
};
struct LengthValuesDisplay : CharacterDisplay
{
	char *val0;
	char *val1;
	char *val2;
	char *val3;

	LengthValuesDisplay()
	{
		numPixelsX = 71 - 14; // should be multiple of six minus one for letters
		numPixelsY = 7;		  // should be multiple of eight minus one for letters
	}
	void process() override;
};
// End

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

// Timing Utils
struct IgnoreClockAfterResetTimer
{

	dsp::Timer timer;
	bool shouldIgnore = false;

	void resetTriggered();
	void process(float deltaTime);
};

struct JamesClockTracker
{

	JamesClockTracker()
	{
		numSteps = 16;
		numRows = 6;
		initializeRows();
	}

	short numRows;
	short numSteps;
	short globalClockDivide = 16;

	short clocksSinceLastStart = 0;

	std::vector<int> rushTracker;

	void initializeRows();
	void reset();

	void nextClock();
	int getCurrentStep();
	int getNextStep();
	int getCurrentStepAccountingForRush(short row);
	int getClocksSinceStart();
	int getClocksSinceLastStep();
	int getRushForRow(short row);

	void setRushForRow(short row, short rush);
};

struct SequelClockTracker
{

	short numSteps;
	short numRows;

	std::vector<short> currentStepTracker;
	std::vector<short> gatesSinceLastStepTracker;
	std::vector<short> divideTracker;
	std::vector<bool> hasPulsedThisStepTracker;

	void initializeRows();

	void nextClock();

	void nextStepForRow(short row);

	int getCurrentStepForRow(short row);

	void resetStepTrackers();

	void resetGatesSinceLastStepTrackers();

	void resetHasPulsedThisStepTrackers();

	bool getHasPulsedThisStepForRow(short row);

	void setHasPulsedThisStepForRow(short row, bool val);
};

struct Sequel8ClockTracker : SequelClockTracker
{
	Sequel8ClockTracker()
	{
		numSteps = 8;
		numRows = 3;
		initializeRows();
	}
};

struct Sequel16ClockTracker : SequelClockTracker
{
	Sequel16ClockTracker()
	{
		numSteps = 16;
		numRows = 3;
		initializeRows();
	}
};

struct SequenceGenerator
{
	int dotLength = 1;
	int dashLength = 3;
	int newLetterLength = 3;
	int newWordLength = 7;
	std::vector<bool> sequence;
	void pushDot();
	void pushDash();
	void pushNewPartInLetter();
	void pushNewLetter();
	void pushNewWord();
	void generateSequence(std::string message);
};
// End

struct SequelSaveInterface
{
	std::array<std::array<double, 16>, 3> knobVals = {{0.f}};
	std::array<std::array<bool, 16>, 3> switchVals = {{false}};
	std::array<double, 3> clockDivideVals = {1.f, 1.f, 1.f};

	double speed = 0.5f;
	int stepCount = 8;
	bool triggerMode = true;

	bool isDirty = false;
};

struct BendWavetable
{	
	std::string debugName = "default";
	enum InterpolationMode { NONE, LINEAR, CUBIC_SPLINE };

	int resolution = 131072;
	float phaseShift = 0.f;
	float table[131072];

	simd::float_4 getValue(simd::float_4 phase, InterpolationMode interpolationMode);
	virtual void generate(){};
};

struct BendTriTable : BendWavetable
{
	BendTriTable()
	{
		generate();
	}
	void generate() override;
};

struct BendSinTable : BendWavetable
{
	BendSinTable()
	{
		phaseShift = -0.25;
		debugName = "sin";
		generate();
	}
	void generate() override;
};

struct BendAnalogSquareTable : BendWavetable
{
	float envelopeFactor;
	BendAnalogSquareTable()
	{
		envelopeFactor = 0.75;
		generate();
	}
	void generate() override;
};

struct BendPerfectSquareTable : BendWavetable
{
	BendPerfectSquareTable()
	{
		generate();
	}
	void generate() override;
};

struct BendOscillatorSimd
{
	simd::float_4 bend = 0.5f;
	simd::float_4 amplitude = 1.f;
	simd::float_4 phase = 0.f;
	simd::float_4 freq = 0.f;

	BendWavetable::InterpolationMode interpolationMode = BendWavetable::InterpolationMode::LINEAR;

	bool syncEnabled = false;
	simd::float_4 sync = 0.f;
	simd::float_4 lastSync = 0.f;

	bool unipolar = false;

	// in LFO mode, we should use a perfect square
	// instead of the "analog" version
	bool usePerfectSquare = false;

	int channels = 0;

	simd::float_4 sinOut = 0.f;
	simd::float_4 squareOut = 0.f;
	simd::float_4 triOut = 0.f;
	simd::float_4 noiseOut = 0.f;

	void process(float deltaTime);

	BendSinTable sinTable;
	BendTriTable triTable;
	BendAnalogSquareTable analogSquareTable;
	BendPerfectSquareTable perfectSquareTable;

	float generateNoise();
};

struct GlideCalculator
{
	bool initialized = false;

	simd::float_4 targetFreq = 0.f;
	simd::float_4 currentFreq = 0.f;

	float glideAmount = 0.f; // should range from 0 - 1

	void initialize(simd::float_4 initialFreq);
	void process(float deltaTime);
};