#include "DanielDavies.hpp"
#include <functional>
#include "widgets/Knobs.hpp"
#include "widgets/Buttons.hpp"
#include "widgets/KeyboardDisplay.hpp"

using namespace rack;

struct Quantify : Module
{

	double keyboardDisplayR0KeyOnValue = 0;
	double keyboardDisplayR1KeyOnValue = 0;
	double keyboardDisplayR2KeyOnValue = 0;

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

	std::vector<double> handleKeyButtons()
	{
		// 0 = c4
		// note interval = 1v/12
		// c = 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
		// c# = ...+ 1/12
		// d = ...+ 2/12
		// etc
		std::vector<double> res;
		if (params[SWITCH_NOTE_C_PARAM].getValue() == 1)
		{
			res.push_back(KEY_ON_C);
			lights[LIGHT_KEY_BUTTON_C_LIGHT].setBrightness(0.5);
		}
		else
		{
			lights[LIGHT_KEY_BUTTON_C_LIGHT].setBrightness(0);
		}
		if (params[SWITCH_NOTE_C_SHARP_PARAM].getValue() == 1)
		{
			res.push_back(KEY_ON_C_SHARP);
			lights[LIGHT_KEY_BUTTON_C_SHARP_LIGHT].setBrightness(0.5);
		}
		else
		{
			lights[LIGHT_KEY_BUTTON_C_SHARP_LIGHT].setBrightness(0);
		}
		if (params[SWITCH_NOTE_D_PARAM].getValue() == 1)
		{
			res.push_back(KEY_ON_D);
			lights[LIGHT_KEY_BUTTON_D_LIGHT].setBrightness(0.5);
		}
		else
		{
			lights[LIGHT_KEY_BUTTON_D_LIGHT].setBrightness(0);
		}
		if (params[SWITCH_NOTE_D_SHARP_PARAM].getValue() == 1)
		{
			res.push_back(KEY_ON_D_SHARP);
			lights[LIGHT_KEY_BUTTON_D_SHARP_LIGHT].setBrightness(0.5);
		}
		else
		{
			lights[LIGHT_KEY_BUTTON_D_SHARP_LIGHT].setBrightness(0);
		}
		if (params[SWITCH_NOTE_E_PARAM].getValue() == 1)
		{
			res.push_back(KEY_ON_E);
			lights[LIGHT_KEY_BUTTON_E_LIGHT].setBrightness(0.5);
		}
		else
		{
			lights[LIGHT_KEY_BUTTON_E_LIGHT].setBrightness(0);
		}
		if (params[SWITCH_NOTE_F_PARAM].getValue() == 1)
		{
			res.push_back(KEY_ON_F);
			lights[LIGHT_KEY_BUTTON_F_LIGHT].setBrightness(0.5);
		}
		else
		{
			lights[LIGHT_KEY_BUTTON_F_LIGHT].setBrightness(0);
		}
		if (params[SWITCH_NOTE_F_SHARP_PARAM].getValue() == 1)
		{
			res.push_back(KEY_ON_F_SHARP);
			lights[LIGHT_KEY_BUTTON_F_SHARP_LIGHT].setBrightness(0.5);
		}
		else
		{
			lights[LIGHT_KEY_BUTTON_F_SHARP_LIGHT].setBrightness(0);
		}
		if (params[SWITCH_NOTE_G_PARAM].getValue() == 1)
		{
			res.push_back(KEY_ON_G);
			lights[LIGHT_KEY_BUTTON_G_LIGHT].setBrightness(0.5);
		}
		else
		{
			lights[LIGHT_KEY_BUTTON_G_LIGHT].setBrightness(0);
		}
		if (params[SWITCH_NOTE_G_SHARP_PARAM].getValue() == 1)
		{
			res.push_back(KEY_ON_G_SHARP);
			lights[LIGHT_KEY_BUTTON_G_SHARP_LIGHT].setBrightness(0.5);
		}
		else
		{
			lights[LIGHT_KEY_BUTTON_G_SHARP_LIGHT].setBrightness(0);
		}
		if (params[SWITCH_NOTE_A_PARAM].getValue() == 1)
		{
			res.push_back(KEY_ON_A);
			lights[LIGHT_KEY_BUTTON_A_LIGHT].setBrightness(0.5);
		}
		else
		{
			lights[LIGHT_KEY_BUTTON_A_LIGHT].setBrightness(0);
		}
		if (params[SWITCH_NOTE_A_SHARP_PARAM].getValue() == 1)
		{
			res.push_back(KEY_ON_A_SHARP);
			lights[LIGHT_KEY_BUTTON_A_SHARP_LIGHT].setBrightness(0.5);
		}
		else
		{
			lights[LIGHT_KEY_BUTTON_A_SHARP_LIGHT].setBrightness(0);
		}
		if (params[SWITCH_NOTE_B_PARAM].getValue() == 1)
		{
			res.push_back(KEY_ON_B);
			lights[LIGHT_KEY_BUTTON_B_LIGHT].setBrightness(0.5);
		}
		else
		{
			lights[LIGHT_KEY_BUTTON_B_LIGHT].setBrightness(0);
		}
		return res;
	}

	double roundToNearestAllowedDecimal(
		double input,
		double allowedDecimals[],
		int numAllowedDecimals,
		double &keyOnValue)
	{
		// See:
		// https://stackoverflow.com/questions/70825012/function-to-round-a-double-to-nearest-double-with-specific-allowed-decimals/70825614#70825614
		double inputFractional = input - floor(input);
		double result = input;
		double minDiff = 1;
		int keyOnIndex = -1;
		for (int i = 0; i < numAllowedDecimals; ++i)
		{
			if (fabs(inputFractional - allowedDecimals[i]) < minDiff)
			{
				result = floor(input) + allowedDecimals[i];
				keyOnIndex++;
			}
			else if (fabs(inputFractional + 1 - allowedDecimals[i]) < minDiff)
			{
				result = floor(input) - 1 + allowedDecimals[i];
				keyOnIndex++;
			}

			minDiff = fabs(input - result);
		}
		if (keyOnIndex >= 0)
		{
			keyOnValue = allowedDecimals[keyOnIndex];
		}
		return result;
	}

	void process(const ProcessArgs &args) override
	{
		std::vector<double> allowedDecimalValues = handleKeyButtons();

		double transposeVal = params[KNOB_TRANSPOSE_PARAM].getValue();
		double nudgeVal = params[KNOB_NUDGE_PARAM].getValue();

		if (inputs[IN_CV_R0_INPUT].isConnected())
		{ // handle row 1
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
			double roundedVoltageR0 = 0;
			double keyOnValue = 0;
			if (allowedDecimalValues.size() != 0)
			{
				roundedVoltageR0 = roundToNearestAllowedDecimal(
					r0AttenuvertedVoltage,
					allowedDecimalValues.data(),
					allowedDecimalValues.size(),
					keyOnValue);
			}
			keyboardDisplayR0KeyOnValue = keyOnValue;
			outputs[OUT_CV_R0_OUTPUT].setVoltage(roundedVoltageR0 + (transposeVal * 1 / 12));
		}
		else
		{
			outputs[OUT_CV_R0_OUTPUT].setVoltage(0);
			keyboardDisplayR0KeyOnValue = -1; // set to minus one so that no keys light up
		}

		if (inputs[IN_CV_R1_INPUT].isConnected())
		{ // handle row 1
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
			double roundedVoltageR1 = 0;
			double keyOnValue = 0;
			if (allowedDecimalValues.size() != 0)
			{
				roundedVoltageR1 = roundToNearestAllowedDecimal(
					r1AttenuvertedVoltage,
					allowedDecimalValues.data(),
					allowedDecimalValues.size(),
					keyOnValue);
			}
			keyboardDisplayR1KeyOnValue = keyOnValue;
			outputs[OUT_CV_R1_OUTPUT].setVoltage(roundedVoltageR1 + (transposeVal * 1 / 12));
		}
		else
		{
			outputs[OUT_CV_R1_OUTPUT].setVoltage(0);
			keyboardDisplayR1KeyOnValue = -1; // set to minus one so that no keys light up
		}

		if (inputs[IN_CV_R2_INPUT].isConnected())
		{ // handle row 1
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
			double roundedVoltageR2 = 0;
			double keyOnValue = 0;
			if (allowedDecimalValues.size() != 0)
			{
				roundedVoltageR2 = roundToNearestAllowedDecimal(
					r2AttenuvertedVoltage,
					allowedDecimalValues.data(),
					allowedDecimalValues.size(),
					keyOnValue);
			}
			keyboardDisplayR2KeyOnValue = keyOnValue;
			outputs[OUT_CV_R2_OUTPUT].setVoltage(roundedVoltageR2 + (transposeVal * 1 / 12));
		}
		else
		{
			outputs[OUT_CV_R2_OUTPUT].setVoltage(0);
			keyboardDisplayR2KeyOnValue = -1; // set to minus one so that no keys light up
		}
	}
};

struct QuantifyWidget : ModuleWidget
{
	QuantifyWidget(Quantify *module)
	{
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/Quantify.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

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

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(11.412, 39.147)), module, Quantify::IN_CV_R0_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(11.412, 69.329)), module, Quantify::IN_CV_R1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(11.412, 99.127)), module, Quantify::IN_CV_R2_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(99.541, 39.147)), module, Quantify::OUT_CV_R0_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(99.541, 69.329)), module, Quantify::OUT_CV_R1_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(99.541, 99.127)), module, Quantify::OUT_CV_R2_OUTPUT));

		if (module)
		{
			KeyboardDisplay *keyboardDisplayR0 = new KeyboardDisplay();
			keyboardDisplayR0->box.pos = mm2px(Vec(56.9, 34.16));
			keyboardDisplayR0->keyOnValue = &module->keyboardDisplayR0KeyOnValue;
			addChild(keyboardDisplayR0);

			KeyboardDisplay *keyboardDisplayR1 = new KeyboardDisplay();
			keyboardDisplayR1->box.pos = mm2px(Vec(56.9, 64.05));
			keyboardDisplayR1->keyOnValue = &module->keyboardDisplayR1KeyOnValue;
			addChild(keyboardDisplayR1);

			KeyboardDisplay *keyboardDisplayR2 = new KeyboardDisplay();
			keyboardDisplayR2->box.pos = mm2px(Vec(56.9, 93.85));
			keyboardDisplayR2->keyOnValue = &module->keyboardDisplayR2KeyOnValue;
			addChild(keyboardDisplayR2);
		}
	}
};

Model *modelQuantify = createModel<Quantify, QuantifyWidget>("Quantify");