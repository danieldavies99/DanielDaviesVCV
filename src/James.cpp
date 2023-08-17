#include "plugin.hpp"

struct James : Module {
	
	const int NUM_GATE_SWITCHES = 96;
	const int NUM_ROWS = 6;
	const int NUM_STEPS = 16;

	enum ParamId {
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
		SWITCH_GATE_R3_C0_PARAM,
		SWITCH_GATE_R3_C1_PARAM,
		SWITCH_GATE_R3_C2_PARAM,
		SWITCH_GATE_R3_C3_PARAM,
		SWITCH_GATE_R3_C4_PARAM,
		SWITCH_GATE_R3_C5_PARAM,
		SWITCH_GATE_R3_C6_PARAM,
		SWITCH_GATE_R3_C7_PARAM,
		SWITCH_GATE_R3_C8_PARAM,
		SWITCH_GATE_R3_C9_PARAM,
		SWITCH_GATE_R3_C10_PARAM,
		SWITCH_GATE_R3_C11_PARAM,
		SWITCH_GATE_R3_C12_PARAM,
		SWITCH_GATE_R3_C13_PARAM,
		SWITCH_GATE_R3_C14_PARAM,
		SWITCH_GATE_R3_C15_PARAM,
		SWITCH_GATE_R4_C0_PARAM,
		SWITCH_GATE_R4_C1_PARAM,
		SWITCH_GATE_R4_C2_PARAM,
		SWITCH_GATE_R4_C3_PARAM,
		SWITCH_GATE_R4_C4_PARAM,
		SWITCH_GATE_R4_C5_PARAM,
		SWITCH_GATE_R4_C6_PARAM,
		SWITCH_GATE_R4_C7_PARAM,
		SWITCH_GATE_R4_C8_PARAM,
		SWITCH_GATE_R4_C9_PARAM,
		SWITCH_GATE_R4_C10_PARAM,
		SWITCH_GATE_R4_C11_PARAM,
		SWITCH_GATE_R4_C12_PARAM,
		SWITCH_GATE_R4_C13_PARAM,
		SWITCH_GATE_R4_C14_PARAM,
		SWITCH_GATE_R4_C15_PARAM,
		SWITCH_GATE_R5_C0_PARAM,
		SWITCH_GATE_R5_C1_PARAM,
		SWITCH_GATE_R5_C2_PARAM,
		SWITCH_GATE_R5_C3_PARAM,
		SWITCH_GATE_R5_C4_PARAM,
		SWITCH_GATE_R5_C5_PARAM,
		SWITCH_GATE_R5_C6_PARAM,
		SWITCH_GATE_R5_C7_PARAM,
		SWITCH_GATE_R5_C8_PARAM,
		SWITCH_GATE_R5_C9_PARAM,
		SWITCH_GATE_R5_C10_PARAM,
		SWITCH_GATE_R5_C11_PARAM,
		SWITCH_GATE_R5_C12_PARAM,
		SWITCH_GATE_R5_C13_PARAM,
		SWITCH_GATE_R5_C14_PARAM,
		SWITCH_GATE_R5_C15_PARAM,
		KNOB_RUSH_R0_PARAM,
		KNOB_RUSH_R1_PARAM,
		KNOB_RUSH_R2_PARAM,
		KNOB_RUSH_R3_PARAM,
		KNOB_RUSH_R4_PARAM,
		KNOB_RUSH_R5_PARAM,
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
		GATE_LIGHT_R3_C0_LIGHT,
		GATE_LIGHT_R3_C1_LIGHT,
		GATE_LIGHT_R3_C2_LIGHT,
		GATE_LIGHT_R3_C3_LIGHT,
		GATE_LIGHT_R3_C4_LIGHT,
		GATE_LIGHT_R3_C5_LIGHT,
		GATE_LIGHT_R3_C6_LIGHT,
		GATE_LIGHT_R3_C7_LIGHT,
		GATE_LIGHT_R3_C8_LIGHT,
		GATE_LIGHT_R3_C9_LIGHT,
		GATE_LIGHT_R3_C10_LIGHT,
		GATE_LIGHT_R3_C11_LIGHT,
		GATE_LIGHT_R3_C12_LIGHT,
		GATE_LIGHT_R3_C13_LIGHT,
		GATE_LIGHT_R3_C14_LIGHT,
		GATE_LIGHT_R3_C15_LIGHT,
		GATE_LIGHT_R4_C0_LIGHT,
		GATE_LIGHT_R4_C1_LIGHT,
		GATE_LIGHT_R4_C2_LIGHT,
		GATE_LIGHT_R4_C3_LIGHT,
		GATE_LIGHT_R4_C4_LIGHT,
		GATE_LIGHT_R4_C5_LIGHT,
		GATE_LIGHT_R4_C6_LIGHT,
		GATE_LIGHT_R4_C7_LIGHT,
		GATE_LIGHT_R4_C8_LIGHT,
		GATE_LIGHT_R4_C9_LIGHT,
		GATE_LIGHT_R4_C10_LIGHT,
		GATE_LIGHT_R4_C11_LIGHT,
		GATE_LIGHT_R4_C12_LIGHT,
		GATE_LIGHT_R4_C13_LIGHT,
		GATE_LIGHT_R4_C14_LIGHT,
		GATE_LIGHT_R4_C15_LIGHT,
		GATE_LIGHT_R5_C0_LIGHT,
		GATE_LIGHT_R5_C1_LIGHT,
		GATE_LIGHT_R5_C2_LIGHT,
		GATE_LIGHT_R5_C3_LIGHT,
		GATE_LIGHT_R5_C4_LIGHT,
		GATE_LIGHT_R5_C5_LIGHT,
		GATE_LIGHT_R5_C6_LIGHT,
		GATE_LIGHT_R5_C7_LIGHT,
		GATE_LIGHT_R5_C8_LIGHT,
		GATE_LIGHT_R5_C9_LIGHT,
		GATE_LIGHT_R5_C10_LIGHT,
		GATE_LIGHT_R5_C11_LIGHT,
		GATE_LIGHT_R5_C12_LIGHT,
		GATE_LIGHT_R5_C13_LIGHT,
		GATE_LIGHT_R5_C14_LIGHT,
		GATE_LIGHT_R5_C15_LIGHT,
		LIGHT_STEP_INDICATOR_C0_LIGHT,
		LIGHT_STEP_INDICATOR_C1_LIGHT,
		LIGHT_STEP_INDICATOR_C2_LIGHT,
		LIGHT_STEP_INDICATOR_C3_LIGHT,
		LIGHT_STEP_INDICATOR_C4_LIGHT,
		LIGHT_STEP_INDICATOR_C5_LIGHT,
		LIGHT_STEP_INDICATOR_C6_LIGHT,
		LIGHT_STEP_INDICATOR_C7_LIGHT,
		LIGHT_STEP_INDICATOR_C8_LIGHT,
		LIGHT_STEP_INDICATOR_C9_LIGHT,
		LIGHT_STEP_INDICATOR_C10_LIGHT,
		LIGHT_STEP_INDICATOR_C11_LIGHT,
		LIGHT_STEP_INDICATOR_C12_LIGHT,
		LIGHT_STEP_INDICATOR_C13_LIGHT,
		LIGHT_STEP_INDICATOR_C14_LIGHT,
		LIGHT_STEP_INDICATOR_C15_LIGHT,
		LIGHT_GATE_MODE_CONTINUOUS_LIGHT,
		LIGHT_GATE_MODE_TRIGGER_LIGHT,
		LIGHTS_LEN
	};

	James() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(KNOB_STEP_COUNT_PARAM, 0.f, 16.f, 16.f, "Step count");
		configParam(KNOB_CLOCK_SPEED_PARAM, 0.f, 1.f, 0.5f, "Speed");
		configSwitch(SWITCH_GATE_MODE_PARAM, 0, 1, 1, "Gate Mode", {"Continuous", "Trigger"});

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
		configSwitch(SWITCH_GATE_R3_C0_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R3_C1_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R3_C2_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R3_C3_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R3_C4_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R3_C5_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R3_C6_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R3_C7_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R3_C8_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R3_C9_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R3_C10_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R3_C11_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R3_C12_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R3_C13_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R3_C14_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R3_C15_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R4_C0_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R4_C1_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R4_C2_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R4_C3_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R4_C4_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R4_C5_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R4_C6_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R4_C7_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R4_C8_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R4_C9_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R4_C10_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R4_C11_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R4_C12_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R4_C13_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R4_C14_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R4_C15_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R5_C0_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R5_C1_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R5_C2_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R5_C3_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R5_C4_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R5_C5_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R5_C6_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R5_C7_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R5_C8_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R5_C9_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R5_C10_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R5_C11_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R5_C12_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R5_C13_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R5_C14_PARAM, 0, 1, 0, "Gate", {"Off", "On"});
		configSwitch(SWITCH_GATE_R5_C15_PARAM, 0, 1, 0, "Gate", {"Off", "On"});

		configInput(IN_CLOCK_INPUT, "Clock");
		configInput(IN_RESET_INPUT, "Reset");
	
		configOutput(OUT_CLOCK_OUTPUT, "Clock");
	
		configOutput(OUT_GATE_R0_OUTPUT, "Row 1 gate");
		configOutput(OUT_GATE_R1_OUTPUT, "Row 2 gate");
		configOutput(OUT_GATE_R2_OUTPUT, "Row 3 gate");
		configOutput(OUT_GATE_R3_OUTPUT, "Row 4 gate");
		configOutput(OUT_GATE_R4_OUTPUT, "Row 5 gate");
		configOutput(OUT_GATE_R5_OUTPUT, "Row 6 gate");

		configParam(KNOB_RUSH_R0_PARAM, 15.f, -15.f, 0.f, "Rush / Drag");
		configParam(KNOB_RUSH_R1_PARAM, 15.f, -15.f, 0.f, "Rush / Drag");
		configParam(KNOB_RUSH_R2_PARAM, 15.f, -15.f, 0.f, "Rush / Drag");
		configParam(KNOB_RUSH_R3_PARAM, 15.f, -15.f, 0.f, "Rush / Drag");
		configParam(KNOB_RUSH_R4_PARAM, 15.f, -15.f, 0.f, "Rush / Drag");
		configParam(KNOB_RUSH_R5_PARAM, 15.f, -15.f, 0.f, "Rush / Drag");
	}

	short getStepLedId(short step) {
		return NUM_GATE_SWITCHES + step;
	}

	void turnOffAllStepIndicatorLights() {
		for(int i = 0; i < NUM_STEPS; i++) {
			lights[getStepLedId(i)].setBrightness(0.0);
		}
	}

	short getButtonId(short row, short column) {
		return column + (row*NUM_STEPS);
	}

	short getLightId(short row, short column) {
		return column + (row*NUM_STEPS);
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
	dsp::PulseGenerator clockOutPulse;
	IgnoreClockAfterResetTimer ignoreClockAfterResetTimer;

	float lastclockVoltage = 0.0f;
	float lastResetInput = 0.0f;

	dsp::PulseGenerator gatePulseGenerators [6] = { };

	JamesClockTracker clockTracker;

	bool gateTriggerModeEnabled = true;

	bool shouldPulseThisClock(short row) {
		// work out if should pulse based on current step - rush
		if(params[
			getButtonId(row, clockTracker.getCurrentStep())
		].getValue() > 0.5 && 
		clockTracker.getRushForRow(row) == clockTracker.getClocksSinceLastStep()) {
			return true;
		}

		// work out if should pulse based on next step - drag 
		if(params[
			getButtonId(row, clockTracker.getNextStep())
		].getValue() > 0.5 && clockTracker.getRushForRow(row) == -(clockTracker.globalClockDivide - clockTracker.getClocksSinceLastStep()) ) {
			return true;
		}
		return false;
	}

	float getInternalClockVoltage(float sampleRate) {
		float clockSpeedInvert = 1 - params[KNOB_CLOCK_SPEED_PARAM].getValue();

		const float minInterval = 0.003f;
		const float maxInterval = 0.08f;
		const float interval = minInterval + ((maxInterval - minInterval)*clockSpeedInvert);
		const float timeSinceLastPulsed = timer.process(1.0 / sampleRate);
		if(timeSinceLastPulsed > interval) {
			clockOutPulse.trigger(1e-3f);
			timer.reset();
		}
		bool shouldClockOutPulse = clockOutPulse.process(1.0 / sampleRate);
		return shouldClockOutPulse ? 10.0 : 0.0;
	}

	int getRushValForRow(short row) {
		return -static_cast<int>(params[NUM_GATE_SWITCHES + row].getValue());
	}

	void reset() {
		clockTracker.reset();
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
			turnOffAllStepIndicatorLights();
			lights[LIGHT_GATE_MODE_TRIGGER_LIGHT].setBrightness(0);
			lights[LIGHT_GATE_MODE_CONTINUOUS_LIGHT].setBrightness(0);
			return;
		}

		float resetInput = inputs[IN_RESET_INPUT].getVoltage();
		if (lastResetInput == 0 && resetInput != 0) {
			reset();
		}

		// set rush/drag values
		for(int i = 0; i < NUM_ROWS; i++) {
			clockTracker.setRushForRow(i, getRushValForRow(i));
		}

		// calculate if row should pulse
		if (lastclockVoltage == 0 && clockVoltage != 0 && !ignoreClockAfterResetTimer.shouldIgnore) {
			clockTracker.nextClock();
			for(int i = 0; i < NUM_ROWS; i++) {
				if(shouldPulseThisClock(i)) {
					gatePulseGenerators[i].trigger(1e-3f);
					clockTracker.setHasPulsedThisStepForRow(i, true);
				}
			}
		}

		// Handle step indicator lights
		turnOffAllStepIndicatorLights();
		lights[getStepLedId(clockTracker.getCurrentStep())].setBrightness(1.0f);
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

		addParam(createParamCentered<SteppedRedKnob>(mm2px(Vec(77.362, 16.145)), module, James::KNOB_STEP_COUNT_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(117.661, 16.145)), module, James::KNOB_CLOCK_SPEED_PARAM));

		addParam(createParamCentered<CKD6InvisibleLatch>(mm2px(Vec(157.961, 16.145)), module, James::SWITCH_GATE_MODE_PARAM));

		addParam(createParamCentered<SteppedRedKnob>(mm2px(Vec(13.135, 33.874)), module, James::KNOB_RUSH_R0_PARAM));
		addParam(createParamCentered<SteppedRedKnob>(mm2px(Vec(13.135, 48.056)), module, James::KNOB_RUSH_R1_PARAM));
		addParam(createParamCentered<SteppedRedKnob>(mm2px(Vec(13.135, 62.238)), module, James::KNOB_RUSH_R2_PARAM));
		addParam(createParamCentered<SteppedRedKnob>(mm2px(Vec(13.135, 76.419)), module, James::KNOB_RUSH_R3_PARAM));
		addParam(createParamCentered<SteppedRedKnob>(mm2px(Vec(13.135, 90.601)), module, James::KNOB_RUSH_R4_PARAM));
		addParam(createParamCentered<SteppedRedKnob>(mm2px(Vec(13.135, 104.783)), module, James::KNOB_RUSH_R5_PARAM));


		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(26.987, 33.867)), module, James::SWITCH_GATE_R0_C0_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(37.062, 33.867)), module, James::SWITCH_GATE_R0_C1_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(47.137, 33.867)), module, James::SWITCH_GATE_R0_C2_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(57.212, 33.867)), module, James::SWITCH_GATE_R0_C3_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(67.287, 33.867)), module, James::SWITCH_GATE_R0_C4_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(77.362, 33.867)), module, James::SWITCH_GATE_R0_C5_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(87.437, 33.867)), module, James::SWITCH_GATE_R0_C6_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(97.511, 33.867)), module, James::SWITCH_GATE_R0_C7_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(107.586, 33.867)), module, James::SWITCH_GATE_R0_C8_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(117.661, 33.867)), module, James::SWITCH_GATE_R0_C9_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(127.736, 33.867)), module, James::SWITCH_GATE_R0_C10_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(137.811, 33.867)), module, James::SWITCH_GATE_R0_C11_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(147.886, 33.867)), module, James::SWITCH_GATE_R0_C12_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(157.961, 33.867)), module, James::SWITCH_GATE_R0_C13_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(168.035, 33.867)), module, James::SWITCH_GATE_R0_C14_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(178.11, 33.867)), module, James::SWITCH_GATE_R0_C15_PARAM));

		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(26.987, 33.867)), module, James::GATE_LIGHT_R0_C0_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(37.062, 33.867)), module, James::GATE_LIGHT_R0_C1_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(47.137, 33.867)), module, James::GATE_LIGHT_R0_C2_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(57.212, 33.867)), module, James::GATE_LIGHT_R0_C3_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(67.287, 33.867)), module, James::GATE_LIGHT_R0_C4_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(77.362, 33.867)), module, James::GATE_LIGHT_R0_C5_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(87.437, 33.867)), module, James::GATE_LIGHT_R0_C6_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(97.511, 33.867)), module, James::GATE_LIGHT_R0_C7_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(107.586, 33.867)), module, James::GATE_LIGHT_R0_C8_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(117.661, 33.867)), module, James::GATE_LIGHT_R0_C9_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(127.736, 33.867)), module, James::GATE_LIGHT_R0_C10_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(137.811, 33.867)), module, James::GATE_LIGHT_R0_C11_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(147.886, 33.867)), module, James::GATE_LIGHT_R0_C12_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(157.961, 33.867)), module, James::GATE_LIGHT_R0_C13_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(168.035, 33.867)), module, James::GATE_LIGHT_R0_C14_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(178.11, 33.867)), module, James::GATE_LIGHT_R0_C15_LIGHT));

	
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(26.987, 48.056)), module, James::SWITCH_GATE_R1_C0_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(37.062, 48.056)), module, James::SWITCH_GATE_R1_C1_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(47.137, 48.056)), module, James::SWITCH_GATE_R1_C2_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(57.212, 48.056)), module, James::SWITCH_GATE_R1_C3_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(67.287, 48.056)), module, James::SWITCH_GATE_R1_C4_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(77.362, 48.056)), module, James::SWITCH_GATE_R1_C5_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(87.437, 48.056)), module, James::SWITCH_GATE_R1_C6_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(97.511, 48.056)), module, James::SWITCH_GATE_R1_C7_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(107.586, 48.056)), module, James::SWITCH_GATE_R1_C8_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(117.661, 48.056)), module, James::SWITCH_GATE_R1_C9_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(127.736, 48.056)), module, James::SWITCH_GATE_R1_C10_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(137.811, 48.056)), module, James::SWITCH_GATE_R1_C11_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(147.886, 48.056)), module, James::SWITCH_GATE_R1_C12_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(157.961, 48.056)), module, James::SWITCH_GATE_R1_C13_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(168.035, 48.056)), module, James::SWITCH_GATE_R1_C14_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(178.11, 48.056)), module, James::SWITCH_GATE_R1_C15_PARAM));

		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(26.987, 48.056)), module, James::GATE_LIGHT_R1_C0_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(37.062, 48.056)), module, James::GATE_LIGHT_R1_C1_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(47.137, 48.056)), module, James::GATE_LIGHT_R1_C2_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(57.212, 48.056)), module, James::GATE_LIGHT_R1_C3_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(67.287, 48.056)), module, James::GATE_LIGHT_R1_C4_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(77.362, 48.056)), module, James::GATE_LIGHT_R1_C5_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(87.437, 48.056)), module, James::GATE_LIGHT_R1_C6_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(97.511, 48.056)), module, James::GATE_LIGHT_R1_C7_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(107.586, 48.056)), module, James::GATE_LIGHT_R1_C8_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(117.661, 48.056)), module, James::GATE_LIGHT_R1_C9_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(127.736, 48.056)), module, James::GATE_LIGHT_R1_C10_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(137.811, 48.056)), module, James::GATE_LIGHT_R1_C11_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(147.886, 48.056)), module, James::GATE_LIGHT_R1_C12_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(157.961, 48.056)), module, James::GATE_LIGHT_R1_C13_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(168.035, 48.056)), module, James::GATE_LIGHT_R1_C14_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(178.11, 48.056)), module, James::GATE_LIGHT_R1_C15_LIGHT));

	
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(26.987, 62.238)), module, James::SWITCH_GATE_R2_C0_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(37.062, 62.238)), module, James::SWITCH_GATE_R2_C1_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(47.137, 62.238)), module, James::SWITCH_GATE_R2_C2_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(57.212, 62.238)), module, James::SWITCH_GATE_R2_C3_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(67.287, 62.238)), module, James::SWITCH_GATE_R2_C4_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(77.362, 62.238)), module, James::SWITCH_GATE_R2_C5_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(87.437, 62.238)), module, James::SWITCH_GATE_R2_C6_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(97.511, 62.238)), module, James::SWITCH_GATE_R2_C7_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(107.586, 62.238)), module, James::SWITCH_GATE_R2_C8_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(117.661, 62.238)), module, James::SWITCH_GATE_R2_C9_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(127.736, 62.238)), module, James::SWITCH_GATE_R2_C10_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(137.811, 62.238)), module, James::SWITCH_GATE_R2_C11_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(147.886, 62.238)), module, James::SWITCH_GATE_R2_C12_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(157.961, 62.238)), module, James::SWITCH_GATE_R2_C13_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(168.035, 62.238)), module, James::SWITCH_GATE_R2_C14_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(178.11, 62.238)), module, James::SWITCH_GATE_R2_C15_PARAM));

		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(26.987, 62.238)), module, James::GATE_LIGHT_R2_C0_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(37.062, 62.238)), module, James::GATE_LIGHT_R2_C1_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(47.137, 62.238)), module, James::GATE_LIGHT_R2_C2_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(57.212, 62.238)), module, James::GATE_LIGHT_R2_C3_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(67.287, 62.238)), module, James::GATE_LIGHT_R2_C4_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(77.362, 62.238)), module, James::GATE_LIGHT_R2_C5_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(87.437, 62.238)), module, James::GATE_LIGHT_R2_C6_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(97.511, 62.238)), module, James::GATE_LIGHT_R2_C7_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(107.586, 62.238)), module, James::GATE_LIGHT_R2_C8_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(117.661, 62.238)), module, James::GATE_LIGHT_R2_C9_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(127.736, 62.238)), module, James::GATE_LIGHT_R2_C10_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(137.811, 62.238)), module, James::GATE_LIGHT_R2_C11_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(147.886, 62.238)), module, James::GATE_LIGHT_R2_C12_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(157.961, 62.238)), module, James::GATE_LIGHT_R2_C13_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(168.035, 62.238)), module, James::GATE_LIGHT_R2_C14_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(178.11, 62.238)), module, James::GATE_LIGHT_R2_C15_LIGHT));


		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(26.987, 76.419)), module, James::SWITCH_GATE_R3_C0_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(37.062, 76.419)), module, James::SWITCH_GATE_R3_C1_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(47.137, 76.419)), module, James::SWITCH_GATE_R3_C2_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(57.212, 76.419)), module, James::SWITCH_GATE_R3_C3_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(67.287, 76.419)), module, James::SWITCH_GATE_R3_C4_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(77.362, 76.419)), module, James::SWITCH_GATE_R3_C5_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(87.437, 76.419)), module, James::SWITCH_GATE_R3_C6_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(97.511, 76.419)), module, James::SWITCH_GATE_R3_C7_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(107.586, 76.419)), module, James::SWITCH_GATE_R3_C8_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(117.661, 76.419)), module, James::SWITCH_GATE_R3_C9_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(127.736, 76.419)), module, James::SWITCH_GATE_R3_C10_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(137.811, 76.419)), module, James::SWITCH_GATE_R3_C11_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(147.886, 76.419)), module, James::SWITCH_GATE_R3_C12_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(157.961, 76.419)), module, James::SWITCH_GATE_R3_C13_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(168.035, 76.419)), module, James::SWITCH_GATE_R3_C14_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(178.11, 76.419)), module, James::SWITCH_GATE_R3_C15_PARAM));

		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(26.987, 76.419)), module, James::GATE_LIGHT_R3_C0_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(37.062, 76.419)), module, James::GATE_LIGHT_R3_C1_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(47.137, 76.419)), module, James::GATE_LIGHT_R3_C2_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(57.212, 76.419)), module, James::GATE_LIGHT_R3_C3_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(67.287, 76.419)), module, James::GATE_LIGHT_R3_C4_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(77.362, 76.419)), module, James::GATE_LIGHT_R3_C5_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(87.437, 76.419)), module, James::GATE_LIGHT_R3_C6_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(97.511, 76.419)), module, James::GATE_LIGHT_R3_C7_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(107.586, 76.419)), module, James::GATE_LIGHT_R3_C8_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(117.661, 76.419)), module, James::GATE_LIGHT_R3_C9_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(127.736, 76.419)), module, James::GATE_LIGHT_R3_C10_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(137.811, 76.419)), module, James::GATE_LIGHT_R3_C11_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(147.886, 76.419)), module, James::GATE_LIGHT_R3_C12_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(157.961, 76.419)), module, James::GATE_LIGHT_R3_C13_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(168.035, 76.419)), module, James::GATE_LIGHT_R3_C14_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(178.11, 76.419)), module, James::GATE_LIGHT_R3_C15_LIGHT));


		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(26.987, 90.601)), module, James::SWITCH_GATE_R4_C0_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(37.062, 90.601)), module, James::SWITCH_GATE_R4_C1_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(46.873, 90.601)), module, James::SWITCH_GATE_R4_C2_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(57.212, 90.601)), module, James::SWITCH_GATE_R4_C3_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(67.287, 90.601)), module, James::SWITCH_GATE_R4_C4_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(77.362, 90.601)), module, James::SWITCH_GATE_R4_C5_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(87.437, 90.601)), module, James::SWITCH_GATE_R4_C6_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(97.511, 90.601)), module, James::SWITCH_GATE_R4_C7_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(107.586, 90.601)), module, James::SWITCH_GATE_R4_C8_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(117.661, 90.601)), module, James::SWITCH_GATE_R4_C9_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(127.736, 90.601)), module, James::SWITCH_GATE_R4_C10_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(137.811, 90.601)), module, James::SWITCH_GATE_R4_C11_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(147.886, 90.601)), module, James::SWITCH_GATE_R4_C12_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(157.961, 90.601)), module, James::SWITCH_GATE_R4_C13_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(168.035, 90.601)), module, James::SWITCH_GATE_R4_C14_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(178.11, 90.601)), module, James::SWITCH_GATE_R4_C15_PARAM));

		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(26.987, 90.601)), module, James::GATE_LIGHT_R4_C0_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(37.062, 90.601)), module, James::GATE_LIGHT_R4_C1_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(46.873, 90.601)), module, James::GATE_LIGHT_R4_C2_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(57.212, 90.601)), module, James::GATE_LIGHT_R4_C3_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(67.287, 90.601)), module, James::GATE_LIGHT_R4_C4_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(77.362, 90.601)), module, James::GATE_LIGHT_R4_C5_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(87.437, 90.601)), module, James::GATE_LIGHT_R4_C6_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(97.511, 90.601)), module, James::GATE_LIGHT_R4_C7_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(107.586, 90.601)), module, James::GATE_LIGHT_R4_C8_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(117.661, 90.601)), module, James::GATE_LIGHT_R4_C9_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(127.736, 90.601)), module, James::GATE_LIGHT_R4_C10_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(137.811, 90.601)), module, James::GATE_LIGHT_R4_C11_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(147.886, 90.601)), module, James::GATE_LIGHT_R4_C12_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(157.961, 90.601)), module, James::GATE_LIGHT_R4_C13_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(168.035, 90.601)), module, James::GATE_LIGHT_R4_C14_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(178.11, 90.601)), module, James::GATE_LIGHT_R4_C15_LIGHT));


		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(26.987, 104.783)), module, James::SWITCH_GATE_R5_C0_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(37.062, 104.783)), module, James::SWITCH_GATE_R5_C1_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(47.137, 104.783)), module, James::SWITCH_GATE_R5_C2_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(57.212, 104.783)), module, James::SWITCH_GATE_R5_C3_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(67.287, 104.783)), module, James::SWITCH_GATE_R5_C4_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(77.362, 104.783)), module, James::SWITCH_GATE_R5_C5_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(87.437, 104.783)), module, James::SWITCH_GATE_R5_C6_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(97.511, 104.783)), module, James::SWITCH_GATE_R5_C7_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(107.586, 104.783)), module, James::SWITCH_GATE_R5_C8_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(117.661, 104.783)), module, James::SWITCH_GATE_R5_C9_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(127.736, 104.783)), module, James::SWITCH_GATE_R5_C10_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(137.811, 104.783)), module, James::SWITCH_GATE_R5_C11_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(147.886, 104.783)), module, James::SWITCH_GATE_R5_C12_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(157.961, 104.783)), module, James::SWITCH_GATE_R5_C13_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(168.035, 104.783)), module, James::SWITCH_GATE_R5_C14_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(178.11, 104.783)), module, James::SWITCH_GATE_R5_C15_PARAM));

		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(26.987, 104.783)), module, James::GATE_LIGHT_R5_C0_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(37.062, 104.783)), module, James::GATE_LIGHT_R5_C1_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(47.137, 104.783)), module, James::GATE_LIGHT_R5_C2_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(57.212, 104.783)), module, James::GATE_LIGHT_R5_C3_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(67.287, 104.783)), module, James::GATE_LIGHT_R5_C4_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(77.362, 104.783)), module, James::GATE_LIGHT_R5_C5_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(87.437, 104.783)), module, James::GATE_LIGHT_R5_C6_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(97.511, 104.783)), module, James::GATE_LIGHT_R5_C7_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(107.586, 104.783)), module, James::GATE_LIGHT_R5_C8_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(117.661, 104.783)), module, James::GATE_LIGHT_R5_C9_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(127.736, 104.783)), module, James::GATE_LIGHT_R5_C10_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(137.811, 104.783)), module, James::GATE_LIGHT_R5_C11_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(147.886, 104.783)), module, James::GATE_LIGHT_R5_C12_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(157.961, 104.783)), module, James::GATE_LIGHT_R5_C13_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(168.035, 104.783)), module, James::GATE_LIGHT_R5_C14_LIGHT));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(178.11, 104.783)), module, James::GATE_LIGHT_R5_C15_LIGHT));


		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(57.212, 16.145)), module, James::IN_CLOCK_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(137.811, 16.145)), module, James::IN_RESET_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(97.511, 16.145)), module, James::OUT_CLOCK_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(201.628, 33.874)), module, James::OUT_GATE_R0_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(201.628, 48.056)), module, James::OUT_GATE_R1_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(201.628, 62.238)), module, James::OUT_GATE_R2_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(201.628, 76.419)), module, James::OUT_GATE_R3_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(201.628, 90.601)), module, James::OUT_GATE_R4_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(201.628, 104.783)), module, James::OUT_GATE_R5_OUTPUT));

		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(164.679, 11.551)), module, James::LIGHT_GATE_MODE_CONTINUOUS_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(164.679, 20.902)), module, James::LIGHT_GATE_MODE_TRIGGER_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(26.987, 114.3)), module, James::LIGHT_STEP_INDICATOR_C0_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(37.062, 114.3)), module, James::LIGHT_STEP_INDICATOR_C1_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(47.137, 114.3)), module, James::LIGHT_STEP_INDICATOR_C2_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(57.212, 114.3)), module, James::LIGHT_STEP_INDICATOR_C3_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(67.287, 114.3)), module, James::LIGHT_STEP_INDICATOR_C4_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(77.362, 114.3)), module, James::LIGHT_STEP_INDICATOR_C5_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(87.437, 114.3)), module, James::LIGHT_STEP_INDICATOR_C6_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(97.511, 114.3)), module, James::LIGHT_STEP_INDICATOR_C7_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(107.586, 114.3)), module, James::LIGHT_STEP_INDICATOR_C8_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(117.661, 114.3)), module, James::LIGHT_STEP_INDICATOR_C9_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(127.736, 114.3)), module, James::LIGHT_STEP_INDICATOR_C10_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(137.811, 114.3)), module, James::LIGHT_STEP_INDICATOR_C11_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(147.886, 114.3)), module, James::LIGHT_STEP_INDICATOR_C12_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(157.961, 114.3)), module, James::LIGHT_STEP_INDICATOR_C13_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(168.035, 114.3)), module, James::LIGHT_STEP_INDICATOR_C14_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(178.11, 114.3)), module, James::LIGHT_STEP_INDICATOR_C15_LIGHT));
	}
};


Model* modelJames = createModel<James, JamesWidget>("James");