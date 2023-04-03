#include "plugin.hpp"

struct James : Module {
	
	const int NUM_GATE_SWITCHES = 48;
	const int NUM_ROWS = 6;

	enum ParamId {
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
		SWITCH_GATE_R3_C0_PARAM,
		SWITCH_GATE_R3_C1_PARAM,
		SWITCH_GATE_R3_C2_PARAM,
		SWITCH_GATE_R3_C3_PARAM,
		SWITCH_GATE_R3_C4_PARAM,
		SWITCH_GATE_R3_C5_PARAM,
		SWITCH_GATE_R3_C6_PARAM,
		SWITCH_GATE_R3_C7_PARAM,
		SWITCH_GATE_R4_C0_PARAM,
		SWITCH_GATE_R4_C1_PARAM,
		SWITCH_GATE_R4_C2_PARAM,
		SWITCH_GATE_R4_C3_PARAM,
		SWITCH_GATE_R4_C4_PARAM,
		SWITCH_GATE_R4_C5_PARAM,
		SWITCH_GATE_R4_C6_PARAM,
		SWITCH_GATE_R4_C7_PARAM,
		SWITCH_GATE_R5_C0_PARAM,
		SWITCH_GATE_R5_C1_PARAM,
		SWITCH_GATE_R5_C2_PARAM,
		SWITCH_GATE_R5_C3_PARAM,
		SWITCH_GATE_R5_C4_PARAM,
		SWITCH_GATE_R5_C5_PARAM,
		SWITCH_GATE_R5_C6_PARAM,
		SWITCH_GATE_R5_C7_PARAM,
		KNOB_DIVIDE_PARAM,
		KNOB_STEP_COUNT_PARAM,
		KNOB_CLOCK_SPEED_PARAM,
		SWITCH_GATE_MODE_PARAM,
		KNOB_RUSH_R0_PARAM,
		KNOB_RUSH_R1_PARAM,
		KNOB_RUSH_R2_PARAM,
		KNOB_RUSH_R3_PARAM,
		KNOB_RUSH_R4_PARAM,
		KNOB_RUSH_R5_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		IN_CLOCK_INPUT,
		IN_RESET_INPUT,
		INPUTS_LEN
	};

	enum OutputId {
		OUT_GATE_R0_OUTPUT,
		OUT_GATE_R1_OUTPUT,
		OUT_GATE_R2_OUTPUT,
		OUT_GATE_R3_OUTPUT,
		OUT_GATE_R4_OUTPUT,
		OUT_GATE_R5_OUTPUT,
		OUT_CLOCK_OUTPUT,
		OUTPUTS_LEN
	};

	enum LightId {
		GATE_LIGHT_R0_C0_LIGHT,
		GATE_LIGHT_R0_C1_LIGHT,
		GATE_LIGHT_R0_C2_LIGHT,
		GATE_LIGHT_R0_C3_LIGHT,
		GATE_LIGHT_R0_C4_LIGHT,
		GATE_LIGHT_R0_C5_LIGHT,
		GATE_LIGHT_R0_C6_LIGHT,
		GATE_LIGHT_R0_C7_LIGHT,
		GATE_LIGHT_R1_C0_LIGHT,
		GATE_LIGHT_R1_C1_LIGHT,
		GATE_LIGHT_R1_C2_LIGHT,
		GATE_LIGHT_R1_C3_LIGHT,
		GATE_LIGHT_R1_C4_LIGHT,
		GATE_LIGHT_R1_C5_LIGHT,
		GATE_LIGHT_R1_C6_LIGHT,
		GATE_LIGHT_R1_C7_LIGHT,
		GATE_LIGHT_R2_C0_LIGHT,
		GATE_LIGHT_R2_C1_LIGHT,
		GATE_LIGHT_R2_C2_LIGHT,
		GATE_LIGHT_R2_C3_LIGHT,
		GATE_LIGHT_R2_C4_LIGHT,
		GATE_LIGHT_R2_C5_LIGHT,
		GATE_LIGHT_R2_C6_LIGHT,
		GATE_LIGHT_R2_C7_LIGHT,
		GATE_LIGHT_R3_C0_LIGHT,
		GATE_LIGHT_R3_C1_LIGHT,
		GATE_LIGHT_R3_C2_LIGHT,
		GATE_LIGHT_R3_C3_LIGHT,
		GATE_LIGHT_R3_C4_LIGHT,
		GATE_LIGHT_R3_C5_LIGHT,
		GATE_LIGHT_R3_C6_LIGHT,
		GATE_LIGHT_R3_C7_LIGHT,
		GATE_LIGHT_R4_C0_LIGHT,
		GATE_LIGHT_R4_C1_LIGHT,
		GATE_LIGHT_R4_C2_LIGHT,
		GATE_LIGHT_R4_C3_LIGHT,
		GATE_LIGHT_R4_C4_LIGHT,
		GATE_LIGHT_R4_C5_LIGHT,
		GATE_LIGHT_R4_C6_LIGHT,
		GATE_LIGHT_R4_C7_LIGHT,
		GATE_LIGHT_R5_C0_LIGHT,
		GATE_LIGHT_R5_C1_LIGHT,
		GATE_LIGHT_R5_C2_LIGHT,
		GATE_LIGHT_R5_C3_LIGHT,
		GATE_LIGHT_R5_C4_LIGHT,
		GATE_LIGHT_R5_C5_LIGHT,
		GATE_LIGHT_R5_C6_LIGHT,
		GATE_LIGHT_R5_C7_LIGHT,
		LIGHT_GATE_MODE_CONTINUOUS_LIGHT,
		LIGHT_GATE_MODE_TRIGGER_LIGHT,
		LIGHT_R0_C0_LIGHT,
		LIGHT_R0_C1_LIGHT,
		LIGHT_R0_C2_LIGHT,
		LIGHT_R0_C3_LIGHT,
		LIGHT_R0_C4_LIGHT,
		LIGHT_R0_C5_LIGHT,
		LIGHT_R0_C6_LIGHT,
		LIGHT_R0_C7_LIGHT,
		LIGHTS_LEN
	};

	James() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(KNOB_DIVIDE_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_STEP_COUNT_PARAM, 0.f, 8.f, 8.f, "Step count");
		configParam(KNOB_CLOCK_SPEED_PARAM, 0.f, 1.0f, 0.5f, "Speed");
		configParam(SWITCH_GATE_MODE_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_RUSH_R0_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R0_C0_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R0_C1_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R0_C2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R0_C3_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R0_C4_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R0_C5_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R0_C6_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R0_C7_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_RUSH_R1_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R1_C0_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R1_C1_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R1_C2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R1_C3_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R1_C4_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R1_C5_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R1_C6_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R1_C7_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_RUSH_R2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R2_C0_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R2_C1_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R2_C2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R2_C3_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R2_C4_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R2_C5_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R2_C6_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R2_C7_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_RUSH_R3_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R3_C0_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R3_C1_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R3_C2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R3_C3_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R3_C4_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R3_C5_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R3_C6_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R3_C7_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_RUSH_R4_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R4_C0_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R4_C1_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R4_C2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R4_C3_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R4_C4_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R4_C5_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R4_C6_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R4_C7_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_RUSH_R5_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R5_C0_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R5_C1_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R5_C2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R5_C3_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R5_C4_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R5_C5_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R5_C6_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R5_C7_PARAM, 0.f, 1.f, 0.f, "");
		configInput(IN_CLOCK_INPUT, "");
		configInput(IN_RESET_INPUT, "");
		configOutput(OUT_CLOCK_OUTPUT, "");
		configOutput(OUT_GATE_R0_OUTPUT, "");
		configOutput(OUT_GATE_R1_OUTPUT, "");
		configOutput(OUT_GATE_R2_OUTPUT, "");
		configOutput(OUT_GATE_R3_OUTPUT, "");
		configOutput(OUT_GATE_R4_OUTPUT, "");
		configOutput(OUT_GATE_R5_OUTPUT, "");
	}

	short getButtonId(short row, short column) {
		return column + (row*8);
	}

	short getLightId(short row, short column) {
		return column + (row*8);
	}

	short getGateOutputId(short row) {
		// I know this seems redundant,
		// but I'm keeping it so that 
		// I understand this code a 
		// year from now
		return row;
	}

	void handleGateButtonLeds() {
		for(int i = 0; i < NUM_GATE_SWITCHES; i++) {
			if(params[i].getValue() > 0) {
				lights[i].setBrightness(0.5);
			} else {
				lights[i].setBrightness(0.0);
			}
		}
	}

	dsp::Timer timer;
	float clockSpeed = 0.5f;
	dsp::PulseGenerator clockOutPulse;
	IgnoreClockAfterResetTimer ignoreClockAfterResetTimer;

	float lastclockVoltage = 0.0f;
	float lastResetInput = 0.0f;

	dsp::PulseGenerator gatePulseGenerators [6] = { };

	ClockTracker clockTracker{8, 6};

	bool gateTriggerModeEnabled = true;

	bool shouldPulseThisStep(short row) {
		return params[
			getButtonId(row, clockTracker.getCurrentStepForRow(row))
		].getValue() > 0.5 
		&& clockTracker.getHasPulsedThisStepForRow(row) == false;
	}

	float getInternalClockVoltage(float sampleRate) {
		clockSpeed = params[KNOB_CLOCK_SPEED_PARAM].getValue();
		const float timeSinceLastPulsed = timer.process(1.0 / sampleRate);
		if(timeSinceLastPulsed > 1.0f - (clockSpeed*0.95f)) {
			clockOutPulse.trigger(1e-3f);
			timer.reset();
		}
		bool shouldClockOutPulse = clockOutPulse.process(1.0 / sampleRate);
		return shouldClockOutPulse ? 10.0 : 0.0;
	}

	void process(const ProcessArgs& args) override {
		ignoreClockAfterResetTimer.process(1.0 / args.sampleRate); // must be called every process to ensure timer progresses

		const bool hasExternalClock = inputs[IN_CLOCK_INPUT].isConnected();
		float internalClockVoltage = 0.0f;

		if(hasExternalClock) {
			outputs[OUT_CLOCK_OUTPUT].setVoltage(inputs[IN_CLOCK_INPUT].getVoltage());
		} else {
			internalClockVoltage = getInternalClockVoltage(args.sampleRate);
			outputs[OUT_CLOCK_OUTPUT].setVoltage(internalClockVoltage);
		}

		const float clockInput = inputs[IN_CLOCK_INPUT].getVoltage();
		const float clockVoltage = hasExternalClock ? clockInput : internalClockVoltage;

		clockTracker.numSteps = round(params[KNOB_STEP_COUNT_PARAM].getValue());

		handleGateButtonLeds();

		if(clockTracker.numSteps == 0) { // don't output anything if steps = 0;
			// turnOffAllStepIndicatorLights();
			lights[LIGHT_GATE_MODE_TRIGGER_LIGHT].setBrightness(0);
			lights[LIGHT_GATE_MODE_CONTINUOUS_LIGHT].setBrightness(0);
			return;
		}

		float resetInput = inputs[IN_RESET_INPUT].getVoltage();
		if (lastResetInput == 0 && resetInput != 0) {
			// reset();
		}

		// calculate if row should pulse
		if (lastclockVoltage == 0 && clockVoltage != 0 && !ignoreClockAfterResetTimer.shouldIgnore) {
			clockTracker.nextClock();
			for(int i = 0; i < NUM_ROWS; i++) {
				if(shouldPulseThisStep(i)) {
					gatePulseGenerators[i].trigger(1e-3f);
					clockTracker.setHasPulsedThisStepForRow(i, true);
				}
			}
		}

		// Handle step indicator lights
		// turnOffAllStepIndicatorLights();
		// lights[getLightId(0, clockTracker.getCurrentStepForRow(0))].setBrightness(1.0f);
		// lights[getLightId(1, clockTracker.getCurrentStepForRow(1))].setBrightness(1.0f);
		// lights[getLightId(2, clockTracker.getCurrentStepForRow(2))].setBrightness(1.0f);
		// End

		// handle gate trigger/continuous toggle
		if(params[SWITCH_GATE_MODE_PARAM].getValue() > 0) {
			gateTriggerModeEnabled = true;
			lights[LIGHT_GATE_MODE_TRIGGER_LIGHT].setBrightness(1);
			lights[LIGHT_GATE_MODE_CONTINUOUS_LIGHT].setBrightness(0);
		} else {
			gateTriggerModeEnabled = false;
			lights[LIGHT_GATE_MODE_TRIGGER_LIGHT].setBrightness(0);
			lights[LIGHT_GATE_MODE_CONTINUOUS_LIGHT].setBrightness(1);
		}
		// end

		// Handle pulse (trigger) gate outputs

		if(gateTriggerModeEnabled) {
			for(int i = 0; i < NUM_ROWS; i++) {
				if(outputs[getGateOutputId(i)].isConnected()) {
					const bool pulse = gatePulseGenerators[i].process(1.0 / args.sampleRate);
					outputs[getGateOutputId(i)].setVoltage(pulse ? 10.0 : 0.0);
				}
			}
		}


		// if(outputs[OUT_GATE_R0_OUTPUT].isConnected() && gateTriggerModeEnabled) {
		// 	// const bool pulseR0 = gatePulseR0.process(1.0 / args.sampleRate);
		// 	// outputs[OUT_GATE_R0_OUTPUT].setVoltage(pulseR0 ? 10.0 : 0.0);	
		// 	const bool pulse = gatePulseGenerators[0].process(1.0 / args.sampleRate);
		// 	outputs[OUT_GATE_R0_OUTPUT].setVoltage(pulse ? 10.0 : 0.0);
		// }

		// if(outputs[OUT_GATE_R1_OUTPUT].isConnected() && gateTriggerModeEnabled) {
		// 	const bool pulseR1 = gatePulseR1.process(1.0 / args.sampleRate);
		// 	outputs[OUT_GATE_R1_OUTPUT].setVoltage(pulseR1 ? 10.0 : 0.0);
		// }

		// if(outputs[OUT_GATE_R2_OUTPUT].isConnected() && gateTriggerModeEnabled) {
		// 	const bool pulseR2 = gatePulseR2.process(1.0 / args.sampleRate);
		// 	outputs[OUT_GATE_R2_OUTPUT].setVoltage(pulseR2 ? 10.0 : 0.0);
		// }

		// if(outputs[OUT_GATE_R3_OUTPUT].isConnected() && gateTriggerModeEnabled) {
		// 	const bool pulseR3 = gatePulseR1.process(1.0 / args.sampleRate);
		// 	outputs[OUT_GATE_R3_OUTPUT].setVoltage(pulseR3 ? 10.0 : 0.0);		
		// }

		// if(outputs[OUT_GATE_R1_OUTPUT].isConnected() && gateTriggerModeEnabled) {
		// 	const bool pulseR1 = gatePulseR1.process(1.0 / args.sampleRate);
		// 	outputs[OUT_GATE_R1_OUTPUT].setVoltage(pulseR1 ? 10.0 : 0.0);
		// }

		// if(outputs[OUT_GATE_R2_OUTPUT].isConnected() && gateTriggerModeEnabled) {
		// 	const bool pulseR2 = gatePulseR2.process(1.0 / args.sampleRate);
		// 	outputs[OUT_GATE_R2_OUTPUT].setVoltage(pulseR2 ? 10.0 : 0.0);
		// }
		// End

		// Handle continuous gate outputs
		// if(outputs[OUT_GATE_R0_OUTPUT].isConnected() && !gateTriggerModeEnabled) {
		// 	const bool shouldGateR0 = params[getButtonId(0, clockTracker.getCurrentStepForRow(0))].getValue() > 0;
		// 	outputs[OUT_GATE_R0_OUTPUT].setVoltage(shouldGateR0 ? 10.0 : 0.0);		
		// }
 
		// if(outputs[OUT_GATE_R1_OUTPUT].isConnected() && !gateTriggerModeEnabled) {
		// 	const bool shouldGateR1 = params[getButtonId(0, clockTracker.getCurrentStepForRow(0))].getValue() > 0;
		// 	outputs[OUT_GATE_R1_OUTPUT].setVoltage(shouldGateR1 ? 10.0 : 0.0);		
		// }

		// if(outputs[OUT_GATE_R2_OUTPUT].isConnected() && !gateTriggerModeEnabled) {
		// 	const bool shouldGateR2 = params[getButtonId(0, clockTracker.getCurrentStepForRow(0))].getValue() > 0;
		// 	outputs[OUT_GATE_R2_OUTPUT].setVoltage(shouldGateR2 ? 10.0 : 0.0);		
		// }
		// End

		lastclockVoltage = clockVoltage;
		lastResetInput = resetInput;
	}
};


struct JamesWidget : ModuleWidget {
	JamesWidget(James* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/James.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<SteppedRedKnob>(mm2px(Vec(57.496, 16.145)), module, James::KNOB_DIVIDE_PARAM));
		addParam(createParamCentered<SteppedRedKnob>(mm2px(Vec(96.113, 16.145)), module, James::KNOB_STEP_COUNT_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(134.731, 16.145)), module, James::KNOB_CLOCK_SPEED_PARAM));
		addParam(createParamCentered<CKD6InvisibleLatch>(mm2px(Vec(173.348, 16.145)), module, James::SWITCH_GATE_MODE_PARAM));

		addParam(createParamCentered<RedKnob>(mm2px(Vec(12.224, 33.874)), module, James::KNOB_RUSH_R0_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(12.224, 48.056)), module, James::KNOB_RUSH_R1_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(12.224, 62.238)), module, James::KNOB_RUSH_R2_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(12.224, 76.419)), module, James::KNOB_RUSH_R3_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(12.224, 90.601)), module, James::KNOB_RUSH_R4_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(12.224, 104.783)), module, James::KNOB_RUSH_R5_PARAM));


		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(38.188, 33.874)), module, James::SWITCH_GATE_R0_C0_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(57.496, 33.874)), module, James::SWITCH_GATE_R0_C1_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(76.805, 33.874)), module, James::SWITCH_GATE_R0_C2_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(96.113, 33.874)), module, James::SWITCH_GATE_R0_C3_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(115.422, 33.874)), module, James::SWITCH_GATE_R0_C4_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(134.731, 33.874)), module, James::SWITCH_GATE_R0_C5_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(154.039, 33.874)), module, James::SWITCH_GATE_R0_C6_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(173.348, 33.874)), module, James::SWITCH_GATE_R0_C7_PARAM));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(38.188, 33.874)), module, James::GATE_LIGHT_R0_C0_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(57.496, 33.874)), module, James::GATE_LIGHT_R0_C1_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(76.805, 33.874)), module, James::GATE_LIGHT_R0_C2_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(96.113, 33.874)), module, James::GATE_LIGHT_R0_C3_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(115.422, 33.874)), module, James::GATE_LIGHT_R0_C4_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(134.731, 33.874)), module, James::GATE_LIGHT_R0_C5_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(154.039, 33.874)), module, James::GATE_LIGHT_R0_C6_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(173.348, 33.874)), module, James::GATE_LIGHT_R0_C7_LIGHT));

		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(38.188, 48.056)), module, James::SWITCH_GATE_R1_C0_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(57.496, 48.056)), module, James::SWITCH_GATE_R1_C1_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(76.805, 48.056)), module, James::SWITCH_GATE_R1_C2_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(96.113, 48.056)), module, James::SWITCH_GATE_R1_C3_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(115.422, 48.056)), module, James::SWITCH_GATE_R1_C4_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(134.731, 48.056)), module, James::SWITCH_GATE_R1_C5_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(154.039, 48.056)), module, James::SWITCH_GATE_R1_C6_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(173.348, 48.056)), module, James::SWITCH_GATE_R1_C7_PARAM));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(38.188, 48.056)), module, James::GATE_LIGHT_R1_C0_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(57.496, 48.056)), module, James::GATE_LIGHT_R1_C1_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(76.805, 48.056)), module, James::GATE_LIGHT_R1_C2_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(96.113, 48.056)), module, James::GATE_LIGHT_R1_C3_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(115.422, 48.056)), module, James::GATE_LIGHT_R1_C4_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(134.731, 48.056)), module, James::GATE_LIGHT_R1_C5_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(154.039, 48.056)), module, James::GATE_LIGHT_R1_C6_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(173.348, 48.056)), module, James::GATE_LIGHT_R1_C7_LIGHT));

		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(38.188, 62.238)), module, James::SWITCH_GATE_R2_C0_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(57.496, 62.238)), module, James::SWITCH_GATE_R2_C1_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(76.805, 62.238)), module, James::SWITCH_GATE_R2_C2_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(96.113, 62.238)), module, James::SWITCH_GATE_R2_C3_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(115.422, 62.238)), module, James::SWITCH_GATE_R2_C4_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(134.731, 62.238)), module, James::SWITCH_GATE_R2_C5_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(154.039, 62.238)), module, James::SWITCH_GATE_R2_C6_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(173.348, 62.238)), module, James::SWITCH_GATE_R2_C7_PARAM));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(38.188, 62.238)), module, James::GATE_LIGHT_R2_C0_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(57.496, 62.238)), module, James::GATE_LIGHT_R2_C1_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(76.805, 62.238)), module, James::GATE_LIGHT_R2_C2_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(96.113, 62.238)), module, James::GATE_LIGHT_R2_C3_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(115.422, 62.238)), module, James::GATE_LIGHT_R2_C4_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(134.731, 62.238)), module, James::GATE_LIGHT_R2_C5_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(154.039, 62.238)), module, James::GATE_LIGHT_R2_C6_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(173.348, 62.238)), module, James::GATE_LIGHT_R2_C7_LIGHT));

		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(38.188, 76.419)), module, James::SWITCH_GATE_R3_C0_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(57.496, 76.419)), module, James::SWITCH_GATE_R3_C1_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(76.805, 76.419)), module, James::SWITCH_GATE_R3_C2_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(96.113, 76.419)), module, James::SWITCH_GATE_R3_C3_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(115.422, 76.419)), module, James::SWITCH_GATE_R3_C4_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(134.731, 76.419)), module, James::SWITCH_GATE_R3_C5_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(154.039, 76.419)), module, James::SWITCH_GATE_R3_C6_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(173.348, 76.419)), module, James::SWITCH_GATE_R3_C7_PARAM));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(38.188, 76.419)), module, James::GATE_LIGHT_R3_C0_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(57.496, 76.419)), module, James::GATE_LIGHT_R3_C1_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(76.805, 76.419)), module, James::GATE_LIGHT_R3_C2_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(96.113, 76.419)), module, James::GATE_LIGHT_R3_C3_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(115.422, 76.419)), module, James::GATE_LIGHT_R3_C4_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(134.731, 76.419)), module, James::GATE_LIGHT_R3_C5_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(154.039, 76.419)), module, James::GATE_LIGHT_R3_C6_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(173.348, 76.419)), module, James::GATE_LIGHT_R3_C7_LIGHT));

		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(38.188, 90.601)), module, James::SWITCH_GATE_R4_C0_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(57.496, 90.601)), module, James::SWITCH_GATE_R4_C1_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(76.805, 90.601)), module, James::SWITCH_GATE_R4_C2_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(96.113, 90.601)), module, James::SWITCH_GATE_R4_C3_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(115.422, 90.601)), module, James::SWITCH_GATE_R4_C4_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(134.731, 90.601)), module, James::SWITCH_GATE_R4_C5_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(154.039, 90.601)), module, James::SWITCH_GATE_R4_C6_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(173.348, 90.601)), module, James::SWITCH_GATE_R4_C7_PARAM));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(38.188, 90.601)), module, James::GATE_LIGHT_R4_C0_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(57.496, 90.601)), module, James::GATE_LIGHT_R4_C1_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(76.805, 90.601)), module, James::GATE_LIGHT_R4_C2_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(96.113, 90.601)), module, James::GATE_LIGHT_R4_C3_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(115.422, 90.601)), module, James::GATE_LIGHT_R4_C4_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(134.731, 90.601)), module, James::GATE_LIGHT_R4_C5_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(154.039, 90.601)), module, James::GATE_LIGHT_R4_C6_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(173.348, 90.601)), module, James::GATE_LIGHT_R4_C7_LIGHT));

		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(38.188, 104.783)), module, James::SWITCH_GATE_R5_C0_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(57.496, 104.783)), module, James::SWITCH_GATE_R5_C1_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(76.805, 104.783)), module, James::SWITCH_GATE_R5_C2_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(96.113, 104.783)), module, James::SWITCH_GATE_R5_C3_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(115.422, 104.783)), module, James::SWITCH_GATE_R5_C4_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(134.731, 104.783)), module, James::SWITCH_GATE_R5_C5_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(154.039, 104.783)), module, James::SWITCH_GATE_R5_C6_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(173.348, 104.783)), module, James::SWITCH_GATE_R5_C7_PARAM));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(38.188, 104.783)), module, James::GATE_LIGHT_R5_C0_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(57.496, 104.783)), module, James::GATE_LIGHT_R5_C1_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(76.805, 104.783)), module, James::GATE_LIGHT_R5_C2_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(96.113, 104.783)), module, James::GATE_LIGHT_R5_C3_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(115.422, 104.783)), module, James::GATE_LIGHT_R5_C4_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(134.731, 104.783)), module, James::GATE_LIGHT_R5_C5_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(154.039, 104.783)), module, James::GATE_LIGHT_R5_C6_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(173.348, 104.783)), module, James::GATE_LIGHT_R5_C7_LIGHT));


		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(76.805, 16.145)), module, James::IN_CLOCK_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(154.039, 16.145)), module, James::IN_RESET_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(115.422, 16.145)), module, James::OUT_CLOCK_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(201.628, 33.874)), module, James::OUT_GATE_R0_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(201.628, 48.056)), module, James::OUT_GATE_R1_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(201.628, 62.238)), module, James::OUT_GATE_R2_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(201.628, 76.419)), module, James::OUT_GATE_R3_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(201.628, 90.601)), module, James::OUT_GATE_R4_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(201.628, 104.783)), module, James::OUT_GATE_R5_OUTPUT));

		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(179.754, 11.551)), module, James::LIGHT_GATE_MODE_CONTINUOUS_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(179.754, 20.902)), module, James::LIGHT_GATE_MODE_TRIGGER_LIGHT));

		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(44.594, 29.28)), module, James::LIGHT_R0_C0_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(63.903, 29.28)), module, James::LIGHT_R0_C1_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(83.211, 29.28)), module, James::LIGHT_R0_C2_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(102.52, 29.28)), module, James::LIGHT_R0_C3_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(121.828, 29.28)), module, James::LIGHT_R0_C4_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(141.137, 29.28)), module, James::LIGHT_R0_C5_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(160.446, 29.28)), module, James::LIGHT_R0_C6_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(179.754, 29.28)), module, James::LIGHT_R0_C7_LIGHT));
	}
};


Model* modelJames = createModel<James, JamesWidget>("James");