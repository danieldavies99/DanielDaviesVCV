#include "plugin.hpp"


struct EnvyModule : Module {
	enum ParamId {
		SLIDER_ATK_PARAM,
		SLIDER_DEC_PARAM,
		SLIDER_SUS_PARAM,
		SLIDER_REL_PARAM,
		KNOB_RAND_ATK_PARAM,
		KNOB_RAND_DEC_PARAM,
		KNOB_RAND_SUS_PARAM,
		KNOB_RAND_REL_PARAM,
		KNOB_MOD_ATK_PARAM,
		KNOB_MOD_DEC_PARAM,
		KNOB_MOD_SUS_PARAM,
		KNOB_MOD_REL_PARAM,
		SWITCH_LOOP_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		SYNC_IN_INPUT,
		BEND_IN_INPUT,
		FREQUENCY_MODULATION_IN_INPUT,
		AMPLITUDE_MODULATION_IN_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		GATE_IN_OUTPUT,
		RETRIG_IN_OUTPUT,
		ENV_OUT_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};

	EnvyModule() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(SLIDER_ATK_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SLIDER_DEC_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SLIDER_SUS_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SLIDER_REL_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_RAND_ATK_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_RAND_DEC_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_RAND_SUS_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_RAND_REL_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_MOD_ATK_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_MOD_DEC_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_MOD_SUS_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_MOD_REL_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_LOOP_PARAM, 0.f, 1.f, 0.f, "");
		configInput(SYNC_IN_INPUT, "");
		configInput(BEND_IN_INPUT, "");
		configInput(FREQUENCY_MODULATION_IN_INPUT, "");
		configInput(AMPLITUDE_MODULATION_IN_INPUT, "");
		configOutput(GATE_IN_OUTPUT, "");
		configOutput(RETRIG_IN_OUTPUT, "");
		configOutput(ENV_OUT_OUTPUT, "");
	}

	void process(const ProcessArgs& args) override {
	}
};


struct EnvyModuleWidget : ModuleWidget {
	EnvyModuleWidget(EnvyModule* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/Envy.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RedSliderMediumVertical>(mm2px(Vec(10.407, 40.818)), module, EnvyModule::SLIDER_ATK_PARAM));
		addParam(createParamCentered<RedSliderMediumVertical>(mm2px(Vec(25.577, 40.818)), module, EnvyModule::SLIDER_DEC_PARAM));
		addParam(createParamCentered<RedSliderMediumVertical>(mm2px(Vec(40.748, 40.818)), module, EnvyModule::SLIDER_SUS_PARAM));
		addParam(createParamCentered<RedSliderMediumVertical>(mm2px(Vec(55.919, 40.818)), module, EnvyModule::SLIDER_REL_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(10.407, 66.103)), module, EnvyModule::KNOB_RAND_ATK_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(25.577, 66.103)), module, EnvyModule::KNOB_RAND_DEC_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(40.748, 66.103)), module, EnvyModule::KNOB_RAND_SUS_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(55.919, 66.103)), module, EnvyModule::KNOB_RAND_REL_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(10.407, 83.008)), module, EnvyModule::KNOB_MOD_ATK_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(25.577, 83.008)), module, EnvyModule::KNOB_MOD_DEC_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(40.748, 83.008)), module, EnvyModule::KNOB_MOD_SUS_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(55.919, 83.008)), module, EnvyModule::KNOB_MOD_REL_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(10.407, 110.457)), module, EnvyModule::SWITCH_LOOP_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(10.407, 94.148)), module, EnvyModule::SYNC_IN_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(25.577, 94.148)), module, EnvyModule::BEND_IN_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(40.748, 94.148)), module, EnvyModule::FREQUENCY_MODULATION_IN_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(55.919, 94.002)), module, EnvyModule::AMPLITUDE_MODULATION_IN_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(25.577, 110.457)), module, EnvyModule::GATE_IN_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(40.748, 110.457)), module, EnvyModule::RETRIG_IN_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(55.919, 110.457)), module, EnvyModule::ENV_OUT_OUTPUT));
	}
};


Model* modelEnvyModule = createModel<EnvyModule, EnvyModuleWidget>("EnvyModule");