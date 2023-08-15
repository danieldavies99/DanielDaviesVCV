#include "plugin.hpp"
#include <functional>

using namespace rack;

struct Sequel16 : Module {
	enum ParamId {
		KNOB_STEP_R0_C0_PARAM,
		KNOB_STEP_R0_C1_PARAM,
		KNOB_STEP_R0_C2_PARAM,
		KNOB_STEP_R0_C3_PARAM,
		KNOB_STEP_R0_C4_PARAM,
		KNOB_STEP_R0_C5_PARAM,
		KNOB_STEP_R0_C6_PARAM,
		KNOB_STEP_R0_C7_PARAM,
		KNOB_STEP_R0_C8_PARAM,
		KNOB_STEP_R0_C9_PARAM,
		KNOB_STEP_R0_C10_PARAM,
		KNOB_STEP_R0_C11_PARAM,
		KNOB_STEP_R0_C12_PARAM,
		KNOB_STEP_R0_C13_PARAM,
		KNOB_STEP_R0_C14_PARAM,
		KNOB_STEP_R0_C15_PARAM,
		KNOB_STEP_R1_C0_PARAM,
		KNOB_STEP_R1_C1_PARAM,
		KNOB_STEP_R1_C2_PARAM,
		KNOB_STEP_R1_C3_PARAM,
		KNOB_STEP_R1_C4_PARAM,
		KNOB_STEP_R1_C5_PARAM,
		KNOB_STEP_R1_C6_PARAM,
		KNOB_STEP_R1_C7_PARAM,
		KNOB_STEP_R1_C8_PARAM,
		KNOB_STEP_R1_C9_PARAM,
		KNOB_STEP_R1_C10_PARAM,
		KNOB_STEP_R1_C11_PARAM,
		KNOB_STEP_R1_C12_PARAM,
		KNOB_STEP_R1_C13_PARAM,
		KNOB_STEP_R1_C14_PARAM,
		KNOB_STEP_R1_C15_PARAM,
		KNOB_STEP_R2_C0_PARAM,
		KNOB_STEP_R2_C1_PARAM,
		KNOB_STEP_R2_C2_PARAM,
		KNOB_STEP_R2_C3_PARAM,
		KNOB_STEP_R2_C4_PARAM,
		KNOB_STEP_R2_C5_PARAM,
		KNOB_STEP_R2_C6_PARAM,
		KNOB_STEP_R2_C7_PARAM,
		KNOB_STEP_R2_C8_PARAM,
		KNOB_STEP_R2_C9_PARAM,
		KNOB_STEP_R2_C10_PARAM,
		KNOB_STEP_R2_C11_PARAM,
		KNOB_STEP_R2_C12_PARAM,
		KNOB_STEP_R2_C13_PARAM,
		KNOB_STEP_R2_C14_PARAM,
		KNOB_STEP_R2_C15_PARAM,
		SWITCH_GATE_R0_C0_PARAM,
		SWITCH_GATE_R0_C1_PARAM,
		SWITCH_GATE_R0_C2_PARAM,
		SWITCH_GATE_R0_C3_PARAM,
		SWITCH_GATE_R0_C4_PARAM,
		SWITCH_GATE_R0_C5_PARAM,
		SWITCH_GATE_R0_C6_PARAM,
		SWITCH_GATE_R0_C7_PARAM,
		SWITCH_GATE_R0_C8_PARAM,
		SWITCH_GATE_R0_C9_PARAM,
		SWITCH_GATE_R0_C10_PARAM,
		SWITCH_GATE_R0_C11_PARAM,
		SWITCH_GATE_R0_C12_PARAM,
		SWITCH_GATE_R0_C13_PARAM,
		SWITCH_GATE_R0_C14_PARAM,
		SWITCH_GATE_R0_C15_PARAM,
		SWITCH_GATE_R1_C0_PARAM,
		SWITCH_GATE_R1_C1_PARAM,
		SWITCH_GATE_R1_C2_PARAM,
		SWITCH_GATE_R1_C3_PARAM,
		SWITCH_GATE_R1_C4_PARAM,
		SWITCH_GATE_R1_C5_PARAM,
		SWITCH_GATE_R1_C6_PARAM,
		SWITCH_GATE_R1_C7_PARAM,
		SWITCH_GATE_R1_C8_PARAM,
		SWITCH_GATE_R1_C9_PARAM,
		SWITCH_GATE_R1_C10_PARAM,
		SWITCH_GATE_R1_C11_PARAM,
		SWITCH_GATE_R1_C12_PARAM,
		SWITCH_GATE_R1_C13_PARAM,
		SWITCH_GATE_R1_C14_PARAM,
		SWITCH_GATE_R1_C15_PARAM,
		SWITCH_GATE_R2_C0_PARAM,
		SWITCH_GATE_R2_C1_PARAM,
		SWITCH_GATE_R2_C2_PARAM,
		SWITCH_GATE_R2_C3_PARAM,
		SWITCH_GATE_R2_C4_PARAM,
		SWITCH_GATE_R2_C5_PARAM,
		SWITCH_GATE_R2_C6_PARAM,
		SWITCH_GATE_R2_C7_PARAM,
		SWITCH_GATE_R2_C8_PARAM,
		SWITCH_GATE_R2_C9_PARAM,
		SWITCH_GATE_R2_C10_PARAM,
		SWITCH_GATE_R2_C11_PARAM,
		SWITCH_GATE_R2_C12_PARAM,
		SWITCH_GATE_R2_C13_PARAM,
		SWITCH_GATE_R2_C14_PARAM,
		SWITCH_GATE_R2_C15_PARAM,
		KNOB_TIME_DIVIDE_R0_PARAM,
		KNOB_TIME_DIVIDE_R1_PARAM,
		KNOB_TIME_DIVIDE_R2_PARAM,
		KNOB_STEP_COUNT_PARAM,
		KNOB_CLOCK_SPEED_PARAM,
		SWITCH_GATE_MODE_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		IN_CLOCK_INPUT,
		IN_RESET_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		OUT_CLOCK_OUTPUT,
		OUT_CV_R0_OUTPUT,
		OUT_GATE_R0_OUTPUT,
		OUT_CV_R1_OUTPUT,
		OUT_GATE_R1_OUTPUT,
		OUT_CV_R2_OUTPUT,
		OUT_GATE_R2_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHT_R0_C0_LIGHT,
		LIGHT_R0_C1_LIGHT,
		LIGHT_R0_C2_LIGHT,
		LIGHT_R0_C3_LIGHT,
		LIGHT_R0_C4_LIGHT,
		LIGHT_R0_C5_LIGHT,
		LIGHT_R0_C6_LIGHT,
		LIGHT_R0_C7_LIGHT,
		LIGHT_R0_C8_LIGHT,
		LIGHT_R0_C9_LIGHT,
		LIGHT_R0_C10_LIGHT,
		LIGHT_R0_C11_LIGHT,
		LIGHT_R0_C12_LIGHT,
		LIGHT_R0_C13_LIGHT,
		LIGHT_R0_C14_LIGHT,
		LIGHT_R0_C15_LIGHT,
		LIGHT_R1_C0_LIGHT,
		LIGHT_R1_C1_LIGHT,
		LIGHT_R1_C2_LIGHT,
		LIGHT_R1_C3_LIGHT,
		LIGHT_R1_C4_LIGHT,
		LIGHT_R1_C5_LIGHT,
		LIGHT_R1_C6_LIGHT,
		LIGHT_R1_C7_LIGHT,
		LIGHT_R1_C8_LIGHT,
		LIGHT_R1_C9_LIGHT,
		LIGHT_R1_C10_LIGHT,
		LIGHT_R1_C11_LIGHT,
		LIGHT_R1_C12_LIGHT,
		LIGHT_R1_C13_LIGHT,
		LIGHT_R1_C14_LIGHT,
		LIGHT_R1_C15_LIGHT,
		LIGHT_R2_C0_LIGHT,
		LIGHT_R2_C1_LIGHT,
		LIGHT_R2_C2_LIGHT,
		LIGHT_R2_C3_LIGHT,
		LIGHT_R2_C4_LIGHT,
		LIGHT_R2_C5_LIGHT,
		LIGHT_R2_C6_LIGHT,
		LIGHT_R2_C7_LIGHT,
		LIGHT_R2_C8_LIGHT,
		LIGHT_R2_C9_LIGHT,
		LIGHT_R2_C10_LIGHT,
		LIGHT_R2_C11_LIGHT,
		LIGHT_R2_C12_LIGHT,
		LIGHT_R2_C13_LIGHT,
		LIGHT_R2_C14_LIGHT,
		LIGHT_R2_C15_LIGHT,
		GATE_LIGHT_R0_C0_LIGHT,
		GATE_LIGHT_R0_C1_LIGHT,
		GATE_LIGHT_R0_C2_LIGHT,
		GATE_LIGHT_R0_C3_LIGHT,
		GATE_LIGHT_R0_C4_LIGHT,
		GATE_LIGHT_R0_C5_LIGHT,
		GATE_LIGHT_R0_C6_LIGHT,
		GATE_LIGHT_R0_C7_LIGHT,
		GATE_LIGHT_R0_C8_LIGHT,
		GATE_LIGHT_R0_C9_LIGHT,
		GATE_LIGHT_R0_C10_LIGHT,
		GATE_LIGHT_R0_C11_LIGHT,
		GATE_LIGHT_R0_C12_LIGHT,
		GATE_LIGHT_R0_C13_LIGHT,
		GATE_LIGHT_R0_C14_LIGHT,
		GATE_LIGHT_R0_C15_LIGHT,
		GATE_LIGHT_R1_C0_LIGHT,
		GATE_LIGHT_R1_C1_LIGHT,
		GATE_LIGHT_R1_C2_LIGHT,
		GATE_LIGHT_R1_C3_LIGHT,
		GATE_LIGHT_R1_C4_LIGHT,
		GATE_LIGHT_R1_C5_LIGHT,
		GATE_LIGHT_R1_C6_LIGHT,
		GATE_LIGHT_R1_C7_LIGHT,
		GATE_LIGHT_R1_C8_LIGHT,
		GATE_LIGHT_R1_C9_LIGHT,
		GATE_LIGHT_R1_C10_LIGHT,
		GATE_LIGHT_R1_C11_LIGHT,
		GATE_LIGHT_R1_C12_LIGHT,
		GATE_LIGHT_R1_C13_LIGHT,
		GATE_LIGHT_R1_C14_LIGHT,
		GATE_LIGHT_R1_C15_LIGHT,
		GATE_LIGHT_R2_C0_LIGHT,
		GATE_LIGHT_R2_C1_LIGHT,
		GATE_LIGHT_R2_C2_LIGHT,
		GATE_LIGHT_R2_C3_LIGHT,
		GATE_LIGHT_R2_C4_LIGHT,
		GATE_LIGHT_R2_C5_LIGHT,
		GATE_LIGHT_R2_C6_LIGHT,
		GATE_LIGHT_R2_C7_LIGHT,
		GATE_LIGHT_R2_C8_LIGHT,
		GATE_LIGHT_R2_C9_LIGHT,
		GATE_LIGHT_R2_C10_LIGHT,
		GATE_LIGHT_R2_C11_LIGHT,
		GATE_LIGHT_R2_C12_LIGHT,
		GATE_LIGHT_R2_C13_LIGHT,
		GATE_LIGHT_R2_C14_LIGHT,
		GATE_LIGHT_R2_C15_LIGHT,
		LIGHT_GATE_MODE_CONTINUOUS_LIGHT,
		LIGHT_GATE_MODE_TRIGGER_LIGHT,
		LIGHTS_LEN
	};

    // Expander
	SequelSaveInterface rightMessages[2];

	Sequel16() {
		rightExpander.producerMessage = &rightMessages[0];
		rightExpander.consumerMessage = &rightMessages[1];

		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);

		// Inputs
		configInput(IN_RESET_INPUT, "Reset");
		configInput(IN_CLOCK_INPUT, "Clock");
		
		// Outputs
		configOutput(OUT_CV_R0_OUTPUT, "Row 1 CV");
		configOutput(OUT_CV_R1_OUTPUT, "Row 2 CV");
		configOutput(OUT_CV_R2_OUTPUT, "Row 3 CV");
		configOutput(OUT_GATE_R0_OUTPUT, "Row 1 gate");
		configOutput(OUT_GATE_R1_OUTPUT, "Row 2 gate");
		configOutput(OUT_GATE_R2_OUTPUT, "Row 3 gate");
		configOutput(OUT_CLOCK_OUTPUT, "Clock");


		// Params
		configParam(KNOB_STEP_COUNT_PARAM, 0.f, 16.f, 16.f, "Step count");
		configParam(KNOB_CLOCK_SPEED_PARAM, 0.f, 1.0f, 0.5f, "Speed");
		configSwitch(SWITCH_GATE_MODE_PARAM, 0, 1, 1, "Gate Mode", {"Continuous", "Trigger"});
		configSwitch(KNOB_TIME_DIVIDE_R0_PARAM, 1, 10, 1, "Clock Divide Row 1", {"1", "2", "3", "4", "6", "8", "16", "32", "48", "64"});
		configSwitch(KNOB_TIME_DIVIDE_R1_PARAM, 1, 10, 1, "Clock Divide Row 2", {"1", "2", "3", "4", "6", "8", "16", "32", "48", "64"});
		configSwitch(KNOB_TIME_DIVIDE_R2_PARAM, 1, 10, 1, "Clock Divide Row 3", {"1", "2", "3", "4", "6", "8", "16", "32", "48", "64"});

		configParam(KNOB_STEP_R0_C0_PARAM, 0.f, 10.f, 0.f, "Step CV");
		configParam(KNOB_STEP_R0_C1_PARAM, 0.f, 10.f, 0.f, "Step CV");
		configParam(KNOB_STEP_R0_C2_PARAM, 0.f, 10.f, 0.f, "Step CV");
		configParam(KNOB_STEP_R0_C3_PARAM, 0.f, 10.f, 0.f, "Step CV");
		configParam(KNOB_STEP_R0_C4_PARAM, 0.f, 10.f, 0.f, "Step CV");
		configParam(KNOB_STEP_R0_C5_PARAM, 0.f, 10.f, 0.f, "Step CV");
		configParam(KNOB_STEP_R0_C6_PARAM, 0.f, 10.f, 0.f, "Step CV");
		configParam(KNOB_STEP_R0_C7_PARAM, 0.f, 10.f, 0.f, "Step CV");
		configParam(KNOB_STEP_R0_C8_PARAM, 0.f, 10.f, 0.f, "Step CV");
		configParam(KNOB_STEP_R0_C9_PARAM, 0.f, 10.f, 0.f, "Step CV");
		configParam(KNOB_STEP_R0_C10_PARAM, 0.f, 10.f, 0.f, "Step CV");
		configParam(KNOB_STEP_R0_C11_PARAM, 0.f, 10.f, 0.f, "Step CV");
		configParam(KNOB_STEP_R0_C12_PARAM, 0.f, 10.f, 0.f, "Step CV");
		configParam(KNOB_STEP_R0_C13_PARAM, 0.f, 10.f, 0.f, "Step CV");
		configParam(KNOB_STEP_R0_C14_PARAM, 0.f, 10.f, 0.f, "Step CV");
		configParam(KNOB_STEP_R0_C15_PARAM, 0.f, 10.f, 0.f, "Step CV");
		configParam(KNOB_STEP_R1_C0_PARAM, 0.f, 10.f, 0.f, "Step CV");
		configParam(KNOB_STEP_R1_C1_PARAM, 0.f, 10.f, 0.f, "Step CV");
		configParam(KNOB_STEP_R1_C2_PARAM, 0.f, 10.f, 0.f, "Step CV");
		configParam(KNOB_STEP_R1_C3_PARAM, 0.f, 10.f, 0.f, "Step CV");
		configParam(KNOB_STEP_R1_C4_PARAM, 0.f, 10.f, 0.f, "Step CV");
		configParam(KNOB_STEP_R1_C5_PARAM, 0.f, 10.f, 0.f, "Step CV");
		configParam(KNOB_STEP_R1_C6_PARAM, 0.f, 10.f, 0.f, "Step CV");
		configParam(KNOB_STEP_R1_C7_PARAM, 0.f, 10.f, 0.f, "Step CV");
		configParam(KNOB_STEP_R1_C8_PARAM, 0.f, 10.f, 0.f, "Step CV");
		configParam(KNOB_STEP_R1_C9_PARAM, 0.f, 10.f, 0.f, "Step CV");
		configParam(KNOB_STEP_R1_C10_PARAM, 0.f, 10.f, 0.f, "Step CV");
		configParam(KNOB_STEP_R1_C11_PARAM, 0.f, 10.f, 0.f, "Step CV");
		configParam(KNOB_STEP_R1_C12_PARAM, 0.f, 10.f, 0.f, "Step CV");
		configParam(KNOB_STEP_R1_C13_PARAM, 0.f, 10.f, 0.f, "Step CV");
		configParam(KNOB_STEP_R1_C14_PARAM, 0.f, 10.f, 0.f, "Step CV");
		configParam(KNOB_STEP_R1_C15_PARAM, 0.f, 10.f, 0.f, "Step CV");
		configParam(KNOB_STEP_R2_C0_PARAM, 0.f, 10.f, 0.f, "Step CV");
		configParam(KNOB_STEP_R2_C1_PARAM, 0.f, 10.f, 0.f, "Step CV");
		configParam(KNOB_STEP_R2_C2_PARAM, 0.f, 10.f, 0.f, "Step CV");
		configParam(KNOB_STEP_R2_C3_PARAM, 0.f, 10.f, 0.f, "Step CV");
		configParam(KNOB_STEP_R2_C4_PARAM, 0.f, 10.f, 0.f, "Step CV");
		configParam(KNOB_STEP_R2_C5_PARAM, 0.f, 10.f, 0.f, "Step CV");
		configParam(KNOB_STEP_R2_C6_PARAM, 0.f, 10.f, 0.f, "Step CV");
		configParam(KNOB_STEP_R2_C7_PARAM, 0.f, 10.f, 0.f, "Step CV");
		configParam(KNOB_STEP_R2_C8_PARAM, 0.f, 10.f, 0.f, "Step CV");
		configParam(KNOB_STEP_R2_C9_PARAM, 0.f, 10.f, 0.f, "Step CV");
		configParam(KNOB_STEP_R2_C10_PARAM, 0.f, 10.f, 0.f, "Step CV");
		configParam(KNOB_STEP_R2_C11_PARAM, 0.f, 10.f, 0.f, "Step CV");
		configParam(KNOB_STEP_R2_C12_PARAM, 0.f, 10.f, 0.f, "Step CV");
		configParam(KNOB_STEP_R2_C13_PARAM, 0.f, 10.f, 0.f, "Step CV");
		configParam(KNOB_STEP_R2_C14_PARAM, 0.f, 10.f, 0.f, "Step CV");
		configParam(KNOB_STEP_R2_C15_PARAM, 0.f, 10.f, 0.f, "Step CV");

		configSwitch(SWITCH_GATE_R0_C0_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R0_C1_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R0_C2_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R0_C3_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R0_C4_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R0_C5_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R0_C6_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R0_C7_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R0_C8_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R0_C9_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R0_C10_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R0_C11_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R0_C12_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R0_C13_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R0_C14_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R0_C15_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R1_C0_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R1_C1_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R1_C2_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R1_C3_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R1_C4_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R1_C5_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R1_C6_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R1_C7_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R1_C8_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R1_C9_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R1_C10_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R1_C11_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R1_C12_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R1_C13_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R1_C14_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R1_C15_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R2_C0_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R2_C1_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R2_C2_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R2_C3_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R2_C4_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R2_C5_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R2_C6_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R2_C7_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R2_C8_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R2_C9_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R2_C10_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R2_C11_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R2_C12_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R2_C13_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R2_C14_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R2_C15_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
	}

	// ****** Right click menu methods *******
	void randomizeGates() {
		for(int row = 0; row < 3; row++) {
			for(int col = 0; col < 16; col++) {
				params[getButtonId(row, col)].setValue(round(random::uniform()));
			}
		}
	}

    void randomizeCVKnobs() {
		for(int row = 0; row < 3; row++) {
			for(int col = 0; col < 16; col++) {
				params[getKnobId(row, col)].setValue(random::uniform() * 10);
			}
		}
	}

	void randomizeGatesForRow(short row) {
		for(int col = 0; col < 16; col++) {
			params[getButtonId(row, col)].setValue(round(random::uniform()));
		}
	}

    void randomizeCVKnobsForRow(short row) {
		for(int col = 0; col < 16; col++) {
			params[getKnobId(row, col)].setValue(random::uniform() * 10);
		}
	}
	// ****** End *******

	int clockDivideDisplayValueR0 = 0;
	int clockDivideDisplayValueR1 = 0;
	int clockDivideDisplayValueR2 = 0;

	dsp::Timer timer;
	float clockSpeed = 0.5f;
	dsp::PulseGenerator clockOutPulse;
	IgnoreClockAfterResetTimer ignoreClockAfterResetTimer;

	float lastclockVoltage = 0.0f;
	float lastResetInput = 0.0f;

	dsp::PulseGenerator gatePulseR0;
	dsp::PulseGenerator gatePulseR1;
	dsp::PulseGenerator gatePulseR2;

	SequelClockTracker clockTracker {16,3};

	bool gateTriggerModeEnabled = true;

	bool sampleAndHoldEnabled = false;

	bool shouldPulseThisStep(short row) {
		return params[getButtonId(row, clockTracker.getCurrentStepForRow(row))].getValue() > 0.5 && clockTracker.getHasPulsedThisStepForRow(row) == false;
	}

	void turnOffAllStepIndicatorLights() {
		for(int i = 0; i < 48; i++ ) {
			lights[i].setBrightness(0);
		}
	}

	short getLightId(short row, short column) {
		return column + (row*16);
	}

	short getKnobId(short row, short column) {
		return column + (row*16);
	}

	short getButtonId(short row, short column) {
		return column + (row*16) + 48;
	}

	void reset() {
		ignoreClockAfterResetTimer.resetTriggered();
	
		clockTracker.resetStepTrackers();
		clockTracker.resetGatesSinceLastStepTrackers();
		clockTracker.resetHasPulsedThisStepTrackers();

		if(shouldPulseThisStep(0)) {
			gatePulseR0.trigger(1e-3f);
			clockTracker.setHasPulsedThisStepForRow(0, true);
		}
		if(shouldPulseThisStep(1)) {
			gatePulseR1.trigger(1e-3f);
			clockTracker.setHasPulsedThisStepForRow(1, true);
		}
		if(shouldPulseThisStep(2)) {
			gatePulseR2.trigger(1e-3f);
			clockTracker.setHasPulsedThisStepForRow(2, true);
		}
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

	void handleGateButtonLeds() {
		for(int i = 0; i < 48; i++) {
			if(params[i + 48].getValue() > 0) {
				lights[i+48].setBrightness(0.5);
			} else {
				lights[i+48].setBrightness(0.0);
			}
		}
	}

	int mapClockDivideValues(int value) {
		switch(value) {
			case 1:
				return 1;
			case 2:
				return 2;
			case 3:
				return 3;
			case 4:
				return 4;
			case 5:
				return 6;
			case 6:
				return 8;
			case 7:
				return 16;
			case 8:
				return 32;
			case 9:
				return 48;
			case 10:
				return 64;
			default:
				return 1;
		}
	}
	
	// Sequel Save Expander handling
	const SequelSaveInterface cleanInterface;
	bool sequelSavePresent = false;
	
	void handleSequelSave() {
		SequelSaveInterface *messagesToSave= (SequelSaveInterface*)rightExpander.module->leftExpander.producerMessage;
		for(int i = 0; i < 3; i++) {
			for(int j = 0; j < 16; j++) {
				messagesToSave->knobVals[i][j] = params[getKnobId(i, j)].getValue();
				messagesToSave->switchVals[i][j] = params[getButtonId(i, j)].getValue() > 0 ? true : false;
			}
		}
		messagesToSave->clockDivideVals[0] = params[KNOB_TIME_DIVIDE_R0_PARAM].getValue();
		messagesToSave->clockDivideVals[1] = params[KNOB_TIME_DIVIDE_R1_PARAM].getValue();
		messagesToSave->clockDivideVals[2] = params[KNOB_TIME_DIVIDE_R2_PARAM].getValue();
		messagesToSave->speed = params[KNOB_CLOCK_SPEED_PARAM].getValue();
		messagesToSave->stepCount = params[KNOB_STEP_COUNT_PARAM].getValue();
		messagesToSave->triggerMode = params[SWITCH_GATE_MODE_PARAM].getValue() > 0;
		messagesToSave->isDirty = true;
		

		SequelSaveInterface *messagesFromSave = (SequelSaveInterface*)rightExpander.consumerMessage;
		if(messagesFromSave->isDirty) {
			for(int i = 0; i < 3; i++) {
				for(int j = 0; j < 16; j++) {
					params[getKnobId(i, j)].setValue(messagesFromSave->knobVals[i][j]);
					paramQuantities[getKnobId(i, j)]->setValue(messagesFromSave->knobVals[i][j]);
					params[getButtonId(i, j)].setValue(messagesFromSave->switchVals[i][j] ? 10.f : 0.f);
				}
			}
			params[KNOB_TIME_DIVIDE_R0_PARAM].setValue(messagesFromSave->clockDivideVals[0]);
			params[KNOB_TIME_DIVIDE_R1_PARAM].setValue(messagesFromSave->clockDivideVals[1]);
			params[KNOB_TIME_DIVIDE_R2_PARAM].setValue(messagesFromSave->clockDivideVals[2]);
			params[KNOB_CLOCK_SPEED_PARAM].setValue(messagesFromSave->speed);
			paramQuantities[KNOB_CLOCK_SPEED_PARAM]->setValue(messagesFromSave->speed);
			params[KNOB_STEP_COUNT_PARAM].setValue(messagesFromSave->stepCount);
			paramQuantities[KNOB_STEP_COUNT_PARAM]->setValue(messagesFromSave->stepCount);
			params[SWITCH_GATE_MODE_PARAM].setValue(messagesFromSave->triggerMode ? 1.f : 0.f);
		}
		*messagesFromSave = cleanInterface;
	}
	// end

	// used for sample and hold
	bool hasPulsedR0 = false;
	bool hasPulsedR1 = false;
	bool hasPulsedR2 = false;

	void process(const ProcessArgs& args) override {
		sequelSavePresent = (rightExpander.module && rightExpander.module->model == modelSequelSave);
		if(sequelSavePresent) {
			handleSequelSave();
		}

		clockTracker.divideTracker[0] = clockDivideDisplayValueR0 = mapClockDivideValues(round(params[KNOB_TIME_DIVIDE_R0_PARAM].getValue()));
		clockTracker.divideTracker[1] = clockDivideDisplayValueR1 = mapClockDivideValues(round(params[KNOB_TIME_DIVIDE_R1_PARAM].getValue()));
		clockTracker.divideTracker[2] = clockDivideDisplayValueR2 = mapClockDivideValues(round(params[KNOB_TIME_DIVIDE_R2_PARAM].getValue()));

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
			turnOffAllStepIndicatorLights();
			lights[LIGHT_GATE_MODE_TRIGGER_LIGHT].setBrightness(0);
			lights[LIGHT_GATE_MODE_CONTINUOUS_LIGHT].setBrightness(0);
			return;
		}

		float resetInput = inputs[IN_RESET_INPUT].getVoltage();
		if (lastResetInput == 0 && resetInput != 0) {
			reset();
		}

		if (lastclockVoltage == 0 && clockVoltage != 0 && !ignoreClockAfterResetTimer.shouldIgnore) {
			clockTracker.nextClock();
			if(shouldPulseThisStep(0)) {
				gatePulseR0.trigger(1e-3f);
				hasPulsedR0 = true;
				clockTracker.setHasPulsedThisStepForRow(0, true);
			}
			if(shouldPulseThisStep(1)) {
				gatePulseR1.trigger(1e-3f);
				hasPulsedR1 = true;
				clockTracker.setHasPulsedThisStepForRow(1, true);
			}
			if(shouldPulseThisStep(2)) {
				gatePulseR2.trigger(1e-3f);
				hasPulsedR2 = true;
				clockTracker.setHasPulsedThisStepForRow(2, true);
			}
		}

		// Handle step indicator lights
		turnOffAllStepIndicatorLights();
		lights[getLightId(0, clockTracker.getCurrentStepForRow(0))].setBrightness(1.0f);
		lights[getLightId(1, clockTracker.getCurrentStepForRow(1))].setBrightness(1.0f);
		lights[getLightId(2, clockTracker.getCurrentStepForRow(2))].setBrightness(1.0f);
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
		if(outputs[OUT_GATE_R0_OUTPUT].isConnected() && gateTriggerModeEnabled) {
			const bool pulseR0 = gatePulseR0.process(1.0 / args.sampleRate);
			outputs[OUT_GATE_R0_OUTPUT].setVoltage(pulseR0 ? 10.0 : 0.0);		
		}

		if(outputs[OUT_GATE_R1_OUTPUT].isConnected() && gateTriggerModeEnabled) {
			const bool pulseR1 = gatePulseR1.process(1.0 / args.sampleRate);
			outputs[OUT_GATE_R1_OUTPUT].setVoltage(pulseR1 ? 10.0 : 0.0);
		}

		if(outputs[OUT_GATE_R2_OUTPUT].isConnected() && gateTriggerModeEnabled) {
			const bool pulseR2 = gatePulseR2.process(1.0 / args.sampleRate);
			outputs[OUT_GATE_R2_OUTPUT].setVoltage(pulseR2 ? 10.0 : 0.0);
		}
		// End

		// Handle continuous gate outputs
		if(outputs[OUT_GATE_R0_OUTPUT].isConnected() && !gateTriggerModeEnabled) {
			const bool shouldGateR0 = params[getButtonId(0, clockTracker.getCurrentStepForRow(0))].getValue() > 0;
			outputs[OUT_GATE_R0_OUTPUT].setVoltage(shouldGateR0 ? 10.0 : 0.0);		
		}

		if(outputs[OUT_GATE_R1_OUTPUT].isConnected() && !gateTriggerModeEnabled) {
			const bool shouldGateR1 = params[getButtonId(0, clockTracker.getCurrentStepForRow(0))].getValue() > 0;
			outputs[OUT_GATE_R1_OUTPUT].setVoltage(shouldGateR1 ? 10.0 : 0.0);		
		}

		if(outputs[OUT_GATE_R2_OUTPUT].isConnected() && !gateTriggerModeEnabled) {
			const bool shouldGateR2 = params[getButtonId(0, clockTracker.getCurrentStepForRow(0))].getValue() > 0;
			outputs[OUT_GATE_R2_OUTPUT].setVoltage(shouldGateR2 ? 10.0 : 0.0);		
		}
		// End

		// Handle CV outputs
		if(outputs[OUT_CV_R0_OUTPUT].isConnected() && (!sampleAndHoldEnabled || (sampleAndHoldEnabled && hasPulsedR0))) {
			const float voltageOutputR0 = params[getKnobId(0, clockTracker.getCurrentStepForRow(0))].getValue();
			outputs[OUT_CV_R0_OUTPUT].setVoltage(voltageOutputR0);
		}
		if(outputs[OUT_CV_R1_OUTPUT].isConnected() && (!sampleAndHoldEnabled || (sampleAndHoldEnabled && hasPulsedR1))) {
			const float voltageOutputR1 = params[getKnobId(1, clockTracker.getCurrentStepForRow(1))].getValue();
			outputs[OUT_CV_R1_OUTPUT].setVoltage(voltageOutputR1);
		}
		if(outputs[OUT_CV_R2_OUTPUT].isConnected() && (!sampleAndHoldEnabled || (sampleAndHoldEnabled && hasPulsedR2))) {
			const float voltageOutputR2 = params[getKnobId(2, clockTracker.getCurrentStepForRow(2))].getValue();
			outputs[OUT_CV_R2_OUTPUT].setVoltage(voltageOutputR2);
		}
		// End
		lastclockVoltage = clockVoltage;
		lastResetInput = resetInput;
		hasPulsedR0 = false;
		hasPulsedR1 = false;
		hasPulsedR2 = false;
	}

	json_t *dataToJson() override {
		json_t *rootJ = json_object();
		json_object_set_new(rootJ, "sampleAndHoldEnabled", json_boolean(sampleAndHoldEnabled));
		return rootJ;
	}

	void dataFromJson(json_t *rootJ) override {
		json_t *sampleAndHoldEnabledJ = json_object_get(rootJ, "sampleAndHoldEnabled");
		if(sampleAndHoldEnabledJ) {
			sampleAndHoldEnabled = json_boolean_value(sampleAndHoldEnabledJ);
		}
	}
};


struct Sequel16Widget : ModuleWidget {
	Sequel16Widget(Sequel16* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/Sequel16.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<SteppedRedKnob>(mm2px(Vec(96.643, 16.145)), module, Sequel16::KNOB_STEP_COUNT_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(135.26, 16.145)), module, Sequel16::KNOB_CLOCK_SPEED_PARAM));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(77.334, 16.145)), module, Sequel16::IN_CLOCK_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(154.568, 16.145)), module, Sequel16::IN_RESET_INPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(115.951, 16.145)), module, Sequel16::OUT_CLOCK_OUTPUT));

		addParam(createParamCentered<SteppedRedKnob>(mm2px(Vec(12.224, 39.431)), module, Sequel16::KNOB_TIME_DIVIDE_R0_PARAM));
		addParam(createParamCentered<SteppedRedKnob>(mm2px(Vec(12.224, 69.329)), module, Sequel16::KNOB_TIME_DIVIDE_R1_PARAM));
		addParam(createParamCentered<SteppedRedKnob>(mm2px(Vec(12.224, 99.226)), module, Sequel16::KNOB_TIME_DIVIDE_R2_PARAM));

		addParam(createParamCentered<CKD6InvisibleLatch>(mm2px(Vec(173.877, 16.145)), module, Sequel16::SWITCH_GATE_MODE_PARAM));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(180.283, 11.551)), module, Sequel16::LIGHT_GATE_MODE_CONTINUOUS_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(180.283, 20.902)), module, Sequel16::LIGHT_GATE_MODE_TRIGGER_LIGHT));

		addParam(createParamCentered<RedKnob>(mm2px(Vec(38.717, 33.874)), module, Sequel16::KNOB_STEP_R0_C0_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(58.026, 33.874)), module, Sequel16::KNOB_STEP_R0_C1_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(77.334, 33.874)), module, Sequel16::KNOB_STEP_R0_C2_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(96.643, 33.874)), module, Sequel16::KNOB_STEP_R0_C3_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(115.951, 33.874)), module, Sequel16::KNOB_STEP_R0_C4_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(135.26, 33.874)), module, Sequel16::KNOB_STEP_R0_C5_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(154.568, 33.874)), module, Sequel16::KNOB_STEP_R0_C6_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(173.877, 33.874)), module, Sequel16::KNOB_STEP_R0_C7_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(193.185, 33.874)), module, Sequel16::KNOB_STEP_R0_C8_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(212.494, 33.874)), module, Sequel16::KNOB_STEP_R0_C9_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(231.802, 33.874)), module, Sequel16::KNOB_STEP_R0_C10_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(251.111, 33.874)), module, Sequel16::KNOB_STEP_R0_C11_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(270.42, 33.874)), module, Sequel16::KNOB_STEP_R0_C12_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(289.728, 33.874)), module, Sequel16::KNOB_STEP_R0_C13_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(309.037, 33.874)), module, Sequel16::KNOB_STEP_R0_C14_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(328.345, 33.874)), module, Sequel16::KNOB_STEP_R0_C15_PARAM));

		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(38.717, 44.987)), module, Sequel16::SWITCH_GATE_R0_C0_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(58.026, 44.987)), module, Sequel16::SWITCH_GATE_R0_C1_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(77.334, 44.987)), module, Sequel16::SWITCH_GATE_R0_C2_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(96.643, 44.987)), module, Sequel16::SWITCH_GATE_R0_C3_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(115.951, 44.987)), module, Sequel16::SWITCH_GATE_R0_C4_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(135.26, 44.987)), module, Sequel16::SWITCH_GATE_R0_C5_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(154.568, 44.987)), module, Sequel16::SWITCH_GATE_R0_C6_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(173.877, 44.987)), module, Sequel16::SWITCH_GATE_R0_C7_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(193.185, 44.987)), module, Sequel16::SWITCH_GATE_R0_C8_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(212.494, 44.987)), module, Sequel16::SWITCH_GATE_R0_C9_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(231.802, 44.987)), module, Sequel16::SWITCH_GATE_R0_C10_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(251.111, 44.987)), module, Sequel16::SWITCH_GATE_R0_C11_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(270.42, 44.987)), module, Sequel16::SWITCH_GATE_R0_C12_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(289.728, 44.987)), module, Sequel16::SWITCH_GATE_R0_C13_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(309.037, 44.987)), module, Sequel16::SWITCH_GATE_R0_C14_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(328.345, 44.987)), module, Sequel16::SWITCH_GATE_R0_C15_PARAM));

	    addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(38.717, 44.987)), module, Sequel16::GATE_LIGHT_R0_C0_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(58.026, 44.987)), module, Sequel16::GATE_LIGHT_R0_C1_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(77.334, 44.987)), module, Sequel16::GATE_LIGHT_R0_C2_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(96.643, 44.987)), module, Sequel16::GATE_LIGHT_R0_C3_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(115.422, 44.987)), module, Sequel16::GATE_LIGHT_R0_C4_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(135.26, 44.987)), module, Sequel16::GATE_LIGHT_R0_C5_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(154.568, 44.987)), module, Sequel16::GATE_LIGHT_R0_C6_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(173.877, 44.987)), module, Sequel16::GATE_LIGHT_R0_C7_LIGHT));
	    addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(193.185, 44.987)), module, Sequel16::GATE_LIGHT_R0_C8_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(212.494, 44.987)), module, Sequel16::GATE_LIGHT_R0_C9_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(231.802, 44.987)), module, Sequel16::GATE_LIGHT_R0_C10_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(251.111, 44.987)), module, Sequel16::GATE_LIGHT_R0_C11_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(270.42, 44.9877)), module, Sequel16::GATE_LIGHT_R0_C12_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(289.728, 44.987)), module, Sequel16::GATE_LIGHT_R0_C13_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(309.037, 44.987)), module, Sequel16::GATE_LIGHT_R0_C14_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(328.345, 44.987)), module, Sequel16::GATE_LIGHT_R0_C15_LIGHT));

		addParam(createParamCentered<RedKnob>(mm2px(Vec(38.717, 63.772)), module, Sequel16::KNOB_STEP_R1_C0_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(58.026, 63.772)), module, Sequel16::KNOB_STEP_R1_C1_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(77.334, 63.772)), module, Sequel16::KNOB_STEP_R1_C2_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(96.643, 63.772)), module, Sequel16::KNOB_STEP_R1_C3_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(115.951, 63.772)), module, Sequel16::KNOB_STEP_R1_C4_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(135.26, 63.772)), module, Sequel16::KNOB_STEP_R1_C5_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(154.568, 63.772)), module, Sequel16::KNOB_STEP_R1_C6_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(173.877, 63.772)), module, Sequel16::KNOB_STEP_R1_C7_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(193.185, 63.772)), module, Sequel16::KNOB_STEP_R1_C8_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(212.494, 63.772)), module, Sequel16::KNOB_STEP_R1_C9_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(231.802, 63.772)), module, Sequel16::KNOB_STEP_R1_C10_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(251.111, 63.772)), module, Sequel16::KNOB_STEP_R1_C11_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(270.42, 63.772)), module, Sequel16::KNOB_STEP_R1_C12_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(289.728, 63.772)), module, Sequel16::KNOB_STEP_R1_C13_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(309.037, 63.772)), module, Sequel16::KNOB_STEP_R1_C14_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(328.345, 63.772)), module, Sequel16::KNOB_STEP_R1_C15_PARAM));

		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(38.717, 74.885)), module, Sequel16::SWITCH_GATE_R1_C0_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(58.026, 74.885)), module, Sequel16::SWITCH_GATE_R1_C1_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(77.334, 74.885)), module, Sequel16::SWITCH_GATE_R1_C2_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(96.643, 74.885)), module, Sequel16::SWITCH_GATE_R1_C3_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(115.951, 74.885)), module, Sequel16::SWITCH_GATE_R1_C4_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(135.26, 74.885)), module, Sequel16::SWITCH_GATE_R1_C5_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(154.568, 74.885)), module, Sequel16::SWITCH_GATE_R1_C6_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(173.877, 74.885)), module, Sequel16::SWITCH_GATE_R1_C7_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(193.185, 74.885)), module, Sequel16::SWITCH_GATE_R1_C8_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(212.494, 74.885)), module, Sequel16::SWITCH_GATE_R1_C9_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(231.802, 74.885)), module, Sequel16::SWITCH_GATE_R1_C10_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(251.111, 74.885)), module, Sequel16::SWITCH_GATE_R1_C11_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(270.42, 74.885)), module, Sequel16::SWITCH_GATE_R1_C12_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(289.728, 74.885)), module, Sequel16::SWITCH_GATE_R1_C13_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(309.037, 74.885)), module, Sequel16::SWITCH_GATE_R1_C14_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(328.345, 74.885)), module, Sequel16::SWITCH_GATE_R1_C15_PARAM));

		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(38.717, 74.885)), module, Sequel16::GATE_LIGHT_R1_C0_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(58.026, 74.885)), module, Sequel16::GATE_LIGHT_R1_C1_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(77.334, 74.885)), module, Sequel16::GATE_LIGHT_R1_C2_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(96.643, 74.885)), module, Sequel16::GATE_LIGHT_R1_C3_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(115.422, 74.885)), module, Sequel16::GATE_LIGHT_R1_C4_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(135.26, 74.885)), module, Sequel16::GATE_LIGHT_R1_C5_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(154.568, 74.885)), module, Sequel16::GATE_LIGHT_R1_C6_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(173.877, 74.885)), module, Sequel16::GATE_LIGHT_R1_C7_LIGHT));
	    addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(193.185, 74.885)), module, Sequel16::GATE_LIGHT_R1_C8_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(212.494, 74.885)), module, Sequel16::GATE_LIGHT_R1_C9_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(231.802, 74.885)), module, Sequel16::GATE_LIGHT_R1_C10_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(251.111, 74.885)), module, Sequel16::GATE_LIGHT_R1_C11_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(270.42, 74.885)), module, Sequel16::GATE_LIGHT_R1_C12_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(289.728, 74.885)), module, Sequel16::GATE_LIGHT_R1_C13_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(309.037, 74.885)), module, Sequel16::GATE_LIGHT_R1_C14_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(328.345, 74.885)), module, Sequel16::GATE_LIGHT_R1_C15_LIGHT));

		addParam(createParamCentered<RedKnob>(mm2px(Vec(38.717, 93.67)), module, Sequel16::KNOB_STEP_R2_C0_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(58.026, 93.67)), module, Sequel16::KNOB_STEP_R2_C1_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(77.334, 93.67)), module, Sequel16::KNOB_STEP_R2_C2_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(96.643, 93.67)), module, Sequel16::KNOB_STEP_R2_C3_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(115.951, 93.67)), module, Sequel16::KNOB_STEP_R2_C4_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(135.26, 93.67)), module, Sequel16::KNOB_STEP_R2_C5_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(154.568, 93.67)), module, Sequel16::KNOB_STEP_R2_C6_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(173.877, 93.67)), module, Sequel16::KNOB_STEP_R2_C7_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(193.185, 93.67)), module, Sequel16::KNOB_STEP_R2_C8_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(212.494, 93.67)), module, Sequel16::KNOB_STEP_R2_C9_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(231.802, 93.67)), module, Sequel16::KNOB_STEP_R2_C10_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(251.111, 93.67)), module, Sequel16::KNOB_STEP_R2_C11_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(270.42, 93.67)), module, Sequel16::KNOB_STEP_R2_C12_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(289.728, 93.67)), module, Sequel16::KNOB_STEP_R2_C13_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(309.037, 93.67)), module, Sequel16::KNOB_STEP_R2_C14_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(328.345, 93.67)), module, Sequel16::KNOB_STEP_R2_C15_PARAM));
		
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(38.717, 104.783)), module, Sequel16::SWITCH_GATE_R2_C0_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(58.026, 104.783)), module, Sequel16::SWITCH_GATE_R2_C1_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(77.334, 104.783)), module, Sequel16::SWITCH_GATE_R2_C2_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(96.643, 104.783)), module, Sequel16::SWITCH_GATE_R2_C3_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(115.951, 104.783)), module, Sequel16::SWITCH_GATE_R2_C4_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(135.26, 104.783)), module, Sequel16::SWITCH_GATE_R2_C5_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(154.568, 104.783)), module, Sequel16::SWITCH_GATE_R2_C6_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(173.877, 104.783)), module, Sequel16::SWITCH_GATE_R2_C7_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(193.185, 104.783)), module, Sequel16::SWITCH_GATE_R2_C8_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(212.494, 104.783)), module, Sequel16::SWITCH_GATE_R2_C9_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(231.802, 104.783)), module, Sequel16::SWITCH_GATE_R2_C10_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(251.111, 104.783)), module, Sequel16::SWITCH_GATE_R2_C11_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(270.42, 104.783)), module, Sequel16::SWITCH_GATE_R2_C12_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(289.728, 104.783)), module, Sequel16::SWITCH_GATE_R2_C13_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(309.037, 104.783)), module, Sequel16::SWITCH_GATE_R2_C14_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(328.345, 104.783)), module, Sequel16::SWITCH_GATE_R2_C15_PARAM));

		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(38.717, 104.783)), module, Sequel16::GATE_LIGHT_R2_C0_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(58.026, 104.783)), module, Sequel16::GATE_LIGHT_R2_C1_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(77.334, 104.783)), module, Sequel16::GATE_LIGHT_R2_C2_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(96.643, 104.783)), module, Sequel16::GATE_LIGHT_R2_C3_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(115.422, 104.783)), module, Sequel16::GATE_LIGHT_R2_C4_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(135.26, 104.783)), module, Sequel16::GATE_LIGHT_R2_C5_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(154.568, 104.783)), module, Sequel16::GATE_LIGHT_R2_C6_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(173.877, 104.783)), module, Sequel16::GATE_LIGHT_R2_C7_LIGHT));
	    addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(193.185, 104.783)), module, Sequel16::GATE_LIGHT_R2_C8_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(212.494, 104.783)), module, Sequel16::GATE_LIGHT_R2_C9_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(231.802, 104.783)), module, Sequel16::GATE_LIGHT_R2_C10_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(251.111, 104.783)), module, Sequel16::GATE_LIGHT_R2_C11_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(270.42, 104.783)), module, Sequel16::GATE_LIGHT_R2_C12_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(289.728, 104.783)), module, Sequel16::GATE_LIGHT_R2_C13_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(309.037, 104.783)), module, Sequel16::GATE_LIGHT_R2_C14_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(328.345, 104.783)), module, Sequel16::GATE_LIGHT_R2_C15_LIGHT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(359.296, 33.591)), module, Sequel16::OUT_CV_R0_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(359.296, 44.704)), module, Sequel16::OUT_GATE_R0_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(359.297, 63.772)), module, Sequel16::OUT_CV_R1_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(359.297, 74.885)), module, Sequel16::OUT_GATE_R1_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(359.297, 93.67)), module, Sequel16::OUT_CV_R2_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(359.297, 104.783)), module, Sequel16::OUT_GATE_R2_OUTPUT));

		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(45.123, 29.28)), module, Sequel16::LIGHT_R0_C0_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(64.432, 29.28)), module, Sequel16::LIGHT_R0_C1_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(83.74, 29.28)), module, Sequel16::LIGHT_R0_C2_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(103.049, 29.28)), module, Sequel16::LIGHT_R0_C3_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(122.358, 29.28)), module, Sequel16::LIGHT_R0_C4_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(141.666, 29.28)), module, Sequel16::LIGHT_R0_C5_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(160.975, 29.28)), module, Sequel16::LIGHT_R0_C6_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(180.283, 29.28)), module, Sequel16::LIGHT_R0_C7_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(199.591, 29.28)), module, Sequel16::LIGHT_R0_C8_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(218.9, 29.28)), module, Sequel16::LIGHT_R0_C9_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(238.208, 29.28)), module, Sequel16::LIGHT_R0_C10_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(257.517, 29.28)), module, Sequel16::LIGHT_R0_C11_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(276.826, 29.28)), module, Sequel16::LIGHT_R0_C12_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(296.134, 29.28)), module, Sequel16::LIGHT_R0_C13_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(315.443, 29.28)), module, Sequel16::LIGHT_R0_C14_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(334.751, 29.28)), module, Sequel16::LIGHT_R0_C15_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(45.123, 59.178)), module, Sequel16::LIGHT_R1_C0_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(64.432, 59.178)), module, Sequel16::LIGHT_R1_C1_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(83.74, 59.178)), module, Sequel16::LIGHT_R1_C2_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(103.049, 59.178)), module, Sequel16::LIGHT_R1_C3_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(122.358, 59.178)), module, Sequel16::LIGHT_R1_C4_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(141.666, 59.178)), module, Sequel16::LIGHT_R1_C5_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(160.975, 59.178)), module, Sequel16::LIGHT_R1_C6_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(180.283, 59.178)), module, Sequel16::LIGHT_R1_C7_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(199.591, 59.178)), module, Sequel16::LIGHT_R1_C8_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(218.9, 59.178)), module, Sequel16::LIGHT_R1_C9_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(238.208, 59.178)), module, Sequel16::LIGHT_R1_C10_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(257.517, 59.178)), module, Sequel16::LIGHT_R1_C11_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(276.826, 59.178)), module, Sequel16::LIGHT_R1_C12_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(296.134, 59.178)), module, Sequel16::LIGHT_R1_C13_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(315.443, 59.178)), module, Sequel16::LIGHT_R1_C14_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(334.751, 59.178)), module, Sequel16::LIGHT_R1_C15_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(45.123, 89.076)), module, Sequel16::LIGHT_R2_C0_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(64.432, 89.076)), module, Sequel16::LIGHT_R2_C1_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(83.74, 89.076)), module, Sequel16::LIGHT_R2_C2_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(103.049, 89.076)), module, Sequel16::LIGHT_R2_C3_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(122.358, 89.076)), module, Sequel16::LIGHT_R2_C4_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(141.666, 89.076)), module, Sequel16::LIGHT_R2_C5_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(160.975, 89.076)), module, Sequel16::LIGHT_R2_C6_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(180.283, 89.076)), module, Sequel16::LIGHT_R2_C7_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(199.591, 89.076)), module, Sequel16::LIGHT_R2_C8_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(218.9, 89.076)), module, Sequel16::LIGHT_R2_C9_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(238.208, 89.076)), module, Sequel16::LIGHT_R2_C10_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(257.517, 89.076)), module, Sequel16::LIGHT_R2_C11_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(276.826, 89.076)), module, Sequel16::LIGHT_R2_C12_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(296.134, 89.076)), module, Sequel16::LIGHT_R2_C13_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(315.443, 89.076)), module, Sequel16::LIGHT_R2_C14_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(334.751, 89.076)), module, Sequel16::LIGHT_R2_C15_LIGHT));

		if(module) {
			DigitDisplay *clockDivideDisplayR0 = new DigitDisplay();
			clockDivideDisplayR0->box.pos = mm2px(Vec(19.5, 37));
			clockDivideDisplayR0->value = &module->clockDivideDisplayValueR0;
			addChild(clockDivideDisplayR0);

			DigitDisplay *clockDivideDisplayR1 = new DigitDisplay();
			clockDivideDisplayR1->box.pos = mm2px(Vec(19.5, 37 + 29.898));
			clockDivideDisplayR1->value = &module->clockDivideDisplayValueR1;
			addChild(clockDivideDisplayR1);

			DigitDisplay *clockDivideDisplayR2 = new DigitDisplay();
			clockDivideDisplayR2->box.pos = mm2px(Vec(19.5, 37 + 29.898 + 29.898));
			clockDivideDisplayR2->value = &module->clockDivideDisplayValueR2;
			addChild(clockDivideDisplayR2);
		}
	}

	void appendContextMenu(Menu* menu) override {
		Sequel16* module = dynamic_cast<Sequel16*>(this->module);

		menu->addChild(new MenuEntry);
		menu->addChild(createMenuLabel("Randomize"));

		struct RandomizeAllGates : MenuItem {
			Sequel16* module;
			void onAction(const event::Action &e) override {
				module->randomizeGates();
			}
		};

		struct RandomizeAllCVKnobs : MenuItem {
			Sequel16* module;
			void onAction(const event::Action &e) override {
				module->randomizeCVKnobs();
			}
		};

		struct RandomizeCVKnobsForRow : MenuItem {
			short row;
			Sequel16* module;
			void onAction(const event::Action &e) override {
				module->randomizeCVKnobsForRow(row);
			}
		};

		struct RandomizeGatesForRow : MenuItem {
			short row;
			Sequel16* module;
			void onAction(const event::Action &e) override {
				module->randomizeGatesForRow(row);
			}
		};

		struct ToggleSampleAndHold : MenuItem {
			Sequel16* module;
			void onAction(const event::Action &e) override {
				module->sampleAndHoldEnabled = !module->sampleAndHoldEnabled;
			}
		};

		RandomizeAllGates* randomizeAllGates = createMenuItem<RandomizeAllGates>("Randomize all gates");
		randomizeAllGates->module = module;
		RandomizeAllCVKnobs* randomizeAllCVKnobs = createMenuItem<RandomizeAllCVKnobs>("Randomize all CV knobs");
		randomizeAllCVKnobs->module = module;

		menu->addChild(randomizeAllCVKnobs);
		menu->addChild(randomizeAllGates);

		for(short row = 0; row < 3; row++) {
			menu->addChild(new MenuSeparator());

			RandomizeCVKnobsForRow* randomizeCVKnobsForRow = createMenuItem<RandomizeCVKnobsForRow>("Randomize CV knobs for row " + std::to_string(row + 1));
			randomizeCVKnobsForRow->row = row;
			randomizeCVKnobsForRow->module = module;

			RandomizeGatesForRow* randomizeGatesForRow = createMenuItem<RandomizeGatesForRow>("Randomize Gates for row " + std::to_string(row + 1));
			randomizeGatesForRow->row = row;
			randomizeGatesForRow->module = module;

			menu->addChild(randomizeCVKnobsForRow);
			menu->addChild(randomizeGatesForRow);
		}
		menu->addChild(new MenuSeparator());
		menu->addChild(createMenuLabel("Settings"));
		ToggleSampleAndHold* sampleAndHoldToggle = createMenuItem<ToggleSampleAndHold>("Sample and hold");
		sampleAndHoldToggle->rightText = CHECKMARK(module->sampleAndHoldEnabled);
		sampleAndHoldToggle->module = module;
		menu->addChild(sampleAndHoldToggle);
	}
};


Model* modelSequel16Module = createModel<Sequel16, Sequel16Widget>("Sequel16");
