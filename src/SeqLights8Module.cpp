#include "plugin.hpp"


struct SeqLights8Module : Module {
	// https://coolors.co/ed6a5a-f4f1bb-9bc1bc-5d576b-e6ebe0
	enum ParamIds {
		KNOB_STEP_R0_C0_PARAM,
		KNOB_STEP_R0_C1_PARAM,
		KNOB_STEP_R0_C2_PARAM,
		KNOB_STEP_R0_C3_PARAM,
		KNOB_STEP_R0_C4_PARAM,
		KNOB_STEP_R0_C5_PARAM,
		KNOB_STEP_R0_C6_PARAM,
		KNOB_STEP_R0_C7_PARAM,
		KNOB_STEP_R1_C0_PARAM,
		KNOB_STEP_R1_C1_PARAM,
		KNOB_STEP_R1_C2_PARAM,
		KNOB_STEP_R1_C3_PARAM,
		KNOB_STEP_R1_C4_PARAM,
		KNOB_STEP_R1_C5_PARAM,
		KNOB_STEP_R1_C6_PARAM,
		KNOB_STEP_R1_C7_PARAM,
		KNOB_STEP_R2_C0_PARAM,
		KNOB_STEP_R2_C1_PARAM,
		KNOB_STEP_R2_C2_PARAM,
		KNOB_STEP_R2_C3_PARAM,
		KNOB_STEP_R2_C4_PARAM,
		KNOB_STEP_R2_C5_PARAM,
		KNOB_STEP_R2_C6_PARAM,
		KNOB_STEP_R2_C7_PARAM,
		SWITCH_GATE_R0_C0_PARAM,
		SWITCH_GATE_R0_C1_PARAM,
		SWITCH_GATE_R0_C2_PARAM,
		SWITCH_GATE_R0_C3_PARAM,
		SWITCH_GATE_R0_C4_PARAM,
		SWITCH_GATE_R0_C5_PARAM,
		SWITCH_GATE_R0_C6_PARAM,
		SWITCH_GATE_R0_C7_PARAM,
		SWITCH_GATE_R1_C0_PARAM,
		SWITCH_GATE_R1_C1_PARAM,
		SWITCH_GATE_R1_C2_PARAM,
		SWITCH_GATE_R1_C3_PARAM,
		SWITCH_GATE_R1_C4_PARAM,
		SWITCH_GATE_R1_C5_PARAM,
		SWITCH_GATE_R1_C6_PARAM,
		SWITCH_GATE_R1_C7_PARAM,
		SWITCH_GATE_R2_C0_PARAM,
		SWITCH_GATE_R2_C1_PARAM,
		SWITCH_GATE_R2_C2_PARAM,
		SWITCH_GATE_R2_C3_PARAM,
		SWITCH_GATE_R2_C4_PARAM,
		SWITCH_GATE_R2_C5_PARAM,
		SWITCH_GATE_R2_C6_PARAM,
		SWITCH_GATE_R2_C7_PARAM,
		KNOB_TIME_DIVIDE_R0_PARAM,
		KNOB_TIME_DIVIDE_R1_PARAM,
		KNOB_TIME_DIVIDE_R2_PARAM,
		KNOB_STEP_COUNT_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		IN_CLOCK_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		OUT_CV_R0_OUTPUT,
		OUT_GATE_R0_OUTPUT,
		OUT_CV_R1_OUTPUT,
		OUT_GATE_R1_OUTPUT,
		OUT_CV_R2_OUTPUT,
		OUT_GATE_R2_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		LIGHT_R0_C0_LIGHT,
		LIGHT_R0_C1_LIGHT,
		LIGHT_R0_C2_LIGHT,
		LIGHT_R0_C3_LIGHT,
		LIGHT_R0_C4_LIGHT,
		LIGHT_R0_C5_LIGHT,
		LIGHT_R0_C6_LIGHT,
		LIGHT_R0_C7_LIGHT,
		LIGHT_R1_C0_LIGHT,
		LIGHT_R1_C1_LIGHT,
		LIGHT_R1_C2_LIGHT,
		LIGHT_R1_C3_LIGHT,
		LIGHT_R1_C4_LIGHT,
		LIGHT_R1_C5_LIGHT,
		LIGHT_R1_C6_LIGHT,
		LIGHT_R1_C7_LIGHT,
		LIGHT_R2_C0_LIGHT,
		LIGHT_R2_C1_LIGHT,
		LIGHT_R2_C2_LIGHT,
		LIGHT_R2_C3_LIGHT,
		LIGHT_R2_C4_LIGHT,
		LIGHT_R2_C5_LIGHT,
		LIGHT_R2_C6_LIGHT,
		LIGHT_R2_C7_LIGHT,
		NUM_LIGHTS
	};

	SeqLights8Module() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		configParam(KNOB_STEP_R0_C0_PARAM, 0.f, 10.f, 0.f, "");
		configParam(KNOB_STEP_R0_C1_PARAM, 0.f, 10.f, 0.f, "");
		configParam(KNOB_STEP_R0_C2_PARAM, 0.f, 10.f, 0.f, "");
		configParam(KNOB_STEP_R0_C3_PARAM, 0.f, 10.f, 0.f, "");
		configParam(KNOB_STEP_R0_C4_PARAM, 0.f, 10.f, 0.f, "");
		configParam(KNOB_STEP_R0_C5_PARAM, 0.f, 10.f, 0.f, "");
		configParam(KNOB_STEP_R0_C6_PARAM, 0.f, 10.f, 0.f, "");
		configParam(KNOB_STEP_R0_C7_PARAM, 0.f, 10.f, 0.f, "");
		configParam(SWITCH_GATE_R0_C0_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R0_C1_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R0_C2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R0_C3_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R0_C4_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R0_C5_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R0_C6_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R0_C7_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_STEP_R1_C0_PARAM, 0.f, 10.f, 0.f, "");
		configParam(KNOB_STEP_R1_C1_PARAM, 0.f, 10.f, 0.f, "");
		configParam(KNOB_STEP_R1_C2_PARAM, 0.f, 10.f, 0.f, "");
		configParam(KNOB_STEP_R1_C3_PARAM, 0.f, 10.f, 0.f, "");
		configParam(KNOB_STEP_R1_C4_PARAM, 0.f, 10.f, 0.f, "");
		configParam(KNOB_STEP_R1_C5_PARAM, 0.f, 10.f, 0.f, "");
		configParam(KNOB_STEP_R1_C6_PARAM, 0.f, 10.f, 0.f, "");
		configParam(KNOB_STEP_R1_C7_PARAM, 0.f, 10.f, 0.f, "");
		configParam(SWITCH_GATE_R1_C0_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R1_C1_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R1_C2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R1_C3_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R1_C4_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R1_C5_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R1_C6_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R1_C7_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_STEP_R2_C0_PARAM, 0.f, 10.f, 0.f, "");
		configParam(KNOB_STEP_R2_C1_PARAM, 0.f, 10.f, 0.f, "");
		configParam(KNOB_STEP_R2_C2_PARAM, 0.f, 10.f, 0.f, "");
		configParam(KNOB_STEP_R2_C3_PARAM, 0.f, 10.f, 0.f, "");
		configParam(KNOB_STEP_R2_C4_PARAM, 0.f, 10.f, 0.f, "");
		configParam(KNOB_STEP_R2_C5_PARAM, 0.f, 10.f, 0.f, "");
		configParam(KNOB_STEP_R2_C6_PARAM, 0.f, 10.f, 0.f, "");
		configParam(KNOB_STEP_R2_C7_PARAM, 0.f, 10.f, 0.f, "");
		configParam(KNOB_TIME_DIVIDE_R0_PARAM, 1.f, 6.f, 1.f, "");
		configParam(KNOB_TIME_DIVIDE_R1_PARAM, 1.f, 6.f, 1.f, "");
		configParam(KNOB_TIME_DIVIDE_R2_PARAM, 1.f, 6.f, 1.f, "");
		configParam(KNOB_STEP_COUNT_PARAM, 0.f, 8.f, 8.f, "");
		configParam(SWITCH_GATE_R2_C0_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R2_C1_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R2_C2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R2_C3_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R2_C4_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R2_C5_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R2_C6_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R2_C7_PARAM, 0.f, 1.f, 0.f, "");
	}

	float lastClockInput = 0.0f;
	dsp::PulseGenerator gatePulseR0;
	dsp::PulseGenerator gatePulseR1;
	dsp::PulseGenerator gatePulseR2;

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

	int numSteps = 8;

	void nextClock() {
		gatesSinceLastStepR0++;
		gatesSinceLastStepR1++;
		gatesSinceLastStepR2++;
		if(gatesSinceLastStepR0 >= divideR0) {
			nextStepR0();
			gatesSinceLastStepR0 = 0;
			setHasPulsedThisStepForRow(0, false);
		}
		if(gatesSinceLastStepR1 >= divideR1) {
			nextStepR1();
			gatesSinceLastStepR1 = 0;
			setHasPulsedThisStepForRow(1, false);
		}
		if(gatesSinceLastStepR2 >= divideR2) {
			nextStepR2();
			gatesSinceLastStepR2 = 0;
			setHasPulsedThisStepForRow(2, false);
		}
	}

	void nextStepR0() {
		currentStepR0 += 1;
		if (currentStepR0 >= numSteps) {
			currentStepR0 = 0;
		}
	}

	void nextStepR1() {
		currentStepR1 += 1;
		if (currentStepR1 >= numSteps) {
			currentStepR1 = 0;
		}
	}

	void nextStepR2() {
		currentStepR2 += 1;
		if (currentStepR2 >= numSteps) {
			currentStepR2 = 0;
		}
	}

	int getCurrentStepForRow(short row) {
		short res = 0;
		switch (row)
		{
			case 0:
				res = currentStepR0;
				break;
			case 1:
				res = currentStepR1;
				break;
			case 2:
				res = currentStepR2;
				break;
		}
		return res;
	}

	bool getHasPulsedThisStepForRow(short row) {
		bool res = false;
		switch (row)
		{
			case 0:
				res = hasPulsedThisStepR0;
				break;
			case 1:
				res = hasPulsedThisStepR1;
				break;
			case 2:
				res = hasPulsedThisStepR2;
				break;
		}
		return res;
	}

	void setHasPulsedThisStepForRow(short row, bool val) {
		switch (row)
		{
			case 0:
				hasPulsedThisStepR0 = val;
				break;
			case 1:
				hasPulsedThisStepR1 = val;
				break;
			case 2:
				hasPulsedThisStepR2 = val;
				break;
		}
	}

	bool shouldPulseThisStep(short row) {
		return params[getButtonId(row, getCurrentStepForRow(row))].getValue() > 0.5 && getHasPulsedThisStepForRow(row) == false;
	}

	void turnOffAllLights() {
		for(int i = 0; i < NUM_LIGHTS; i++ ) {
			lights[i].setBrightness(0);
		}
	}

	short getLightId(short row, short column) {
		return column + (row*8);
	}

	short getKnobId(short row, short column) {
		return column + (row*8);
	}

	short getButtonId(short row, short column) {
		return column + (row*8) + 24;
	}


	void process(const ProcessArgs& args) override {
		float clockInput = inputs[IN_CLOCK_INPUT].getVoltage();

		numSteps = round(params[KNOB_STEP_COUNT_PARAM].getValue());

		if(numSteps == 0) {
			turnOffAllLights();
			return;
		}
		
		if (lastClockInput == 0 && clockInput != 0) {
			nextClock();
			if(shouldPulseThisStep(0)) {
				gatePulseR0.trigger(1e-3f);
				setHasPulsedThisStepForRow(0, true);
			}
			if(shouldPulseThisStep(1)) {
				gatePulseR1.trigger(1e-3f);
				setHasPulsedThisStepForRow(1, true);
			}
			if(shouldPulseThisStep(2)) {
				gatePulseR2.trigger(1e-3f);
				setHasPulsedThisStepForRow(2, true);
			}
		}

		turnOffAllLights();

		lights[getLightId(0, getCurrentStepForRow(0))].setBrightness(1.0f);
		lights[getLightId(1, getCurrentStepForRow(1))].setBrightness(1.0f);
		lights[getLightId(2, getCurrentStepForRow(2))].setBrightness(1.0f);

		bool pulseR0 = gatePulseR0.process(1.0 / args.sampleRate);
		outputs[OUT_GATE_R0_OUTPUT].setVoltage(pulseR0 ? 10.0 : 0.0);

		bool pulseR1 = gatePulseR1.process(1.0 / args.sampleRate);
		outputs[OUT_GATE_R1_OUTPUT].setVoltage(pulseR1 ? 10.0 : 0.0);

		bool pulseR2 = gatePulseR2.process(1.0 / args.sampleRate);
		outputs[OUT_GATE_R2_OUTPUT].setVoltage(pulseR2 ? 10.0 : 0.0);

		float voltageOutputR0 = 0.0f;
		voltageOutputR0 = params[getKnobId(0, getCurrentStepForRow(0))].getValue();
		float voltageOutputR1 = 0.0f;
		voltageOutputR1 = params[getKnobId(1, getCurrentStepForRow(1))].getValue();
		float voltageOutputR2 = 0.0f;
		voltageOutputR2 = params[getKnobId(2, getCurrentStepForRow(2))].getValue();

		divideR0 = round(params[KNOB_TIME_DIVIDE_R0_PARAM].getValue());
		divideR1 = round(params[KNOB_TIME_DIVIDE_R1_PARAM].getValue());
		divideR2 = round(params[KNOB_TIME_DIVIDE_R2_PARAM].getValue());

		outputs[OUT_CV_R0_OUTPUT].setVoltage(voltageOutputR0);
		outputs[OUT_CV_R1_OUTPUT].setVoltage(voltageOutputR1);
		outputs[OUT_CV_R2_OUTPUT].setVoltage(voltageOutputR2);

		lastClockInput = clockInput;
	}
};


struct SeqLights8ModuleWidget : ModuleWidget {
	SeqLights8ModuleWidget(SeqLights8Module* module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/SeqLights8Module.svg")));

		// addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		// addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		// addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		// addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		// addParam(createParamCentered<RedKnob>(mm2px(Vec(37.237, 34.294)), module, SeqLights8Module::KNOB_STEP_R0_C0_PARAM));
		// addParam(createParamCentered<RedKnob>(mm2px(Vec(61.446, 34.294)), module, SeqLights8Module::KNOB_STEP_R0_C1_PARAM));
		// addParam(createParamCentered<RedKnob>(mm2px(Vec(85.654, 34.294)), module, SeqLights8Module::KNOB_STEP_R0_C2_PARAM));
		// addParam(createParamCentered<RedKnob>(mm2px(Vec(109.863, 34.294)), module, SeqLights8Module::KNOB_STEP_R0_C3_PARAM));
		// addParam(createParamCentered<RedKnob>(mm2px(Vec(134.071, 34.294)), module, SeqLights8Module::KNOB_STEP_R0_C4_PARAM));
		// addParam(createParamCentered<RedKnob>(mm2px(Vec(158.28, 34.294)), module, SeqLights8Module::KNOB_STEP_R0_C5_PARAM));
		// addParam(createParamCentered<RedKnob>(mm2px(Vec(182.488, 34.294)), module, SeqLights8Module::KNOB_STEP_R0_C6_PARAM));
		// addParam(createParamCentered<RedKnob>(mm2px(Vec(206.696, 34.294)), module, SeqLights8Module::KNOB_STEP_R0_C7_PARAM));

		// addParam(createParamCentered<LatchingSwitch<CKD6>>(mm2px(Vec(37.237, 45.406)), module, SeqLights8Module::SWITCH_GATE_R0_C0_PARAM));
		// addParam(createParamCentered<LatchingSwitch<CKD6>>(mm2px(Vec(61.446, 45.406)), module, SeqLights8Module::SWITCH_GATE_R0_C1_PARAM));
		// addParam(createParamCentered<LatchingSwitch<CKD6>>(mm2px(Vec(85.654, 45.406)), module, SeqLights8Module::SWITCH_GATE_R0_C2_PARAM));
		// addParam(createParamCentered<LatchingSwitch<CKD6>>(mm2px(Vec(109.863, 45.406)), module, SeqLights8Module::SWITCH_GATE_R0_C3_PARAM));
		// addParam(createParamCentered<LatchingSwitch<CKD6>>(mm2px(Vec(134.071, 45.406)), module, SeqLights8Module::SWITCH_GATE_R0_C4_PARAM));
		// addParam(createParamCentered<LatchingSwitch<CKD6>>(mm2px(Vec(158.28, 45.406)), module, SeqLights8Module::SWITCH_GATE_R0_C5_PARAM));
		// addParam(createParamCentered<LatchingSwitch<CKD6>>(mm2px(Vec(182.488, 45.406)), module, SeqLights8Module::SWITCH_GATE_R0_C6_PARAM));
		// addParam(createParamCentered<LatchingSwitch<CKD6>>(mm2px(Vec(206.696, 45.406)), module, SeqLights8Module::SWITCH_GATE_R0_C7_PARAM));

		// addParam(createParamCentered<RedKnob>(mm2px(Vec(37.237, 59.694)), module, SeqLights8Module::KNOB_STEP_R1_C0_PARAM));
		// addParam(createParamCentered<RedKnob>(mm2px(Vec(61.446, 59.694)), module, SeqLights8Module::KNOB_STEP_R1_C1_PARAM));
		// addParam(createParamCentered<RedKnob>(mm2px(Vec(85.654, 59.694)), module, SeqLights8Module::KNOB_STEP_R1_C2_PARAM));
		// addParam(createParamCentered<RedKnob>(mm2px(Vec(109.863, 59.694)), module, SeqLights8Module::KNOB_STEP_R1_C3_PARAM));
		// addParam(createParamCentered<RedKnob>(mm2px(Vec(134.071, 59.694)), module, SeqLights8Module::KNOB_STEP_R1_C4_PARAM));
		// addParam(createParamCentered<RedKnob>(mm2px(Vec(158.28, 59.694)), module, SeqLights8Module::KNOB_STEP_R1_C5_PARAM));
		// addParam(createParamCentered<RedKnob>(mm2px(Vec(182.488, 59.694)), module, SeqLights8Module::KNOB_STEP_R1_C6_PARAM));
		// addParam(createParamCentered<RedKnob>(mm2px(Vec(206.696, 59.694)), module, SeqLights8Module::KNOB_STEP_R1_C7_PARAM));

		// addParam(createParamCentered<LatchingSwitch<CKD6>>(mm2px(Vec(37.237, 70.806)), module, SeqLights8Module::SWITCH_GATE_R1_C0_PARAM));
		// addParam(createParamCentered<LatchingSwitch<CKD6>>(mm2px(Vec(61.446, 70.806)), module, SeqLights8Module::SWITCH_GATE_R1_C1_PARAM));
		// addParam(createParamCentered<LatchingSwitch<CKD6>>(mm2px(Vec(85.654, 70.806)), module, SeqLights8Module::SWITCH_GATE_R1_C2_PARAM));
		// addParam(createParamCentered<LatchingSwitch<CKD6>>(mm2px(Vec(109.863, 70.806)), module, SeqLights8Module::SWITCH_GATE_R1_C3_PARAM));
		// addParam(createParamCentered<LatchingSwitch<CKD6>>(mm2px(Vec(134.071, 70.806)), module, SeqLights8Module::SWITCH_GATE_R1_C4_PARAM));
		// addParam(createParamCentered<LatchingSwitch<CKD6>>(mm2px(Vec(158.28, 70.806)), module, SeqLights8Module::SWITCH_GATE_R1_C5_PARAM));
		// addParam(createParamCentered<LatchingSwitch<CKD6>>(mm2px(Vec(182.488, 70.806)), module, SeqLights8Module::SWITCH_GATE_R1_C6_PARAM));
		// addParam(createParamCentered<LatchingSwitch<CKD6>>(mm2px(Vec(206.696, 70.806)), module, SeqLights8Module::SWITCH_GATE_R1_C7_PARAM));

		// addParam(createParamCentered<RedKnob>(mm2px(Vec(37.237, 85.094)), module, SeqLights8Module::KNOB_STEP_R2_C0_PARAM));
		// addParam(createParamCentered<RedKnob>(mm2px(Vec(61.446, 85.094)), module, SeqLights8Module::KNOB_STEP_R2_C1_PARAM));
		// addParam(createParamCentered<RedKnob>(mm2px(Vec(85.654, 85.094)), module, SeqLights8Module::KNOB_STEP_R2_C2_PARAM));
		// addParam(createParamCentered<RedKnob>(mm2px(Vec(109.863, 85.094)), module, SeqLights8Module::KNOB_STEP_R2_C3_PARAM));
		// addParam(createParamCentered<RedKnob>(mm2px(Vec(134.071, 85.094)), module, SeqLights8Module::KNOB_STEP_R2_C4_PARAM));
		// addParam(createParamCentered<RedKnob>(mm2px(Vec(158.28, 85.094)), module, SeqLights8Module::KNOB_STEP_R2_C5_PARAM));
		// addParam(createParamCentered<RedKnob>(mm2px(Vec(182.488, 85.094)), module, SeqLights8Module::KNOB_STEP_R2_C6_PARAM));
		// addParam(createParamCentered<RedKnob>(mm2px(Vec(206.696, 85.094)), module, SeqLights8Module::KNOB_STEP_R2_C7_PARAM));

		// addParam(createParamCentered<SteppedRedKnob>(mm2px(Vec(15.41, 39.85)), module, SeqLights8Module::KNOB_TIME_DIVIDE_R0_PARAM));
		// addParam(createParamCentered<SteppedRedKnob>(mm2px(Vec(15.41, 65.25)), module, SeqLights8Module::KNOB_TIME_DIVIDE_R1_PARAM));
		// addParam(createParamCentered<SteppedRedKnob>(mm2px(Vec(15.41, 90.65)), module, SeqLights8Module::KNOB_TIME_DIVIDE_R2_PARAM));
		// addParam(createParamCentered<SteppedRedKnob>(mm2px(Vec(109.863, 16.565)), module, SeqLights8Module::KNOB_STEP_COUNT_PARAM));

		// addParam(createParamCentered<LatchingSwitch<CKD6>>(mm2px(Vec(37.237, 96.206)), module, SeqLights8Module::SWITCH_GATE_R2_C0_PARAM));
		// addParam(createParamCentered<LatchingSwitch<CKD6>>(mm2px(Vec(61.446, 96.206)), module, SeqLights8Module::SWITCH_GATE_R2_C1_PARAM));
		// addParam(createParamCentered<LatchingSwitch<CKD6>>(mm2px(Vec(85.654, 96.206)), module, SeqLights8Module::SWITCH_GATE_R2_C2_PARAM));
		// addParam(createParamCentered<LatchingSwitch<CKD6>>(mm2px(Vec(109.863, 96.206)), module, SeqLights8Module::SWITCH_GATE_R2_C3_PARAM));
		// addParam(createParamCentered<LatchingSwitch<CKD6>>(mm2px(Vec(134.071, 96.206)), module, SeqLights8Module::SWITCH_GATE_R2_C4_PARAM));
		// addParam(createParamCentered<LatchingSwitch<CKD6>>(mm2px(Vec(158.28, 96.206)), module, SeqLights8Module::SWITCH_GATE_R2_C5_PARAM));
		// addParam(createParamCentered<LatchingSwitch<CKD6>>(mm2px(Vec(182.488, 96.206)), module, SeqLights8Module::SWITCH_GATE_R2_C6_PARAM));
		// addParam(createParamCentered<LatchingSwitch<CKD6>>(mm2px(Vec(206.696, 96.206)), module, SeqLights8Module::SWITCH_GATE_R2_C7_PARAM));


		// addInput(createInputCentered<PJ301MPort>(mm2px(Vec(85.654, 16.565)), module, SeqLights8Module::IN_CLOCK_INPUT));

		// addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(234.493, 34.294)), module, SeqLights8Module::OUT_CV_R0_OUTPUT));
		// addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(234.493, 45.406)), module, SeqLights8Module::OUT_GATE_R0_OUTPUT));
		// addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(234.493, 59.694)), module, SeqLights8Module::OUT_CV_R1_OUTPUT));
		// addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(234.493, 70.806)), module, SeqLights8Module::OUT_GATE_R1_OUTPUT));
		// addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(234.493, 85.094)), module, SeqLights8Module::OUT_CV_R2_OUTPUT));
		// addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(234.493, 96.206)), module, SeqLights8Module::OUT_GATE_R2_OUTPUT));

		// addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(43.644, 29.7)), module, SeqLights8Module::LIGHT_R0_C0_LIGHT));
		// addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(67.852, 29.7)), module, SeqLights8Module::LIGHT_R0_C1_LIGHT));
		// addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(92.061, 29.7)), module, SeqLights8Module::LIGHT_R0_C2_LIGHT));
		// addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(116.269, 29.7)), module, SeqLights8Module::LIGHT_R0_C3_LIGHT));
		// addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(140.477, 29.7)), module, SeqLights8Module::LIGHT_R0_C4_LIGHT));
		// addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(164.686, 29.7)), module, SeqLights8Module::LIGHT_R0_C5_LIGHT));
		// addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(188.894, 29.7)), module, SeqLights8Module::LIGHT_R0_C6_LIGHT));
		// addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(213.103, 29.7)), module, SeqLights8Module::LIGHT_R0_C7_LIGHT));
		// addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(43.644, 55.1)), module, SeqLights8Module::LIGHT_R1_C0_LIGHT));
		// addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(67.852, 55.1)), module, SeqLights8Module::LIGHT_R1_C1_LIGHT));
		// addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(92.061, 55.1)), module, SeqLights8Module::LIGHT_R1_C2_LIGHT));
		// addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(116.269, 55.1)), module, SeqLights8Module::LIGHT_R1_C3_LIGHT));
		// addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(140.477, 55.1)), module, SeqLights8Module::LIGHT_R1_C4_LIGHT));
		// addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(164.686, 55.1)), module, SeqLights8Module::LIGHT_R1_C5_LIGHT));
		// addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(188.894, 55.1)), module, SeqLights8Module::LIGHT_R1_C6_LIGHT));
		// addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(213.103, 55.1)), module, SeqLights8Module::LIGHT_R1_C7_LIGHT));
		// addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(43.644, 80.5)), module, SeqLights8Module::LIGHT_R2_C0_LIGHT));
		// addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(67.852, 80.5)), module, SeqLights8Module::LIGHT_R2_C1_LIGHT));
		// addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(92.061, 80.5)), module, SeqLights8Module::LIGHT_R2_C2_LIGHT));
		// addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(116.269, 80.5)), module, SeqLights8Module::LIGHT_R2_C3_LIGHT));
		// addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(140.477, 80.5)), module, SeqLights8Module::LIGHT_R2_C4_LIGHT));
		// addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(164.686, 80.5)), module, SeqLights8Module::LIGHT_R2_C5_LIGHT));
		// addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(188.894, 80.5)), module, SeqLights8Module::LIGHT_R2_C6_LIGHT));
		// addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(213.103, 80.5)), module, SeqLights8Module::LIGHT_R2_C7_LIGHT));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<SteppedRedKnob>(mm2px(Vec(96.113, 16.145)), module, SeqLights8Module::KNOB_STEP_COUNT_PARAM));

		addParam(createParamCentered<RedKnob>(mm2px(Vec(38.188, 33.874)), module, SeqLights8Module::KNOB_STEP_R0_C0_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(57.496, 33.874)), module, SeqLights8Module::KNOB_STEP_R0_C2_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(76.805, 33.874)), module, SeqLights8Module::KNOB_STEP_R0_C3_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(96.113, 33.874)), module, SeqLights8Module::KNOB_STEP_R0_C4_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(115.422, 33.874)), module, SeqLights8Module::KNOB_STEP_R0_C1_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(134.731, 33.874)), module, SeqLights8Module::KNOB_STEP_R0_C5_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(154.039, 33.874)), module, SeqLights8Module::KNOB_STEP_R0_C6_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(173.348, 33.874)), module, SeqLights8Module::KNOB_STEP_R0_C7_PARAM));

		addParam(createParamCentered<SteppedRedKnob>(mm2px(Vec(18.574, 39.431)), module, SeqLights8Module::KNOB_TIME_DIVIDE_R0_PARAM));

		addParam(createParamCentered<LatchingSwitch<CKD6>>(mm2px(Vec(38.188, 44.987)), module, SeqLights8Module::SWITCH_GATE_R0_C0_PARAM));
		addParam(createParamCentered<LatchingSwitch<CKD6>>(mm2px(Vec(57.496, 44.987)), module, SeqLights8Module::SWITCH_GATE_R0_C2_PARAM));
		addParam(createParamCentered<LatchingSwitch<CKD6>>(mm2px(Vec(76.805, 44.987)), module, SeqLights8Module::SWITCH_GATE_R0_C3_PARAM));
		addParam(createParamCentered<LatchingSwitch<CKD6>>(mm2px(Vec(96.113, 44.987)), module, SeqLights8Module::SWITCH_GATE_R0_C4_PARAM));
		addParam(createParamCentered<LatchingSwitch<CKD6>>(mm2px(Vec(115.422, 44.987)), module, SeqLights8Module::SWITCH_GATE_R0_C1_PARAM));
		addParam(createParamCentered<LatchingSwitch<CKD6>>(mm2px(Vec(134.731, 44.987)), module, SeqLights8Module::SWITCH_GATE_R0_C5_PARAM));
		addParam(createParamCentered<LatchingSwitch<CKD6>>(mm2px(Vec(154.039, 44.987)), module, SeqLights8Module::SWITCH_GATE_R0_C6_PARAM));
		addParam(createParamCentered<LatchingSwitch<CKD6>>(mm2px(Vec(173.348, 44.987)), module, SeqLights8Module::SWITCH_GATE_R0_C7_PARAM));

		addParam(createParamCentered<RedKnob>(mm2px(Vec(38.188, 63.772)), module, SeqLights8Module::KNOB_STEP_R1_C0_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(57.496, 63.772)), module, SeqLights8Module::KNOB_STEP_R1_C1_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(76.805, 63.772)), module, SeqLights8Module::KNOB_STEP_R1_C2_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(96.113, 63.772)), module, SeqLights8Module::KNOB_STEP_R1_C3_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(115.422, 63.772)), module, SeqLights8Module::KNOB_STEP_R1_C4_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(134.731, 63.772)), module, SeqLights8Module::KNOB_STEP_R1_C5_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(154.039, 63.772)), module, SeqLights8Module::KNOB_STEP_R1_C6_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(173.348, 63.772)), module, SeqLights8Module::KNOB_STEP_R1_C7_PARAM));

		addParam(createParamCentered<SteppedRedKnob>(mm2px(Vec(18.574, 69.329)), module, SeqLights8Module::KNOB_TIME_DIVIDE_R1_PARAM));

		addParam(createParamCentered<LatchingSwitch<CKD6>>(mm2px(Vec(38.188, 74.885)), module, SeqLights8Module::SWITCH_GATE_R1_C0_PARAM));
		addParam(createParamCentered<LatchingSwitch<CKD6>>(mm2px(Vec(57.496, 74.885)), module, SeqLights8Module::SWITCH_GATE_R1_C1_PARAM));
		addParam(createParamCentered<LatchingSwitch<CKD6>>(mm2px(Vec(76.805, 74.885)), module, SeqLights8Module::SWITCH_GATE_R1_C2_PARAM));
		addParam(createParamCentered<LatchingSwitch<CKD6>>(mm2px(Vec(96.113, 74.885)), module, SeqLights8Module::SWITCH_GATE_R1_C3_PARAM));
		addParam(createParamCentered<LatchingSwitch<CKD6>>(mm2px(Vec(115.422, 74.885)), module, SeqLights8Module::SWITCH_GATE_R1_C4_PARAM));
		addParam(createParamCentered<LatchingSwitch<CKD6>>(mm2px(Vec(134.731, 74.885)), module, SeqLights8Module::SWITCH_GATE_R1_C5_PARAM));
		addParam(createParamCentered<LatchingSwitch<CKD6>>(mm2px(Vec(154.039, 74.885)), module, SeqLights8Module::SWITCH_GATE_R1_C6_PARAM));
		addParam(createParamCentered<LatchingSwitch<CKD6>>(mm2px(Vec(173.348, 74.885)), module, SeqLights8Module::SWITCH_GATE_R1_C7_PARAM));

		addParam(createParamCentered<RedKnob>(mm2px(Vec(38.188, 93.67)), module, SeqLights8Module::KNOB_STEP_R2_C0_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(57.496, 93.67)), module, SeqLights8Module::KNOB_STEP_R2_C1_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(76.805, 93.67)), module, SeqLights8Module::KNOB_STEP_R2_C2_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(96.113, 93.67)), module, SeqLights8Module::KNOB_STEP_R2_C3_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(115.422, 93.67)), module, SeqLights8Module::KNOB_STEP_R2_C4_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(134.731, 93.67)), module, SeqLights8Module::KNOB_STEP_R2_C5_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(154.039, 93.67)), module, SeqLights8Module::KNOB_STEP_R2_C6_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(173.348, 93.67)), module, SeqLights8Module::KNOB_STEP_R2_C7_PARAM));

		addParam(createParamCentered<SteppedRedKnob>(mm2px(Vec(18.574, 99.226)), module, SeqLights8Module::KNOB_TIME_DIVIDE_R2_PARAM));

		addParam(createParamCentered<LatchingSwitch<CKD6>>(mm2px(Vec(38.188, 104.783)), module, SeqLights8Module::SWITCH_GATE_R2_C0_PARAM));
		addParam(createParamCentered<LatchingSwitch<CKD6>>(mm2px(Vec(57.496, 104.783)), module, SeqLights8Module::SWITCH_GATE_R2_C1_PARAM));
		addParam(createParamCentered<LatchingSwitch<CKD6>>(mm2px(Vec(76.805, 104.783)), module, SeqLights8Module::SWITCH_GATE_R2_C2_PARAM));
		addParam(createParamCentered<LatchingSwitch<CKD6>>(mm2px(Vec(96.113, 104.783)), module, SeqLights8Module::SWITCH_GATE_R2_C3_PARAM));
		addParam(createParamCentered<LatchingSwitch<CKD6>>(mm2px(Vec(115.422, 104.783)), module, SeqLights8Module::SWITCH_GATE_R2_C4_PARAM));
		addParam(createParamCentered<LatchingSwitch<CKD6>>(mm2px(Vec(134.731, 104.783)), module, SeqLights8Module::SWITCH_GATE_R2_C5_PARAM));
		addParam(createParamCentered<LatchingSwitch<CKD6>>(mm2px(Vec(154.039, 104.783)), module, SeqLights8Module::SWITCH_GATE_R2_C6_PARAM));
		addParam(createParamCentered<LatchingSwitch<CKD6>>(mm2px(Vec(173.348, 104.783)), module, SeqLights8Module::SWITCH_GATE_R2_C7_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(76.805, 16.145)), module, SeqLights8Module::IN_CLOCK_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(201.144, 33.591)), module, SeqLights8Module::OUT_CV_R0_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(201.144, 44.704)), module, SeqLights8Module::OUT_GATE_R0_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(201.144, 63.772)), module, SeqLights8Module::OUT_CV_R1_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(201.144, 74.885)), module, SeqLights8Module::OUT_GATE_R1_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(201.144, 93.67)), module, SeqLights8Module::OUT_CV_R2_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(201.144, 104.783)), module, SeqLights8Module::OUT_GATE_R2_OUTPUT));

		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(44.594, 29.28)), module, SeqLights8Module::LIGHT_R0_C0_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(63.903, 29.28)), module, SeqLights8Module::LIGHT_R0_C2_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(83.211, 29.28)), module, SeqLights8Module::LIGHT_R0_C3_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(102.52, 29.28)), module, SeqLights8Module::LIGHT_R0_C4_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(121.828, 29.28)), module, SeqLights8Module::LIGHT_R0_C1_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(141.137, 29.28)), module, SeqLights8Module::LIGHT_R0_C5_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(160.446, 29.28)), module, SeqLights8Module::LIGHT_R0_C6_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(179.754, 29.28)), module, SeqLights8Module::LIGHT_R0_C7_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(44.594, 59.178)), module, SeqLights8Module::LIGHT_R1_C0_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(63.903, 59.178)), module, SeqLights8Module::LIGHT_R1_C1_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(83.211, 59.178)), module, SeqLights8Module::LIGHT_R1_C2_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(102.52, 59.178)), module, SeqLights8Module::LIGHT_R1_C3_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(121.828, 59.178)), module, SeqLights8Module::LIGHT_R1_C4_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(141.137, 59.178)), module, SeqLights8Module::LIGHT_R1_C5_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(160.446, 59.178)), module, SeqLights8Module::LIGHT_R1_C6_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(179.754, 59.178)), module, SeqLights8Module::LIGHT_R1_C7_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(44.594, 89.076)), module, SeqLights8Module::LIGHT_R2_C0_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(63.903, 89.076)), module, SeqLights8Module::LIGHT_R2_C1_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(83.211, 89.076)), module, SeqLights8Module::LIGHT_R2_C2_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(102.52, 89.076)), module, SeqLights8Module::LIGHT_R2_C3_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(121.828, 89.076)), module, SeqLights8Module::LIGHT_R2_C4_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(141.137, 89.076)), module, SeqLights8Module::LIGHT_R2_C5_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(160.446, 89.076)), module, SeqLights8Module::LIGHT_R2_C6_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(179.754, 89.076)), module, SeqLights8Module::LIGHT_R2_C7_LIGHT));
	}
};


Model* modelSeqLights8Module = createModel<SeqLights8Module, SeqLights8ModuleWidget>("SeqLights8Module");