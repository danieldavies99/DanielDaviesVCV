#include "DanielDavies.hpp"
#include <unordered_map>
#include "widgets/Knobs.hpp"
#include "widgets/Buttons.hpp"
#include "widgets/KeyboardDisplay.hpp"
#include "utilities/Quantize.hpp"

using namespace rack;

static constexpr int RESOLUTION = 1000; // 1mV resolution
static constexpr int RANGE_MIN = -10 * RESOLUTION; // -10000
static constexpr int RANGE_MAX = 10 * RESOLUTION;  //  10000
static constexpr int TABLE_SIZE = RANGE_MAX - RANGE_MIN; // 20000

struct Quantify : Module
{
	enum ParamId
	{
		KNOB_ATTENUVERT_R0_PARAM,
		SWITCH_NOTE_B_PARAM,
		SWITCH_NOTE_A_SHARP_PARAM,
		SWITCH_NOTE_A_PARAM,
		SWITCH_NOTE_G_SHARP_PARAM,
		SWITCH_NOTE_G_PARAM,
		SWITCH_NOTE_F_SHARP_PARAM,
		KNOB_ATTENUVERT_R1_PARAM,
		SWITCH_NOTE_F_PARAM,
		SWITCH_NOTE_E_PARAM,
		SWITCH_NOTE_D_SHARP_PARAM,
		SWITCH_NOTE_D_PARAM,
		SWITCH_NOTE_C_SHARP_PARAM,
		KNOB_ATTENUVERT_R2_PARAM,
		SWITCH_NOTE_C_PARAM,
		KNOB_TRANSPOSE_PARAM,
		KNOB_NUDGE_PARAM,
		PARAMS_LEN
	};
	enum InputId
	{
		IN_CV_R0_INPUT,
		IN_CV_R1_INPUT,
		IN_CV_R2_INPUT,
		INPUTS_LEN
	};
	enum OutputId
	{
		OUT_CV_R0_OUTPUT,
		OUT_CV_R1_OUTPUT,
		OUT_CV_R2_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId
	{
		LIGHT_KEY_BUTTON_C_LIGHT,
		LIGHT_KEY_BUTTON_C_SHARP_LIGHT,
		LIGHT_KEY_BUTTON_D_LIGHT,
		LIGHT_KEY_BUTTON_D_SHARP_LIGHT,
		LIGHT_KEY_BUTTON_E_LIGHT,
		LIGHT_KEY_BUTTON_F_LIGHT,
		LIGHT_KEY_BUTTON_F_SHARP_LIGHT,
		LIGHT_KEY_BUTTON_G_LIGHT,
		LIGHT_KEY_BUTTON_G_SHARP_LIGHT,
		LIGHT_KEY_BUTTON_A_LIGHT,
		LIGHT_KEY_BUTTON_A_SHARP_LIGHT,
		LIGHT_KEY_BUTTON_B_LIGHT,
		LIGHTS_LEN
	};

	double roundedVoltageR0 = 0;
	double roundedVoltageR1 = 0;
	double roundedVoltageR2 = 0;

	bool displayR0on = 0;
	bool displayR1on = 0;
	bool displayR2on = 0;

	Quantify()
	{
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);

		configParam(KNOB_ATTENUVERT_R0_PARAM, -1.f, 1.f, 0.f, "Attenuvert 1");
		configParam(KNOB_ATTENUVERT_R1_PARAM, -1.f, 1.f, 0.f, "Attenuvert 2");
		configParam(KNOB_ATTENUVERT_R2_PARAM, -1.f, 1.f, 0.f, "Attenuvert 3");
		configParam(KNOB_TRANSPOSE_PARAM, -12.f, 12.f, 0.f, "Transpose");
		configParam(KNOB_NUDGE_PARAM, -2.f, 2.f, 0.f, "Nudge");

		configSwitch(SWITCH_NOTE_B_PARAM, 0.f, 1.f, 0.f, "B", {"Off", "On"});
		configSwitch(SWITCH_NOTE_A_SHARP_PARAM, 0.f, 1.f, 0.f, "A#", {"Off", "On"});
		configSwitch(SWITCH_NOTE_A_PARAM, 0.f, 1.f, 0.f, "A", {"Off", "On"});
		configSwitch(SWITCH_NOTE_G_SHARP_PARAM, 0.f, 1.f, 0.f, "G#", {"Off", "On"});
		configSwitch(SWITCH_NOTE_G_PARAM, 0.f, 1.f, 0.f, "G", {"Off", "On"});
		configSwitch(SWITCH_NOTE_F_SHARP_PARAM, 0.f, 1.f, 0.f, "F#", {"Off", "On"});
		configSwitch(SWITCH_NOTE_F_PARAM, 0.f, 1.f, 0.f, "F", {"Off", "On"});
		configSwitch(SWITCH_NOTE_E_PARAM, 0.f, 1.f, 0.f, "E", {"Off", "On"});
		configSwitch(SWITCH_NOTE_D_SHARP_PARAM, 0.f, 1.f, 0.f, "D#", {"Off", "On"});
		configSwitch(SWITCH_NOTE_D_PARAM, 0.f, 1.f, 0.f, "D", {"Off", "On"});
		configSwitch(SWITCH_NOTE_C_SHARP_PARAM, 0.f, 1.f, 0.f, "C#", {"Off", "On"});
		configSwitch(SWITCH_NOTE_C_PARAM, 0.f, 1.f, 0.f, "C", {"Off", "On"});
		configInput(IN_CV_R0_INPUT, "CV 1");
		configInput(IN_CV_R1_INPUT, "CV 2");
		configInput(IN_CV_R2_INPUT, "CV 3");
		configOutput(OUT_CV_R0_OUTPUT, "CV 1");
		configOutput(OUT_CV_R1_OUTPUT, "CV 2");
		configOutput(OUT_CV_R2_OUTPUT, "CV 3");
	}

	quantize::KeyMask handleKeyButtons()
	{
		quantize::KeyMask mask = 0;

		auto setNote = [&](int paramIndex, int lightIndex, int bitPosition) {
			if (params[paramIndex].getValue() == 1)
			{
				mask |= (1 << bitPosition);
				lights[lightIndex].setBrightness(0.5f);
			}
			else
			{
				lights[lightIndex].setBrightness(0.0f);
			}
		};

		setNote(SWITCH_NOTE_C_PARAM,        LIGHT_KEY_BUTTON_C_LIGHT,        0);
		setNote(SWITCH_NOTE_C_SHARP_PARAM,  LIGHT_KEY_BUTTON_C_SHARP_LIGHT,  1);
		setNote(SWITCH_NOTE_D_PARAM,        LIGHT_KEY_BUTTON_D_LIGHT,        2);
		setNote(SWITCH_NOTE_D_SHARP_PARAM,  LIGHT_KEY_BUTTON_D_SHARP_LIGHT,  3);
		setNote(SWITCH_NOTE_E_PARAM,        LIGHT_KEY_BUTTON_E_LIGHT,        4);
		setNote(SWITCH_NOTE_F_PARAM,        LIGHT_KEY_BUTTON_F_LIGHT,        5);
		setNote(SWITCH_NOTE_F_SHARP_PARAM,  LIGHT_KEY_BUTTON_F_SHARP_LIGHT,  6);
		setNote(SWITCH_NOTE_G_PARAM,        LIGHT_KEY_BUTTON_G_LIGHT,        7);
		setNote(SWITCH_NOTE_G_SHARP_PARAM,  LIGHT_KEY_BUTTON_G_SHARP_LIGHT,  8);
		setNote(SWITCH_NOTE_A_PARAM,        LIGHT_KEY_BUTTON_A_LIGHT,        9);
		setNote(SWITCH_NOTE_A_SHARP_PARAM,  LIGHT_KEY_BUTTON_A_SHARP_LIGHT, 10);
		setNote(SWITCH_NOTE_B_PARAM,        LIGHT_KEY_BUTTON_B_LIGHT,       11);

		return mask;
	}

	std::unordered_map<quantize::KeyMask, std::vector<double>> cachedTables;

	const std::vector<double>& getCachedTable(quantize::KeyMask mask) {
		auto it = cachedTables.find(mask);
		if (it != cachedTables.end()) return it->second;

		std::vector<double> table(TABLE_SIZE);  // 20000 entries from -10V to +10V
		auto allowed = quantize::allowedDecimalsFromMask(mask);

		for (int i = 0; i < TABLE_SIZE; ++i) {
			double dummy;
			double input = (RANGE_MIN + i) / static_cast<double>(RESOLUTION);  // Convert to volts
			table[i] = quantize::roundToNearestAllowedDecimal(input, allowed.data(), allowed.size(), dummy);
		}

		cachedTables[mask] = std::move(table);
		return cachedTables[mask];
	}

	double quantizeFast(double input, quantize::KeyMask mask) {
		if (mask == 0) return input; // fail-safe

		int index = clamp(int(input * RESOLUTION) - RANGE_MIN, 0, TABLE_SIZE - 1);
		return getCachedTable(mask)[index];
	}

	void process(const ProcessArgs &args) override
	{
		quantize::KeyMask mask = handleKeyButtons();

		double transposeVal = params[KNOB_TRANSPOSE_PARAM].getValue();
		double nudgeVal = params[KNOB_NUDGE_PARAM].getValue();

		displayR0on = 0;
		displayR1on = 0;
		displayR2on = 0;

		if (inputs[IN_CV_R0_INPUT].isConnected())
		{ // handle row 1
			displayR0on = 1;

			double r0Input = inputs[IN_CV_R0_INPUT].getVoltage();
			double r0AttenuvertValue = params[KNOB_ATTENUVERT_R0_PARAM].getValue();
			double r0AttenuvertedVoltage = (r0Input * r0AttenuvertValue) + nudgeVal;
			if (r0AttenuvertedVoltage > 10)
			{
				r0AttenuvertedVoltage = 10;
			}
			if (r0AttenuvertedVoltage < -10)
			{
				r0AttenuvertedVoltage = -10;
			}
			if (mask != 0) {
				roundedVoltageR0 = quantizeFast(r0AttenuvertedVoltage, mask) + (transposeVal * 1 / 12);
			}
			outputs[OUT_CV_R0_OUTPUT].setVoltage(roundedVoltageR0);
		}
		else
		{
			outputs[OUT_CV_R0_OUTPUT].setVoltage(0);
		}

		if (inputs[IN_CV_R1_INPUT].isConnected())
		{ // handle row 1
			displayR1on = 1;

			double r1Input = inputs[IN_CV_R1_INPUT].getVoltage();
			double r1AttenuvertValue = params[KNOB_ATTENUVERT_R1_PARAM].getValue();
			double r1AttenuvertedVoltage = (r1Input * r1AttenuvertValue) + nudgeVal;
			if (r1AttenuvertedVoltage > 10)
			{
				r1AttenuvertedVoltage = 10;
			}
			if (r1AttenuvertedVoltage < -10)
			{
				r1AttenuvertedVoltage = -10;
			}
			if (mask != 0) {
				roundedVoltageR1 = quantizeFast(r1AttenuvertedVoltage, mask) + (transposeVal * 1 / 12);
			}
			outputs[OUT_CV_R1_OUTPUT].setVoltage(roundedVoltageR1);
		}
		else
		{
			outputs[OUT_CV_R1_OUTPUT].setVoltage(0);
		}

		if (inputs[IN_CV_R2_INPUT].isConnected())
		{ // handle row 1
			displayR2on = 1;

			double r2Input = inputs[IN_CV_R2_INPUT].getVoltage();
			double r2AttenuvertValue = params[KNOB_ATTENUVERT_R2_PARAM].getValue();
			double r2AttenuvertedVoltage = (r2Input * r2AttenuvertValue) + nudgeVal;
			if (r2AttenuvertedVoltage > 10)
			{
				r2AttenuvertedVoltage = 10;
			}
			if (r2AttenuvertedVoltage < -10)
			{
				r2AttenuvertedVoltage = -10;
			}
			if (mask != 0) {
				roundedVoltageR2 = quantizeFast(r2AttenuvertedVoltage, mask)  + (transposeVal * 1 / 12);
			}
			outputs[OUT_CV_R2_OUTPUT].setVoltage(roundedVoltageR2);
		}
		else
		{
			outputs[OUT_CV_R2_OUTPUT].setVoltage(0);
		}
	}
};

struct QuantifyWidget : ModuleWidget
{
	QuantifyWidget(Quantify *module)
	{
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/panels/light/Quantify.svg"),asset::plugin(pluginInstance, "res/panels/dark/Quantify.svg")));

		addChild(createWidget<ThemedScrew>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ThemedScrew>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ThemedScrew>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ThemedScrew>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RedKnob>(mm2px(Vec(22.852, 39.147)), module, Quantify::KNOB_ATTENUVERT_R0_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(22.852, 69.329)), module, Quantify::KNOB_ATTENUVERT_R1_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(22.852, 99.127)), module, Quantify::KNOB_ATTENUVERT_R2_PARAM));

		addParam(createParamCentered<SteppedRedKnob>(mm2px(Vec(80.15, 16.145)), module, Quantify::KNOB_TRANSPOSE_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(60.841, 16.145)), module, Quantify::KNOB_NUDGE_PARAM));

		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(44.452, 39.147)), module, Quantify::SWITCH_NOTE_B_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(35.704, 44.146)), module, Quantify::SWITCH_NOTE_A_SHARP_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(44.452, 49.144)), module, Quantify::SWITCH_NOTE_A_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(35.704, 54.142)), module, Quantify::SWITCH_NOTE_G_SHARP_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(44.452, 59.141)), module, Quantify::SWITCH_NOTE_G_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(35.704, 64.139)), module, Quantify::SWITCH_NOTE_F_SHARP_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(44.452, 69.137)), module, Quantify::SWITCH_NOTE_F_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(44.452, 79.134)), module, Quantify::SWITCH_NOTE_E_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(35.704, 84.132)), module, Quantify::SWITCH_NOTE_D_SHARP_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(44.452, 89.131)), module, Quantify::SWITCH_NOTE_D_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(35.704, 94.129)), module, Quantify::SWITCH_NOTE_C_SHARP_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(44.452, 99.127)), module, Quantify::SWITCH_NOTE_C_PARAM));

		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(44.452, 39.147)), module, Quantify::LIGHT_KEY_BUTTON_B_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(35.704, 44.146)), module, Quantify::LIGHT_KEY_BUTTON_A_SHARP_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(44.452, 49.144)), module, Quantify::LIGHT_KEY_BUTTON_A_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(35.704, 54.142)), module, Quantify::LIGHT_KEY_BUTTON_G_SHARP_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(44.452, 59.141)), module, Quantify::LIGHT_KEY_BUTTON_G_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(35.704, 64.139)), module, Quantify::LIGHT_KEY_BUTTON_F_SHARP_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(44.452, 69.137)), module, Quantify::LIGHT_KEY_BUTTON_F_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(44.452, 79.134)), module, Quantify::LIGHT_KEY_BUTTON_E_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(35.704, 84.132)), module, Quantify::LIGHT_KEY_BUTTON_D_SHARP_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(44.452, 89.131)), module, Quantify::LIGHT_KEY_BUTTON_D_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(35.704, 94.129)), module, Quantify::LIGHT_KEY_BUTTON_C_SHARP_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(44.452, 99.127)), module, Quantify::LIGHT_KEY_BUTTON_C_LIGHT));

		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(11.412, 39.147)), module, Quantify::IN_CV_R0_INPUT));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(11.412, 69.329)), module, Quantify::IN_CV_R1_INPUT));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(11.412, 99.127)), module, Quantify::IN_CV_R2_INPUT));

		addOutput(createOutputCentered<ThemedPJ301MPort>(mm2px(Vec(99.541, 39.147)), module, Quantify::OUT_CV_R0_OUTPUT));
		addOutput(createOutputCentered<ThemedPJ301MPort>(mm2px(Vec(99.541, 69.329)), module, Quantify::OUT_CV_R1_OUTPUT));
		addOutput(createOutputCentered<ThemedPJ301MPort>(mm2px(Vec(99.541, 99.127)), module, Quantify::OUT_CV_R2_OUTPUT));

		if (module)
		{
			KeyboardDisplay *keyboardDisplayR0 = new KeyboardDisplay();
			keyboardDisplayR0->box.pos = mm2px(Vec(56.9, 34.16));
			keyboardDisplayR0->mappedVoltage = &module->roundedVoltageR0;
			keyboardDisplayR0->on = &module->displayR0on;
			addChild(keyboardDisplayR0);

			KeyboardDisplay *keyboardDisplayR1 = new KeyboardDisplay();
			keyboardDisplayR1->box.pos = mm2px(Vec(56.9, 64.05));
			keyboardDisplayR1->mappedVoltage = &module->roundedVoltageR1;
			keyboardDisplayR1->on = &module->displayR1on;
			addChild(keyboardDisplayR1);

			KeyboardDisplay *keyboardDisplayR2 = new KeyboardDisplay();
			keyboardDisplayR2->box.pos = mm2px(Vec(56.9, 93.85));
			keyboardDisplayR2->mappedVoltage = &module->roundedVoltageR2;
			keyboardDisplayR2->on = &module->displayR2on;
			addChild(keyboardDisplayR2);
		}
	}
};

Model *modelQuantify = createModel<Quantify, QuantifyWidget>("Quantify");