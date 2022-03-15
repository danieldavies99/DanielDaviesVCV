#include "plugin.hpp"


struct SequelSaveModule : Module {
	enum ParamId {
		SWITCH_SAVE_0_PARAM,
		SWITCH_LOAD_0_PARAM,
		SWITCH_SAVE_1_PARAM,
		SWITCH_LOAD_1_PARAM,
		SWITCH_SAVE_2_PARAM,
		SWITCH_LOAD_2_PARAM,
		SWITCH_SAVE_3_PARAM,
		SWITCH_LOAD_3_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		IN_SAVE_0_INPUT,
		IN_LOAD_0_INPUT,
		IN_SAVE_1_INPUT,
		IN_LOAD_1_INPUT,
		IN_SAVE_2_INPUT,
		IN_LOAD_2_INPUT,
		IN_SAVE_3_INPUT,
		IN_LOAD_3_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};

	SequelSaveInterface leftMessages[2];// messages from mother (first index is page), see enum called AuxFromMotherIds in MixerCommon.hpp

	SequelSaveModule() {
		leftExpander.producerMessage = &leftMessages[0];
		leftExpander.consumerMessage = &leftMessages[1];

		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(SWITCH_SAVE_0_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_LOAD_0_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_SAVE_1_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_LOAD_1_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_SAVE_2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_LOAD_2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_SAVE_3_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWITCH_LOAD_3_PARAM, 0.f, 1.f, 0.f, "");
		configInput(IN_SAVE_0_INPUT, "");
		configInput(IN_LOAD_0_INPUT, "");
		configInput(IN_SAVE_1_INPUT, "");
		configInput(IN_LOAD_1_INPUT, "");
		configInput(IN_SAVE_2_INPUT, "");
		configInput(IN_LOAD_2_INPUT, "");
		configInput(IN_SAVE_3_INPUT, "");
		configInput(IN_LOAD_3_INPUT, "");
	}

	double lastSaveButton0Val = 0;
	double lastSaveButton1Val = 0;
	double lastSaveButton2Val = 0;
	double lastSaveButton3Val = 0;

	double lastLoadButton0Val = 0;
	double lastLoadButton1Val = 0;
	double lastLoadButton2Val = 0;
	double lastLoadButton3Val = 0;

	double lastSaveInput0 = 0;
	double lastSaveInput1 = 0;
	double lastSaveInput2 = 0;
	double lastSaveInput3 = 0;

	double lastLoadInput0 = 0;
	double lastLoadInput1 = 0;
	double lastLoadInput2 = 0;
	double lastLoadInput3 = 0;

	int selectedSaveRow = 0;
	bool sequelPresent = false;

	const SequelSaveInterface cleanInterface;

	SequelSaveInterface sequelSaveStateRow0;
	SequelSaveInterface sequelSaveStateRow1;
	SequelSaveInterface sequelSaveStateRow2;
	SequelSaveInterface sequelSaveStateRow3;

	void process(const ProcessArgs& args) override {
		sequelPresent = leftExpander.module && (leftExpander.module->model == modelSequel8Module || leftExpander.module->model == modelSequel16Module);

		double saveButton0Val = params[SWITCH_SAVE_0_PARAM].getValue();
		double saveButton1Val = params[SWITCH_SAVE_1_PARAM].getValue();
		double saveButton2Val = params[SWITCH_SAVE_2_PARAM].getValue();
		double saveButton3Val = params[SWITCH_SAVE_3_PARAM].getValue();

		double loadButton0Val = params[SWITCH_LOAD_0_PARAM].getValue();
		double loadButton1Val = params[SWITCH_LOAD_1_PARAM].getValue();
		double loadButton2Val = params[SWITCH_LOAD_2_PARAM].getValue();
		double loadButton3Val = params[SWITCH_LOAD_3_PARAM].getValue();

		double saveInput0Val = inputs[IN_SAVE_0_INPUT].getVoltage();
		double saveInput1Val = inputs[IN_SAVE_1_INPUT].getVoltage();
		double saveInput2Val = inputs[IN_SAVE_2_INPUT].getVoltage();
		double saveInput3Val = inputs[IN_SAVE_3_INPUT].getVoltage();

		double loadInput0Val = inputs[IN_LOAD_0_INPUT].getVoltage();
		double loadInput1Val = inputs[IN_LOAD_1_INPUT].getVoltage();
		double loadInput2Val = inputs[IN_LOAD_2_INPUT].getVoltage();
		double loadInput3Val = inputs[IN_LOAD_3_INPUT].getVoltage();

		SequelSaveInterface *messagesFromMother = (SequelSaveInterface*)leftExpander.consumerMessage;

		if(sequelPresent) {
			if((saveButton0Val > 0 && lastSaveButton0Val == 0) || (saveInput0Val > 0 && lastSaveInput0 == 0)) { // requesting mother
				selectedSaveRow = 0;
				leftExpander.messageFlipRequested = true;
			}
			if((saveButton1Val > 0 && lastSaveButton1Val == 0) || (saveInput1Val > 0 && lastSaveInput1 == 0)) { // requesting mother
				selectedSaveRow = 1;
				leftExpander.messageFlipRequested = true;
			}
			if((saveButton2Val > 0 && lastSaveButton2Val == 0) || (saveInput2Val > 0 && lastSaveInput2 == 0)) { // requesting mother
				selectedSaveRow = 2;
				leftExpander.messageFlipRequested = true;
			}
			if((saveButton3Val > 0 && lastSaveButton3Val == 0) || (saveInput3Val > 0 && lastSaveInput3 == 0)) { // requesting mother
				selectedSaveRow = 3;
				leftExpander.messageFlipRequested = true;
			}

			if(messagesFromMother->isDirty) { // info received from mother
				switch(selectedSaveRow) {
					case 0:
						sequelSaveStateRow0 = *messagesFromMother;
						break;
					case 1:
						sequelSaveStateRow1 = *messagesFromMother;
						break;
					case 2:
						sequelSaveStateRow2 = *messagesFromMother;
						break;
					case 3:
						sequelSaveStateRow3 = *messagesFromMother;
					break;
				}

			}
			*messagesFromMother = cleanInterface;

			if((loadButton0Val > 0 && lastLoadButton0Val == 0) || (loadInput0Val > 0 && lastLoadInput0 == 0)) { // sending saved info to mother
				SequelSaveInterface *messagesToMother = (SequelSaveInterface*)leftExpander.module->rightExpander.producerMessage;
				*messagesToMother = sequelSaveStateRow0;
				messagesToMother->isDirty = true;
				leftExpander.module->rightExpander.messageFlipRequested = true;
			}
			if((loadButton1Val > 0 && lastLoadButton1Val == 0) || (loadInput1Val > 0 && lastLoadInput1 == 0)) { // sending saved info to mother
				SequelSaveInterface *messagesToMother = (SequelSaveInterface*)leftExpander.module->rightExpander.producerMessage;
				*messagesToMother = sequelSaveStateRow1;
				messagesToMother->isDirty = true;
				leftExpander.module->rightExpander.messageFlipRequested = true;
			}
			if((loadButton2Val > 0 && lastLoadButton2Val == 0) || (loadInput2Val > 0 && lastLoadInput2 == 0)) { // sending saved info to mother
				SequelSaveInterface *messagesToMother = (SequelSaveInterface*)leftExpander.module->rightExpander.producerMessage;
				*messagesToMother = sequelSaveStateRow2;
				messagesToMother->isDirty = true;
				leftExpander.module->rightExpander.messageFlipRequested = true;
			}
			if((loadButton3Val > 0 && lastLoadButton3Val == 0) || (loadInput3Val > 0 && lastLoadInput3 == 0)) { // sending saved info to mother
				SequelSaveInterface *messagesToMother = (SequelSaveInterface*)leftExpander.module->rightExpander.producerMessage;
				*messagesToMother = sequelSaveStateRow3;
				messagesToMother->isDirty = true;
				leftExpander.module->rightExpander.messageFlipRequested = true;
			}
		}

		lastSaveButton0Val = saveButton0Val;
		lastSaveButton1Val = saveButton1Val;
		lastSaveButton2Val = saveButton2Val;
		lastSaveButton3Val = saveButton3Val;

		lastLoadButton0Val = loadButton0Val;
		lastLoadButton1Val = loadButton1Val;
		lastLoadButton2Val = loadButton2Val;
		lastLoadButton3Val = loadButton3Val;

		lastSaveInput0 = saveInput0Val;
		lastSaveInput1 = saveInput1Val;
		lastSaveInput2 = saveInput2Val;
		lastSaveInput3 = saveInput3Val;

		lastLoadInput0 = loadInput0Val;
		lastLoadInput1 = loadInput1Val;
		lastLoadInput2 = loadInput2Val;
		lastLoadInput3 = loadInput3Val;

	}

	json_t* getJsonKnobsForRow(SequelSaveInterface sequelSaveStateRow) {
		json_t *knobs = json_array();
		for(int i = 0; i < 3; i++) {
			json_t *newKnobRow = json_array();
			for(int j = 0; j < 16; j++) {
				json_array_append(newKnobRow, json_real(sequelSaveStateRow.knobVals[i][j]));
			}
			json_array_append(knobs, newKnobRow);
		}
		return knobs;
	}

	json_t* getJsonSwitchesForRow(SequelSaveInterface sequelSaveStateRow) {
		json_t *switches = json_array();
		for(int i = 0; i < 3; i++) {
			json_t *newSwitchRow = json_array();
			for(int j = 0; j < 16; j++) {
				json_array_append(newSwitchRow, json_boolean(sequelSaveStateRow.switchVals[i][j]));
			}
			json_array_append(switches, newSwitchRow);
		}
		return switches;
	}

	json_t* getJsonClockDivideValsForRow(SequelSaveInterface sequelSaveStateRow) {
		json_t *clockDivideVals = json_array();
		for(int i = 0; i < 3; i++) {
			json_array_append(clockDivideVals, json_real(sequelSaveStateRow.clockDivideVals[i]));
		}
		return clockDivideVals;
	}

	json_t *dataToJson() override {
		json_t *rootJ = json_object();

		json_object_set_new(rootJ, "knobsRow0", getJsonKnobsForRow(sequelSaveStateRow0));
		json_object_set_new(rootJ, "switchesRow0", getJsonSwitchesForRow(sequelSaveStateRow0));
		json_object_set_new(rootJ, "clockDivideValsRow0", getJsonClockDivideValsForRow(sequelSaveStateRow0));
		json_object_set_new(rootJ, "speedValRow0", json_real(sequelSaveStateRow0.speed));
		json_object_set_new(rootJ, "stepCountValRow0", json_integer(sequelSaveStateRow0.stepCount));
		json_object_set_new(rootJ, "triggerModeValRow0", json_boolean(sequelSaveStateRow0.triggerMode));

		json_object_set_new(rootJ, "knobsRow1", getJsonKnobsForRow(sequelSaveStateRow1));
		json_object_set_new(rootJ, "switchesRow1", getJsonSwitchesForRow(sequelSaveStateRow1));
		json_object_set_new(rootJ, "clockDivideValsRow1", getJsonClockDivideValsForRow(sequelSaveStateRow1));
		json_object_set_new(rootJ, "speedValRow1", json_real(sequelSaveStateRow1.speed));
		json_object_set_new(rootJ, "stepCountValRow1", json_integer(sequelSaveStateRow1.stepCount));
		json_object_set_new(rootJ, "triggerModeValRow1", json_boolean(sequelSaveStateRow1.triggerMode));

		json_object_set_new(rootJ, "knobsRow2", getJsonKnobsForRow(sequelSaveStateRow2));
		json_object_set_new(rootJ, "switchesRow2", getJsonSwitchesForRow(sequelSaveStateRow2));
		json_object_set_new(rootJ, "clockDivideValsRow2", getJsonClockDivideValsForRow(sequelSaveStateRow2));
		json_object_set_new(rootJ, "speedValRow2", json_real(sequelSaveStateRow2.speed));
		json_object_set_new(rootJ, "stepCountValRow2", json_integer(sequelSaveStateRow2.stepCount));
		json_object_set_new(rootJ, "triggerModeValRow2", json_boolean(sequelSaveStateRow2.triggerMode));

		json_object_set_new(rootJ, "knobsRow3", getJsonKnobsForRow(sequelSaveStateRow3));
		json_object_set_new(rootJ, "switchesRow3", getJsonSwitchesForRow(sequelSaveStateRow3));
		json_object_set_new(rootJ, "clockDivideValsRow3", getJsonClockDivideValsForRow(sequelSaveStateRow3));
		json_object_set_new(rootJ, "speedValRow3", json_real(sequelSaveStateRow3.speed));
		json_object_set_new(rootJ, "stepCountValRow3", json_integer(sequelSaveStateRow3.stepCount));
		json_object_set_new(rootJ, "triggerModeValRow3", json_boolean(sequelSaveStateRow3.triggerMode));
		return rootJ;
	}

	void loadKnobsFromJson(json_t *knobs, SequelSaveInterface &sequelSaveStateRow) {
		for(int i = 0; i < 3; i++) {
			for(int j = 0; j < 16; j++) {
				sequelSaveStateRow.knobVals[i][j] = json_real_value(json_array_get(json_array_get(knobs, i), j));
			}
		}
	}

	void loadSwitchesFromJson(json_t *switches, SequelSaveInterface &sequelSaveStateRow) {
		for(int i = 0; i < 3; i++) {
			for(int j = 0; j < 16; j++) {
				sequelSaveStateRow.switchVals[i][j] = json_boolean_value(json_array_get(json_array_get(switches, i), j)) ? 10.f : 0.f;
			}
		}
	}

	void loadClockDivideValsFromJson(json_t *clockDivideVals, SequelSaveInterface &sequelSaveStateRow) {
		for(int i = 0; i < 3; i++) {
			sequelSaveStateRow.clockDivideVals[i] = json_real_value(json_array_get(clockDivideVals, i));
		}
	}

	void dataFromJson(json_t *rootJ) override { // TO DO refactor this bullshit
		json_t *knobsRow0 = json_object_get(rootJ, "knobsRow0");
		json_t *switchesRow0 = json_object_get(rootJ, "switchesRow0");
		json_t *clockDivideValsRow0 = json_object_get(rootJ, "clockDivideValsRow0");
		if(knobsRow0 && switchesRow0 && clockDivideValsRow0) {
			loadKnobsFromJson(knobsRow0, sequelSaveStateRow0);
			loadSwitchesFromJson(switchesRow0, sequelSaveStateRow0);
			loadClockDivideValsFromJson(clockDivideValsRow0, sequelSaveStateRow0);
			sequelSaveStateRow0.speed = json_real_value(json_object_get(rootJ, "speedValRow0"));
			sequelSaveStateRow0.stepCount = json_integer_value(json_object_get(rootJ, "stepCountValRow0"));
			sequelSaveStateRow0.triggerMode = json_boolean_value(json_object_get(rootJ, "triggerModeValRow0"));
		}

		json_t *knobsRow1 = json_object_get(rootJ, "knobsRow1");
		json_t *switchesRow1 = json_object_get(rootJ, "switchesRow1");
		json_t *clockDivideValsRow1 = json_object_get(rootJ, "clockDivideValsRow1");
		if(knobsRow1 && switchesRow1 && clockDivideValsRow1) {
			loadKnobsFromJson(knobsRow1, sequelSaveStateRow1);
			loadSwitchesFromJson(switchesRow1, sequelSaveStateRow1);
			loadClockDivideValsFromJson(clockDivideValsRow1, sequelSaveStateRow1);
			sequelSaveStateRow1.speed = json_real_value(json_object_get(rootJ, "speedValRow1"));
			sequelSaveStateRow1.stepCount = json_integer_value(json_object_get(rootJ, "stepCountValRow1"));
			sequelSaveStateRow1.triggerMode = json_boolean_value(json_object_get(rootJ, "triggerModeValRow1"));
		}

		json_t *knobsRow2 = json_object_get(rootJ, "knobsRow2");
		json_t *switchesRow2 = json_object_get(rootJ, "switchesRow2");
		json_t *clockDivideValsRow2 = json_object_get(rootJ, "clockDivideValsRow2");
		if(knobsRow2 && switchesRow2 && clockDivideValsRow2) {
			loadKnobsFromJson(knobsRow2, sequelSaveStateRow2);
			loadSwitchesFromJson(switchesRow2, sequelSaveStateRow2);
			loadClockDivideValsFromJson(clockDivideValsRow2, sequelSaveStateRow2);
			sequelSaveStateRow2.speed = json_real_value(json_object_get(rootJ, "speedValRow2"));
			sequelSaveStateRow2.stepCount = json_integer_value(json_object_get(rootJ, "stepCountValRow2"));
			sequelSaveStateRow2.triggerMode = json_boolean_value(json_object_get(rootJ, "triggerModeValRow2"));
		}

		json_t *knobsRow3 = json_object_get(rootJ, "knobsRow3");
		json_t *switchesRow3 = json_object_get(rootJ, "switchesRow3");
		json_t *clockDivideValsRow3 = json_object_get(rootJ, "clockDivideValsRow3");
		if(knobsRow3 && switchesRow3 && clockDivideValsRow3) {
			loadKnobsFromJson(knobsRow3, sequelSaveStateRow3);
			loadSwitchesFromJson(switchesRow3, sequelSaveStateRow3);
			loadClockDivideValsFromJson(clockDivideValsRow3, sequelSaveStateRow3);
			sequelSaveStateRow3.speed = json_real_value(json_object_get(rootJ, "speedValRow3"));
			sequelSaveStateRow3.stepCount = json_integer_value(json_object_get(rootJ, "stepCountValRow3"));
			sequelSaveStateRow3.triggerMode = json_boolean_value(json_object_get(rootJ, "triggerModeValRow3"));
		}
	}
};


struct SequelSaveModuleWidget : ModuleWidget {
	SequelSaveModuleWidget(SequelSaveModule* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/SequelSave.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<CKD6>(mm2px(Vec(8.13, 39.665)), module, SequelSaveModule::SWITCH_SAVE_0_PARAM));
		addParam(createParamCentered<CKD6>(mm2px(Vec(41.317, 39.665)), module, SequelSaveModule::SWITCH_LOAD_0_PARAM));
		addParam(createParamCentered<CKD6>(mm2px(Vec(8.13, 60.487)), module, SequelSaveModule::SWITCH_SAVE_1_PARAM));
		addParam(createParamCentered<CKD6>(mm2px(Vec(41.317, 60.487)), module, SequelSaveModule::SWITCH_LOAD_1_PARAM));
		addParam(createParamCentered<CKD6>(mm2px(Vec(8.13, 81.309)), module, SequelSaveModule::SWITCH_SAVE_2_PARAM));
		addParam(createParamCentered<CKD6>(mm2px(Vec(41.317, 81.31)), module, SequelSaveModule::SWITCH_LOAD_2_PARAM));
		addParam(createParamCentered<CKD6>(mm2px(Vec(8.13, 102.132)), module, SequelSaveModule::SWITCH_SAVE_3_PARAM));
		addParam(createParamCentered<CKD6>(mm2px(Vec(41.317, 102.132)), module, SequelSaveModule::SWITCH_LOAD_3_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(24.723, 39.665)), module, SequelSaveModule::IN_SAVE_0_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(57.91, 39.665)), module, SequelSaveModule::IN_LOAD_0_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(24.723, 60.487)), module, SequelSaveModule::IN_SAVE_1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(57.91, 60.487)), module, SequelSaveModule::IN_LOAD_1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(24.723, 81.309)), module, SequelSaveModule::IN_SAVE_2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(57.91, 81.31)), module, SequelSaveModule::IN_LOAD_2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(24.723, 102.132)), module, SequelSaveModule::IN_SAVE_3_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(57.91, 102.132)), module, SequelSaveModule::IN_LOAD_3_INPUT));
	}
};


Model* modelSequelSaveModule = createModel<SequelSaveModule, SequelSaveModuleWidget>("SequelSave");