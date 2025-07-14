#include "DanielDavies.hpp"
#include "SequelSaveInterface.hpp"

struct SequelSave : Module
{
	enum ParamId
	{
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
	enum InputId
	{
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
	enum OutputId
	{
		OUTPUTS_LEN
	};
	enum LightId
	{
		LIGHT_CONNECTED_LIGHT,
		LIGHTS_LEN
	};

	SequelSaveInterface leftMessages[2];

	SequelSave()
	{
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

	SequelSaveInterface sequelSaveStates[4];

	void process(const ProcessArgs &args) override
	{
		sequelPresent = leftExpander.module && (leftExpander.module->model == modelSequel8 || leftExpander.module->model == modelSequel16);

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

		SequelSaveInterface *messagesFromMother = (SequelSaveInterface *)leftExpander.consumerMessage;

		lights[LIGHT_CONNECTED_LIGHT].setBrightness(0.f);
		if (sequelPresent)
		{
			lights[LIGHT_CONNECTED_LIGHT].setBrightness(1.f);
			if ((saveButton0Val > 0 && lastSaveButton0Val == 0) || (saveInput0Val > 0 && lastSaveInput0 == 0))
			{ // requesting mother
				selectedSaveRow = 0;
				leftExpander.messageFlipRequested = true;
			}
			if ((saveButton1Val > 0 && lastSaveButton1Val == 0) || (saveInput1Val > 0 && lastSaveInput1 == 0))
			{ // requesting mother
				selectedSaveRow = 1;
				leftExpander.messageFlipRequested = true;
			}
			if ((saveButton2Val > 0 && lastSaveButton2Val == 0) || (saveInput2Val > 0 && lastSaveInput2 == 0))
			{ // requesting mother
				selectedSaveRow = 2;
				leftExpander.messageFlipRequested = true;
			}
			if ((saveButton3Val > 0 && lastSaveButton3Val == 0) || (saveInput3Val > 0 && lastSaveInput3 == 0))
			{ // requesting mother
				selectedSaveRow = 3;
				leftExpander.messageFlipRequested = true;
			}

			if (messagesFromMother->isDirty)
			{ // info received from mother
				sequelSaveStates[selectedSaveRow] = *messagesFromMother;
			}
			*messagesFromMother = cleanInterface;

			if ((loadButton0Val > 0 && lastLoadButton0Val == 0) || (loadInput0Val > 0 && lastLoadInput0 == 0))
			{ // sending saved info to mother
				SequelSaveInterface *messagesToMother = (SequelSaveInterface *)leftExpander.module->rightExpander.producerMessage;
				*messagesToMother = sequelSaveStates[0];
				messagesToMother->isDirty = true;
				leftExpander.module->rightExpander.messageFlipRequested = true;
			}
			if ((loadButton1Val > 0 && lastLoadButton1Val == 0) || (loadInput1Val > 0 && lastLoadInput1 == 0))
			{ // sending saved info to mother
				SequelSaveInterface *messagesToMother = (SequelSaveInterface *)leftExpander.module->rightExpander.producerMessage;
				*messagesToMother = sequelSaveStates[1];
				messagesToMother->isDirty = true;
				leftExpander.module->rightExpander.messageFlipRequested = true;
			}
			if ((loadButton2Val > 0 && lastLoadButton2Val == 0) || (loadInput2Val > 0 && lastLoadInput2 == 0))
			{ // sending saved info to mother
				SequelSaveInterface *messagesToMother = (SequelSaveInterface *)leftExpander.module->rightExpander.producerMessage;
				*messagesToMother = sequelSaveStates[2];
				messagesToMother->isDirty = true;
				leftExpander.module->rightExpander.messageFlipRequested = true;
			}
			if ((loadButton3Val > 0 && lastLoadButton3Val == 0) || (loadInput3Val > 0 && lastLoadInput3 == 0))
			{ // sending saved info to mother
				SequelSaveInterface *messagesToMother = (SequelSaveInterface *)leftExpander.module->rightExpander.producerMessage;
				*messagesToMother = sequelSaveStates[3];
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

	json_t *getJsonKnobsForRow(SequelSaveInterface sequelSaveStateRow)
	{
		json_t *knobs = json_array();
		for (int i = 0; i < 3; i++)
		{
			json_t *newKnobRow = json_array();
			for (int j = 0; j < 16; j++)
			{
				json_array_append(newKnobRow, json_real(sequelSaveStateRow.knobVals[i][j]));
			}
			json_array_append(knobs, newKnobRow);
		}
		return knobs;
	}

	json_t *getJsonSwitchesForRow(SequelSaveInterface sequelSaveStateRow)
	{
		json_t *switches = json_array();
		for (int i = 0; i < 3; i++)
		{
			json_t *newSwitchRow = json_array();
			for (int j = 0; j < 16; j++)
			{
				json_array_append(newSwitchRow, json_boolean(sequelSaveStateRow.switchVals[i][j]));
			}
			json_array_append(switches, newSwitchRow);
		}
		return switches;
	}

	json_t *getJsonClockDivideValsForRow(SequelSaveInterface sequelSaveStateRow)
	{
		json_t *clockDivideVals = json_array();
		for (int i = 0; i < 3; i++)
		{
			json_array_append(clockDivideVals, json_real(sequelSaveStateRow.clockDivideVals[i]));
		}
		return clockDivideVals;
	}

	json_t *getFullJsonForRow(int rowNumber)
	{
		json_t *rootJ = json_object();
		json_object_set_new(rootJ, "knobVals", getJsonKnobsForRow(sequelSaveStates[rowNumber]));
		json_object_set_new(rootJ, "switchVals", getJsonSwitchesForRow(sequelSaveStates[rowNumber]));
		json_object_set_new(rootJ, "clockDivideVals", getJsonClockDivideValsForRow(sequelSaveStates[rowNumber]));
		json_object_set_new(rootJ, "speedVal", json_real(sequelSaveStates[rowNumber].speed));
		json_object_set_new(rootJ, "stepCountVal", json_integer(sequelSaveStates[rowNumber].stepCount));
		json_object_set_new(rootJ, "triggerModeVal", json_boolean(sequelSaveStates[rowNumber].triggerMode));
		return rootJ;
	}

	json_t *dataToJson() override
	{
		json_t *rootJ = json_object();

		json_object_set_new(rootJ, "rowState0", getFullJsonForRow(0));
		json_object_set_new(rootJ, "rowState1", getFullJsonForRow(1));
		json_object_set_new(rootJ, "rowState2", getFullJsonForRow(2));
		json_object_set_new(rootJ, "rowState3", getFullJsonForRow(3));

		return rootJ;
	}

	void loadKnobsFromJson(json_t *knobs, SequelSaveInterface &sequelSaveStateRow)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				sequelSaveStateRow.knobVals[i][j] = json_real_value(json_array_get(json_array_get(knobs, i), j));
			}
		}
	}

	void loadSwitchesFromJson(json_t *switches, SequelSaveInterface &sequelSaveStateRow)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				sequelSaveStateRow.switchVals[i][j] = json_boolean_value(json_array_get(json_array_get(switches, i), j)) ? 10.f : 0.f;
			}
		}
	}

	void loadClockDivideValsFromJson(json_t *clockDivideVals, SequelSaveInterface &sequelSaveStateRow)
	{
		for (int i = 0; i < 3; i++)
		{
			sequelSaveStateRow.clockDivideVals[i] = json_real_value(json_array_get(clockDivideVals, i));
		}
	}

	void loadRowFromJson(int rowNumber, json_t *rootJ)
	{
		std::string rowIdentifier = "rowState" + std::to_string(rowNumber);
		json_t *row = json_object_get(rootJ, rowIdentifier.c_str());
		json_t *knobVals = json_object_get(row, "knobVals");
		json_t *switchVals = json_object_get(row, "switchVals");
		json_t *clockDivideVals = json_object_get(row, "clockDivideVals");
		if (knobVals && switchVals && clockDivideVals)
		{
			loadKnobsFromJson(knobVals, sequelSaveStates[rowNumber]);
			loadSwitchesFromJson(switchVals, sequelSaveStates[rowNumber]);
			loadClockDivideValsFromJson(clockDivideVals, sequelSaveStates[rowNumber]);
			sequelSaveStates[rowNumber].speed = json_real_value(json_object_get(row, "speedVal"));
			sequelSaveStates[rowNumber].stepCount = json_integer_value(json_object_get(row, "stepCountVal"));
			sequelSaveStates[rowNumber].triggerMode = json_boolean_value(json_object_get(row, "triggerModeVal"));
		}
	}

	void dataFromJson(json_t *rootJ) override
	{
		loadRowFromJson(0, rootJ);
		loadRowFromJson(1, rootJ);
		loadRowFromJson(2, rootJ);
		loadRowFromJson(3, rootJ);
	}
};

struct SequelSaveWidget : ModuleWidget
{
	SequelSaveWidget(SequelSave *module)
	{
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/SequelSave.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<CKD6>(mm2px(Vec(8.13, 39.665)), module, SequelSave::SWITCH_SAVE_0_PARAM));
		addParam(createParamCentered<CKD6>(mm2px(Vec(41.317, 39.665)), module, SequelSave::SWITCH_LOAD_0_PARAM));
		addParam(createParamCentered<CKD6>(mm2px(Vec(8.13, 60.487)), module, SequelSave::SWITCH_SAVE_1_PARAM));
		addParam(createParamCentered<CKD6>(mm2px(Vec(41.317, 60.487)), module, SequelSave::SWITCH_LOAD_1_PARAM));
		addParam(createParamCentered<CKD6>(mm2px(Vec(8.13, 81.309)), module, SequelSave::SWITCH_SAVE_2_PARAM));
		addParam(createParamCentered<CKD6>(mm2px(Vec(41.317, 81.31)), module, SequelSave::SWITCH_LOAD_2_PARAM));
		addParam(createParamCentered<CKD6>(mm2px(Vec(8.13, 102.132)), module, SequelSave::SWITCH_SAVE_3_PARAM));
		addParam(createParamCentered<CKD6>(mm2px(Vec(41.317, 102.132)), module, SequelSave::SWITCH_LOAD_3_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(24.723, 39.665)), module, SequelSave::IN_SAVE_0_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(57.91, 39.665)), module, SequelSave::IN_LOAD_0_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(24.723, 60.487)), module, SequelSave::IN_SAVE_1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(57.91, 60.487)), module, SequelSave::IN_LOAD_1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(24.723, 81.309)), module, SequelSave::IN_SAVE_2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(57.91, 81.31)), module, SequelSave::IN_LOAD_2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(24.723, 102.132)), module, SequelSave::IN_SAVE_3_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(57.91, 102.132)), module, SequelSave::IN_LOAD_3_INPUT));

		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(57.91, 13.551)), module, SequelSave::LIGHT_CONNECTED_LIGHT));
	}
};

Model *modelSequelSave = createModel<SequelSave, SequelSaveWidget>("SequelSave");