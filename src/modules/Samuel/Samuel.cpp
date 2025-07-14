#include "DanielDavies.hpp"
#include "SamuelSequenceGenerator.hpp"
#include "widgets/Knobs.hpp"
#include "widgets/TextInputDisplay.hpp"
#include "widgets/LengthValuesDisplay.hpp"
#include "utilities/IgnoreClockAfterResetTimer.hpp"

struct Samuel : Module
{
	enum ParamId
	{
		KNOB_DOT_LENGTH_PARAM,
		KNOB_DASH_LENGTH_PARAM,
		KNOB_NEW_LETTER_LENGTH_PARAM,
		KNOB_NEW_WORD_LENGTH_PARAM,
		PARAMS_LEN
	};
	enum InputId
	{
		INPUT_CLOCK_IN_INPUT,
		INPUT_RESET_INPUT,
		INPUTS_LEN
	};
	enum OutputId
	{
		OUTPUT_GATE_OUT_OUTPUT,
		OUT_END_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId
	{
		LIGHTS_LEN
	};

	Samuel()
	{
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(KNOB_DOT_LENGTH_PARAM, 0.f, 9.f, 1.f, "Dot Length");
		configParam(KNOB_DASH_LENGTH_PARAM, 0.f, 9.f, 3.f, "Dash Length");
		configParam(KNOB_NEW_LETTER_LENGTH_PARAM, 0.f, 9.f, 3.f, "New Letter Length");
		configParam(KNOB_NEW_WORD_LENGTH_PARAM, 0.f, 9.f, 7.f, "New Word Length");

		configInput(INPUT_CLOCK_IN_INPUT, "Clock");
		configInput(INPUT_RESET_INPUT, "Reset");

		configOutput(OUTPUT_GATE_OUT_OUTPUT, "Gate");
		configOutput(OUT_END_OUTPUT, "End");
	}

	IgnoreClockAfterResetTimer ignoreClockAfterResetTimer;
	float lastclockVoltage = 0.0f;
	float lastResetInput = 0.0f;

	std::string message = "";
	std::string lastMessage;

	char screenDotLength = '0';
	char screenDashLength = '0';
	char screenNewLetterLength = '0';
	char screenNewWordLength = '0';
	int step = 0;

	dsp::PulseGenerator endGatePulse;

	SequenceGenerator sequenceGenerator;

	void process(const ProcessArgs &args) override
	{
		sequenceGenerator.dotLength = (int)params[KNOB_DOT_LENGTH_PARAM].getValue();
		sequenceGenerator.dashLength = (int)params[KNOB_DASH_LENGTH_PARAM].getValue();
		sequenceGenerator.newLetterLength = (int)params[KNOB_NEW_LETTER_LENGTH_PARAM].getValue();
		sequenceGenerator.newWordLength = (int)params[KNOB_NEW_WORD_LENGTH_PARAM].getValue();

		screenDotLength = '0' + sequenceGenerator.dotLength;
		screenDashLength = '0' + sequenceGenerator.dashLength;
		screenNewLetterLength = '0' + sequenceGenerator.newLetterLength;
		screenNewWordLength = '0' + sequenceGenerator.newWordLength;

		ignoreClockAfterResetTimer.process(1.0 / args.sampleRate);

		float resetInput = inputs[INPUT_RESET_INPUT].getVoltage();
		if (lastResetInput == 0 && resetInput != 0)
		{ // reset triggered
			ignoreClockAfterResetTimer.resetTriggered();
			step = 0;
		}

		sequenceGenerator.generateSequence(message); // TODO: possible efficiency improvement: calling per letter rather than the whole sequence each time
		if ((int)sequenceGenerator.sequence.size() < 1)
		{
			outputs[OUTPUT_GATE_OUT_OUTPUT].setVoltage(0);
			return;
		}
		const float clockInput = inputs[INPUT_CLOCK_IN_INPUT].getVoltage();
		if (step > (int)sequenceGenerator.sequence.size())
		{
			step = 0;
		}
		if (lastclockVoltage == 0 && clockInput != 0 && !ignoreClockAfterResetTimer.shouldIgnore)
		{ // clock detected
			if (step == 0)
			{
				endGatePulse.trigger(1e-3f);
			}
			outputs[OUTPUT_GATE_OUT_OUTPUT].setVoltage(sequenceGenerator.sequence[step] ? 10.0f : 0);
			step++;
		}

		const bool shouldPulseEnd = endGatePulse.process(1.0 / args.sampleRate);
		outputs[OUT_END_OUTPUT].setVoltage(shouldPulseEnd ? 10.0 : 0.0);

		lastclockVoltage = clockInput;
		lastMessage = message;
		lastResetInput = resetInput;
	}

	json_t *dataToJson() override
	{
		json_t *rootJ = json_object();
		json_object_set_new(rootJ, "samuelText", json_string(message.c_str()));
		return rootJ;
	}

	void dataFromJson(json_t *rootJ) override
	{
		json_t *messageJ = json_object_get(rootJ, "samuelText");
		if (messageJ)
		{
			message = json_string_value(messageJ);
		}
	}
};

struct SamuelWidget : ModuleWidget
{
	SamuelWidget(Samuel *module)
	{
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/Samuel.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<SteppedRedKnob>(mm2px(Vec(9.956, 94.672)), module, Samuel::KNOB_DOT_LENGTH_PARAM));
		addParam(createParamCentered<SteppedRedKnob>(mm2px(Vec(27.942, 94.672)), module, Samuel::KNOB_DASH_LENGTH_PARAM));
		addParam(createParamCentered<SteppedRedKnob>(mm2px(Vec(45.929, 94.672)), module, Samuel::KNOB_NEW_LETTER_LENGTH_PARAM));
		addParam(createParamCentered<SteppedRedKnob>(mm2px(Vec(63.915, 94.672)), module, Samuel::KNOB_NEW_WORD_LENGTH_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(63.915, 16.245)), module, Samuel::INPUT_CLOCK_IN_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(81.901, 16.245)), module, Samuel::INPUT_RESET_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(88.935, 88.853)), module, Samuel::OUTPUT_GATE_OUT_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(88.935, 99.276)), module, Samuel::OUT_END_OUTPUT));

		if (module)
		{
			TextInputDisplay *textInputDisplay = createWidget<TextInputDisplay>(mm2px(Vec(5.759, 25.0)));
			textInputDisplay->initialize();
			textInputDisplay->message = &module->message;
			addChild(textInputDisplay);

			LengthValuesDisplay *lengthValuesDisplay = createWidget<LengthValuesDisplay>(mm2px(Vec(5.759, 105.28)));
			lengthValuesDisplay->initialize();
			lengthValuesDisplay->val0 = &module->screenDotLength;
			lengthValuesDisplay->val1 = &module->screenDashLength;
			lengthValuesDisplay->val2 = &module->screenNewLetterLength;
			lengthValuesDisplay->val3 = &module->screenNewWordLength;
			addChild(lengthValuesDisplay);
		}
	}
};

Model *modelSamuel = createModel<Samuel, SamuelWidget>("Samuel");