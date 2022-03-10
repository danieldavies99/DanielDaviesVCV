#include "plugin.hpp"


struct SequelSwitchModule : Module {
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

	SequelSwitchInterface leftMessages[2];// messages from mother (first index is page), see enum called AuxFromMotherIds in MixerCommon.hpp

	SequelSwitchModule() {
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

	const SequelSwitchInterface cleanInterface;

	SequelSwitchInterface sequelSwitchStateRow0;
	SequelSwitchInterface sequelSwitchStateRow1;
	SequelSwitchInterface sequelSwitchStateRow2;
	SequelSwitchInterface sequelSwitchStateRow3;

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

		SequelSwitchInterface *messagesFromMother = (SequelSwitchInterface*)leftExpander.consumerMessage;

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
						sequelSwitchStateRow0 = *messagesFromMother;
						break;
					case 1:
						sequelSwitchStateRow1 = *messagesFromMother;
						break;
					case 2:
						sequelSwitchStateRow2 = *messagesFromMother;
						break;
					case 3:
						sequelSwitchStateRow3 = *messagesFromMother;
					break;
				}

			}
			*messagesFromMother = cleanInterface;

			if((loadButton0Val > 0 && lastLoadButton0Val == 0) || (loadInput0Val > 0 && lastLoadInput0 == 0)) { // sending saved info to mother
				SequelSwitchInterface *messagesToMother = (SequelSwitchInterface*)leftExpander.module->rightExpander.producerMessage;
				*messagesToMother = sequelSwitchStateRow0;
				messagesToMother->isDirty = true;
				leftExpander.module->rightExpander.messageFlipRequested = true;
			}
			if((loadButton1Val > 0 && lastLoadButton1Val == 0) || (loadInput1Val > 0 && lastLoadInput1 == 0)) { // sending saved info to mother
				SequelSwitchInterface *messagesToMother = (SequelSwitchInterface*)leftExpander.module->rightExpander.producerMessage;
				*messagesToMother = sequelSwitchStateRow1;
				messagesToMother->isDirty = true;
				leftExpander.module->rightExpander.messageFlipRequested = true;
			}
			if((loadButton2Val > 0 && lastLoadButton2Val == 0) || (loadInput2Val > 0 && lastLoadInput2 == 0)) { // sending saved info to mother
				SequelSwitchInterface *messagesToMother = (SequelSwitchInterface*)leftExpander.module->rightExpander.producerMessage;
				*messagesToMother = sequelSwitchStateRow2;
				messagesToMother->isDirty = true;
				leftExpander.module->rightExpander.messageFlipRequested = true;
			}
			if((loadButton3Val > 0 && lastLoadButton3Val == 0) || (loadInput3Val > 0 && lastLoadInput3 == 0)) { // sending saved info to mother
				SequelSwitchInterface *messagesToMother = (SequelSwitchInterface*)leftExpander.module->rightExpander.producerMessage;
				*messagesToMother = sequelSwitchStateRow3;
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

	json_t* getJsonKnobsForRow(SequelSwitchInterface sequelSwitchStateRow) {
		json_t *knobs = json_array();
		for(int i = 0; i < 3; i++) {
			json_t *newKnobRow = json_array();
			for(int j = 0; j < 16; j++) {
				json_array_append(newKnobRow, json_real(sequelSwitchStateRow.knobVals[i][j]));
			}
			json_array_append(knobs, newKnobRow);
		}
		return knobs;
	}

	json_t* getJsonSwitchesForRow(SequelSwitchInterface sequelSwitchStateRow) {
		json_t *switches = json_array();
		for(int i = 0; i < 3; i++) {
			json_t *newSwitchRow = json_array();
			for(int j = 0; j < 16; j++) {
				json_array_append(newSwitchRow, json_boolean(sequelSwitchStateRow.switchVals[i][j]));
			}
			json_array_append(switches, newSwitchRow);
		}
		return switches;
	}

	json_t* getJsonClockDivideValsForRow(SequelSwitchInterface sequelSwitchStateRow) {
		json_t *clockDivideVals = json_array();
		for(int i = 0; i < 3; i++) {
			json_array_append(clockDivideVals, json_real(sequelSwitchStateRow.clockDivideVals[i]));
		}
		return clockDivideVals;
	}

	json_t *dataToJson() override {
		json_t *rootJ = json_object();

		json_object_set_new(rootJ, "knobsRow0", getJsonKnobsForRow(sequelSwitchStateRow0));
		json_object_set_new(rootJ, "switchesRow0", getJsonSwitchesForRow(sequelSwitchStateRow0));
		json_object_set_new(rootJ, "clockDivideValsRow0", getJsonClockDivideValsForRow(sequelSwitchStateRow0));
		json_object_set_new(rootJ, "speedValRow0", json_real(sequelSwitchStateRow0.speed));
		json_object_set_new(rootJ, "stepCountValRow0", json_integer(sequelSwitchStateRow0.stepCount));
		json_object_set_new(rootJ, "triggerModeValRow0", json_boolean(sequelSwitchStateRow0.triggerMode));

		json_object_set_new(rootJ, "knobsRow1", getJsonKnobsForRow(sequelSwitchStateRow1));
		json_object_set_new(rootJ, "switchesRow1", getJsonSwitchesForRow(sequelSwitchStateRow1));
		json_object_set_new(rootJ, "clockDivideValsRow1", getJsonClockDivideValsForRow(sequelSwitchStateRow1));
		json_object_set_new(rootJ, "speedValRow1", json_real(sequelSwitchStateRow1.speed));
		json_object_set_new(rootJ, "stepCountValRow1", json_integer(sequelSwitchStateRow1.stepCount));
		json_object_set_new(rootJ, "triggerModeValRow1", json_boolean(sequelSwitchStateRow1.triggerMode));

		json_object_set_new(rootJ, "knobsRow2", getJsonKnobsForRow(sequelSwitchStateRow2));
		json_object_set_new(rootJ, "switchesRow2", getJsonSwitchesForRow(sequelSwitchStateRow2));
		json_object_set_new(rootJ, "clockDivideValsRow2", getJsonClockDivideValsForRow(sequelSwitchStateRow2));
		json_object_set_new(rootJ, "speedValRow2", json_real(sequelSwitchStateRow2.speed));
		json_object_set_new(rootJ, "stepCountValRow2", json_integer(sequelSwitchStateRow2.stepCount));
		json_object_set_new(rootJ, "triggerModeValRow2", json_boolean(sequelSwitchStateRow2.triggerMode));

		json_object_set_new(rootJ, "knobsRow3", getJsonKnobsForRow(sequelSwitchStateRow3));
		json_object_set_new(rootJ, "switchesRow3", getJsonSwitchesForRow(sequelSwitchStateRow3));
		json_object_set_new(rootJ, "clockDivideValsRow3", getJsonClockDivideValsForRow(sequelSwitchStateRow3));
		json_object_set_new(rootJ, "speedValRow3", json_real(sequelSwitchStateRow3.speed));
		json_object_set_new(rootJ, "stepCountValRow3", json_integer(sequelSwitchStateRow3.stepCount));
		json_object_set_new(rootJ, "triggerModeValRow3", json_boolean(sequelSwitchStateRow3.triggerMode));
		return rootJ;
	}

	void loadKnobsFromJson(json_t *knobs, SequelSwitchInterface &sequelSwitchStateRow) {
		for(int i = 0; i < 3; i++) {
			for(int j = 0; j < 16; j++) {
				sequelSwitchStateRow.knobVals[i][j] = json_real_value(json_array_get(json_array_get(knobs, i), j));
			}
		}
	}

	void loadSwitchesFromJson(json_t *switches, SequelSwitchInterface &sequelSwitchStateRow) {
		for(int i = 0; i < 3; i++) {
			for(int j = 0; j < 16; j++) {
				sequelSwitchStateRow.switchVals[i][j] = json_boolean_value(json_array_get(json_array_get(switches, i), j)) ? 10.f : 0.f;
			}
		}
	}

	void loadClockDivideValsFromJson(json_t *clockDivideVals, SequelSwitchInterface &sequelSwitchStateRow) {
		for(int i = 0; i < 3; i++) {
			sequelSwitchStateRow.clockDivideVals[i] = json_real_value(json_array_get(clockDivideVals, i));
		}
	}

	void dataFromJson(json_t *rootJ) override { // TO DO refactor this bullshit
		json_t *knobsRow0 = json_object_get(rootJ, "knobsRow0");
		json_t *switchesRow0 = json_object_get(rootJ, "switchesRow0");
		json_t *clockDivideValsRow0 = json_object_get(rootJ, "clockDivideValsRow0");
		if(knobsRow0 && switchesRow0 && clockDivideValsRow0) {
			loadKnobsFromJson(knobsRow0, sequelSwitchStateRow0);
			loadSwitchesFromJson(switchesRow0, sequelSwitchStateRow0);
			loadClockDivideValsFromJson(clockDivideValsRow0, sequelSwitchStateRow0);
			sequelSwitchStateRow0.speed = json_real_value(json_object_get(rootJ, "speedValRow0"));
			sequelSwitchStateRow0.stepCount = json_integer_value(json_object_get(rootJ, "stepCountValRow0"));
			sequelSwitchStateRow0.triggerMode = json_boolean_value(json_object_get(rootJ, "triggerModeValRow0"));
		}

		json_t *knobsRow1 = json_object_get(rootJ, "knobsRow1");
		json_t *switchesRow1 = json_object_get(rootJ, "switchesRow1");
		json_t *clockDivideValsRow1 = json_object_get(rootJ, "clockDivideValsRow1");
		if(knobsRow1 && switchesRow1 && clockDivideValsRow1) {
			loadKnobsFromJson(knobsRow1, sequelSwitchStateRow1);
			loadSwitchesFromJson(switchesRow1, sequelSwitchStateRow1);
			loadClockDivideValsFromJson(clockDivideValsRow1, sequelSwitchStateRow1);
			sequelSwitchStateRow1.speed = json_real_value(json_object_get(rootJ, "speedValRow1"));
			sequelSwitchStateRow1.stepCount = json_integer_value(json_object_get(rootJ, "stepCountValRow1"));
			sequelSwitchStateRow1.triggerMode = json_boolean_value(json_object_get(rootJ, "triggerModeValRow1"));
		}

		json_t *knobsRow2 = json_object_get(rootJ, "knobsRow2");
		json_t *switchesRow2 = json_object_get(rootJ, "switchesRow2");
		json_t *clockDivideValsRow2 = json_object_get(rootJ, "clockDivideValsRow2");
		if(knobsRow2 && switchesRow2 && clockDivideValsRow2) {
			loadKnobsFromJson(knobsRow2, sequelSwitchStateRow2);
			loadSwitchesFromJson(switchesRow2, sequelSwitchStateRow2);
			loadClockDivideValsFromJson(clockDivideValsRow2, sequelSwitchStateRow2);
			sequelSwitchStateRow2.speed = json_real_value(json_object_get(rootJ, "speedValRow2"));
			sequelSwitchStateRow2.stepCount = json_integer_value(json_object_get(rootJ, "stepCountValRow2"));
			sequelSwitchStateRow2.triggerMode = json_boolean_value(json_object_get(rootJ, "triggerModeValRow2"));
		}

		json_t *knobsRow3 = json_object_get(rootJ, "knobsRow3");
		json_t *switchesRow3 = json_object_get(rootJ, "switchesRow3");
		json_t *clockDivideValsRow3 = json_object_get(rootJ, "clockDivideValsRow3");
		if(knobsRow3 && switchesRow3 && clockDivideValsRow3) {
			loadKnobsFromJson(knobsRow3, sequelSwitchStateRow3);
			loadSwitchesFromJson(switchesRow3, sequelSwitchStateRow3);
			loadClockDivideValsFromJson(clockDivideValsRow3, sequelSwitchStateRow3);
			sequelSwitchStateRow3.speed = json_real_value(json_object_get(rootJ, "speedValRow3"));
			sequelSwitchStateRow3.stepCount = json_integer_value(json_object_get(rootJ, "stepCountValRow3"));
			sequelSwitchStateRow3.triggerMode = json_boolean_value(json_object_get(rootJ, "triggerModeValRow3"));
		}
	}
};


struct SequelSwitchModuleWidget : ModuleWidget {
	SequelSwitchModuleWidget(SequelSwitchModule* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/SequelSwitch.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<CKD6>(mm2px(Vec(8.13, 39.665)), module, SequelSwitchModule::SWITCH_SAVE_0_PARAM));
		addParam(createParamCentered<CKD6>(mm2px(Vec(41.317, 39.665)), module, SequelSwitchModule::SWITCH_LOAD_0_PARAM));
		addParam(createParamCentered<CKD6>(mm2px(Vec(8.13, 60.487)), module, SequelSwitchModule::SWITCH_SAVE_1_PARAM));
		addParam(createParamCentered<CKD6>(mm2px(Vec(41.317, 60.487)), module, SequelSwitchModule::SWITCH_LOAD_1_PARAM));
		addParam(createParamCentered<CKD6>(mm2px(Vec(8.13, 81.309)), module, SequelSwitchModule::SWITCH_SAVE_2_PARAM));
		addParam(createParamCentered<CKD6>(mm2px(Vec(41.317, 81.31)), module, SequelSwitchModule::SWITCH_LOAD_2_PARAM));
		addParam(createParamCentered<CKD6>(mm2px(Vec(8.13, 102.132)), module, SequelSwitchModule::SWITCH_SAVE_3_PARAM));
		addParam(createParamCentered<CKD6>(mm2px(Vec(41.317, 102.132)), module, SequelSwitchModule::SWITCH_LOAD_3_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(24.723, 39.665)), module, SequelSwitchModule::IN_SAVE_0_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(57.91, 39.665)), module, SequelSwitchModule::IN_LOAD_0_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(24.723, 60.487)), module, SequelSwitchModule::IN_SAVE_1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(57.91, 60.487)), module, SequelSwitchModule::IN_LOAD_1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(24.723, 81.309)), module, SequelSwitchModule::IN_SAVE_2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(57.91, 81.31)), module, SequelSwitchModule::IN_LOAD_2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(24.723, 102.132)), module, SequelSwitchModule::IN_SAVE_3_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(57.91, 102.132)), module, SequelSwitchModule::IN_LOAD_3_INPUT));
	}
};


Model* modelSequelSwitchModule = createModel<SequelSwitchModule, SequelSwitchModuleWidget>("SequelSwitchModule");