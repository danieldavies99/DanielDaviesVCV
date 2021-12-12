#include "plugin.hpp"


struct Sequel16 : Module {
	enum ParamId {
		KNOB_STEP_COUNT_PARAM,
		KNOB_CLOCK_SPEED_PARAM,
		SWITCH_GATE_MODE_PARAM,
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
		KNOB_TIME_DIVIDE_R0_PARAM,
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
		KNOB_TIME_DIVIDE_R1_PARAM,
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
		KNOB_TIME_DIVIDE_R2_PARAM,
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
		LIGHT_GATE_MODE_CONTINOUS_LIGHT,
		LIGHT_GATE_MODE_TRIGGER_LIGHT,
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
		LIGHTS_LEN
	};

	Sequel16() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(KNOB_STEP_COUNT_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_CLOCK_SPEED_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_MODE_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_STEP_R0_C0_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_STEP_R0_C1_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_STEP_R0_C2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_STEP_R0_C3_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_STEP_R0_C4_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_STEP_R0_C5_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_STEP_R0_C6_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_STEP_R0_C7_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_STEP_R0_C8_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_STEP_R0_C9_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_STEP_R0_C10_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_STEP_R0_C11_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_STEP_R0_C12_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_STEP_R0_C13_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_STEP_R0_C14_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_STEP_R0_C15_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_TIME_DIVIDE_R0_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R0_C0_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R0_C1_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R0_C2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R0_C3_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R0_C4_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R0_C5_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R0_C6_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R0_C7_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R0_C8_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R0_C9_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R0_C10_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R0_C11_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R0_C12_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R0_C13_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R0_C14_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R0_C15_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_STEP_R1_C0_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_STEP_R1_C1_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_STEP_R1_C2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_STEP_R1_C3_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_STEP_R1_C4_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_STEP_R1_C5_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_STEP_R1_C6_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_STEP_R1_C7_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_STEP_R1_C8_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_STEP_R1_C9_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_STEP_R1_C10_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_STEP_R1_C11_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_STEP_R1_C12_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_STEP_R1_C13_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_STEP_R1_C14_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_STEP_R1_C15_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_TIME_DIVIDE_R1_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R1_C0_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R1_C1_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R1_C2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R1_C3_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R1_C4_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R1_C5_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R1_C6_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R1_C7_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R1_C8_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R1_C9_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R1_C10_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R1_C11_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R1_C12_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R1_C13_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R1_C14_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R1_C15_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_STEP_R2_C0_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_STEP_R2_C1_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_STEP_R2_C2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_STEP_R2_C3_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_STEP_R2_C4_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_STEP_R2_C5_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_STEP_R2_C6_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_STEP_R2_C7_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_STEP_R2_C8_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_STEP_R2_C9_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_STEP_R2_C10_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_STEP_R2_C11_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_STEP_R2_C12_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_STEP_R2_C13_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_STEP_R2_C14_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_STEP_R2_C15_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_TIME_DIVIDE_R2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R2_C0_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R2_C1_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R2_C2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R2_C3_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R2_C4_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R2_C5_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R2_C6_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R2_C7_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R2_C8_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R2_C9_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R2_C10_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R2_C11_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R2_C12_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R2_C13_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R2_C14_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_GATE_R2_C15_PARAM, 0.f, 1.f, 0.f, "");
		configInput(IN_CLOCK_INPUT, "");
		configInput(IN_RESET_INPUT, "");
		configOutput(OUT_CLOCK_OUTPUT, "");
		configOutput(OUT_CV_R0_OUTPUT, "");
		configOutput(OUT_GATE_R0_OUTPUT, "");
		configOutput(OUT_CV_R1_OUTPUT, "");
		configOutput(OUT_GATE_R1_OUTPUT, "");
		configOutput(OUT_CV_R2_OUTPUT, "");
		configOutput(OUT_GATE_R2_OUTPUT, "");
	}

	void process(const ProcessArgs& args) override {
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

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(96.643, 16.145)), module, Sequel16::KNOB_STEP_COUNT_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(135.26, 16.145)), module, Sequel16::KNOB_CLOCK_SPEED_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(173.877, 16.145)), module, Sequel16::SWITCH_GATE_MODE_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(38.717, 33.874)), module, Sequel16::KNOB_STEP_R0_C0_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(58.026, 33.874)), module, Sequel16::KNOB_STEP_R0_C1_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(77.334, 33.874)), module, Sequel16::KNOB_STEP_R0_C2_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(96.643, 33.874)), module, Sequel16::KNOB_STEP_R0_C3_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(115.951, 33.874)), module, Sequel16::KNOB_STEP_R0_C4_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(135.26, 33.874)), module, Sequel16::KNOB_STEP_R0_C5_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(154.568, 33.874)), module, Sequel16::KNOB_STEP_R0_C6_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(173.877, 33.874)), module, Sequel16::KNOB_STEP_R0_C7_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(193.185, 33.874)), module, Sequel16::KNOB_STEP_R0_C8_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(212.494, 33.874)), module, Sequel16::KNOB_STEP_R0_C9_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(231.802, 33.874)), module, Sequel16::KNOB_STEP_R0_C10_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(251.111, 33.874)), module, Sequel16::KNOB_STEP_R0_C11_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(270.42, 33.874)), module, Sequel16::KNOB_STEP_R0_C12_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(289.728, 33.874)), module, Sequel16::KNOB_STEP_R0_C13_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(309.037, 33.874)), module, Sequel16::KNOB_STEP_R0_C14_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(328.345, 33.874)), module, Sequel16::KNOB_STEP_R0_C15_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(12.224, 39.431)), module, Sequel16::KNOB_TIME_DIVIDE_R0_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(38.717, 44.987)), module, Sequel16::SWITCH_GATE_R0_C0_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(58.026, 44.987)), module, Sequel16::SWITCH_GATE_R0_C1_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(77.334, 44.987)), module, Sequel16::SWITCH_GATE_R0_C2_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(96.643, 44.987)), module, Sequel16::SWITCH_GATE_R0_C3_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(115.951, 44.987)), module, Sequel16::SWITCH_GATE_R0_C4_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(135.26, 44.987)), module, Sequel16::SWITCH_GATE_R0_C5_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(154.568, 44.987)), module, Sequel16::SWITCH_GATE_R0_C6_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(173.877, 44.987)), module, Sequel16::SWITCH_GATE_R0_C7_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(193.185, 44.987)), module, Sequel16::SWITCH_GATE_R0_C8_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(212.494, 44.987)), module, Sequel16::SWITCH_GATE_R0_C9_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(231.802, 44.987)), module, Sequel16::SWITCH_GATE_R0_C10_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(251.111, 44.987)), module, Sequel16::SWITCH_GATE_R0_C11_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(270.42, 44.987)), module, Sequel16::SWITCH_GATE_R0_C12_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(289.728, 44.987)), module, Sequel16::SWITCH_GATE_R0_C13_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(309.037, 44.987)), module, Sequel16::SWITCH_GATE_R0_C14_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(328.345, 44.987)), module, Sequel16::SWITCH_GATE_R0_C15_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(38.717, 63.772)), module, Sequel16::KNOB_STEP_R1_C0_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(58.026, 63.772)), module, Sequel16::KNOB_STEP_R1_C1_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(77.334, 63.772)), module, Sequel16::KNOB_STEP_R1_C2_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(96.643, 63.772)), module, Sequel16::KNOB_STEP_R1_C3_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(115.951, 63.772)), module, Sequel16::KNOB_STEP_R1_C4_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(135.26, 63.772)), module, Sequel16::KNOB_STEP_R1_C5_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(154.568, 63.772)), module, Sequel16::KNOB_STEP_R1_C6_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(173.877, 63.772)), module, Sequel16::KNOB_STEP_R1_C7_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(193.185, 63.772)), module, Sequel16::KNOB_STEP_R1_C8_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(212.494, 63.772)), module, Sequel16::KNOB_STEP_R1_C9_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(231.802, 63.772)), module, Sequel16::KNOB_STEP_R1_C10_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(251.111, 63.772)), module, Sequel16::KNOB_STEP_R1_C11_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(270.42, 63.772)), module, Sequel16::KNOB_STEP_R1_C12_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(289.728, 63.772)), module, Sequel16::KNOB_STEP_R1_C13_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(309.037, 63.772)), module, Sequel16::KNOB_STEP_R1_C14_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(328.345, 63.772)), module, Sequel16::KNOB_STEP_R1_C15_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(12.224, 69.329)), module, Sequel16::KNOB_TIME_DIVIDE_R1_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(38.717, 74.885)), module, Sequel16::SWITCH_GATE_R1_C0_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(58.026, 74.885)), module, Sequel16::SWITCH_GATE_R1_C1_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(77.334, 74.885)), module, Sequel16::SWITCH_GATE_R1_C2_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(96.643, 74.885)), module, Sequel16::SWITCH_GATE_R1_C3_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(115.951, 74.885)), module, Sequel16::SWITCH_GATE_R1_C4_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(135.26, 74.885)), module, Sequel16::SWITCH_GATE_R1_C5_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(154.568, 74.885)), module, Sequel16::SWITCH_GATE_R1_C6_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(173.877, 74.885)), module, Sequel16::SWITCH_GATE_R1_C7_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(193.185, 74.885)), module, Sequel16::SWITCH_GATE_R1_C8_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(212.494, 74.885)), module, Sequel16::SWITCH_GATE_R1_C9_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(231.802, 74.885)), module, Sequel16::SWITCH_GATE_R1_C10_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(251.111, 74.885)), module, Sequel16::SWITCH_GATE_R1_C11_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(270.42, 74.885)), module, Sequel16::SWITCH_GATE_R1_C12_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(289.728, 74.885)), module, Sequel16::SWITCH_GATE_R1_C13_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(309.037, 74.885)), module, Sequel16::SWITCH_GATE_R1_C14_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(328.345, 74.885)), module, Sequel16::SWITCH_GATE_R1_C15_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(38.717, 93.67)), module, Sequel16::KNOB_STEP_R2_C0_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(58.026, 93.67)), module, Sequel16::KNOB_STEP_R2_C1_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(77.334, 93.67)), module, Sequel16::KNOB_STEP_R2_C2_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(96.643, 93.67)), module, Sequel16::KNOB_STEP_R2_C3_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(115.951, 93.67)), module, Sequel16::KNOB_STEP_R2_C4_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(135.26, 93.67)), module, Sequel16::KNOB_STEP_R2_C5_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(154.568, 93.67)), module, Sequel16::KNOB_STEP_R2_C6_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(173.877, 93.67)), module, Sequel16::KNOB_STEP_R2_C7_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(193.185, 93.67)), module, Sequel16::KNOB_STEP_R2_C8_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(212.494, 93.67)), module, Sequel16::KNOB_STEP_R2_C9_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(231.802, 93.67)), module, Sequel16::KNOB_STEP_R2_C10_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(251.111, 93.67)), module, Sequel16::KNOB_STEP_R2_C11_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(270.42, 93.67)), module, Sequel16::KNOB_STEP_R2_C12_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(289.728, 93.67)), module, Sequel16::KNOB_STEP_R2_C13_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(309.037, 93.67)), module, Sequel16::KNOB_STEP_R2_C14_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(328.345, 93.67)), module, Sequel16::KNOB_STEP_R2_C15_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(12.224, 99.226)), module, Sequel16::KNOB_TIME_DIVIDE_R2_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(38.717, 104.783)), module, Sequel16::SWITCH_GATE_R2_C0_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(58.026, 104.783)), module, Sequel16::SWITCH_GATE_R2_C1_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(77.334, 104.783)), module, Sequel16::SWITCH_GATE_R2_C2_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(96.643, 104.783)), module, Sequel16::SWITCH_GATE_R2_C3_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(115.951, 104.783)), module, Sequel16::SWITCH_GATE_R2_C4_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(135.26, 104.783)), module, Sequel16::SWITCH_GATE_R2_C5_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(154.568, 104.783)), module, Sequel16::SWITCH_GATE_R2_C6_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(173.877, 104.783)), module, Sequel16::SWITCH_GATE_R2_C7_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(193.185, 104.783)), module, Sequel16::SWITCH_GATE_R2_C8_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(212.494, 104.783)), module, Sequel16::SWITCH_GATE_R2_C9_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(231.802, 104.783)), module, Sequel16::SWITCH_GATE_R2_C10_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(251.111, 104.783)), module, Sequel16::SWITCH_GATE_R2_C11_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(270.42, 104.783)), module, Sequel16::SWITCH_GATE_R2_C12_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(289.728, 104.783)), module, Sequel16::SWITCH_GATE_R2_C13_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(309.037, 104.783)), module, Sequel16::SWITCH_GATE_R2_C14_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(328.345, 104.783)), module, Sequel16::SWITCH_GATE_R2_C15_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(77.334, 16.145)), module, Sequel16::IN_CLOCK_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(154.568, 16.145)), module, Sequel16::IN_RESET_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(115.951, 16.145)), module, Sequel16::OUT_CLOCK_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(359.296, 33.591)), module, Sequel16::OUT_CV_R0_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(359.296, 44.704)), module, Sequel16::OUT_GATE_R0_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(359.297, 63.772)), module, Sequel16::OUT_CV_R1_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(359.297, 74.885)), module, Sequel16::OUT_GATE_R1_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(359.297, 93.67)), module, Sequel16::OUT_CV_R2_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(359.297, 104.783)), module, Sequel16::OUT_GATE_R2_OUTPUT));

		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(180.283, 11.551)), module, Sequel16::LIGHT_GATE_MODE_CONTINOUS_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(180.283, 20.902)), module, Sequel16::LIGHT_GATE_MODE_TRIGGER_LIGHT));
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
	}
};


Model* modelSequel16 = createModel<Sequel16, Sequel16Widget>("Sequel16");