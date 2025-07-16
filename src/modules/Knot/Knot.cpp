#include "DanielDavies.hpp"
#include <algorithm>
#include "KnotPattern.hpp"
#include "widgets/Knobs.hpp"
#include "widgets/DigitDisplay.hpp"
#include "widgets/LineDisplay.hpp"
#include "utilities/GateDetector.hpp"

struct Knot : Module
{
	enum ParamId
	{
		KNOB_PATTERN_SELECT_PARAM,
		PARAMS_LEN
	};
	enum InputId
	{
		INPUT_PATTERN_RESET_INPUT,
		INPUT_PATTERN_STEP_INPUT,
		INPUT_CONTROL_1_2_INPUT,
		INPUT_CONTROL_1_3_INPUT,
		INPUT_CONTROL_RANDOM_INPUT,
		INPUT_IN_1_INPUT,
		INPUT_CONTROL_3_4_INPUT,
		INPUT_CONTROL_2_4_INPUT,
		INPUT_CONTROL_UNDO_INPUT,
		INPUT_IN_2_INPUT,
		INPUT_CONTROL_2_3_INPUT,
		INPUT_CONTROL_SHIFT_UP_INPUT,
		INPUT_CONTROL_REDO_INPUT,
		INPUT_IN_3_INPUT,
		INPUT_CONTROL_1_4_INPUT,
		INPUT_CONTROL_SHIFT_DOWN_INPUT,
		INPUT_CONTROL_RESET_INPUT,
		INPUT_IN_4_INPUT,
		INPUTS_LEN
	};
	enum OutputId
	{
		OUTPUT_OUT_1_OUTPUT,
		OUTPUT_OUT_2_OUTPUT,
		OUTPUT_OUT_3_OUTPUT,
		OUTPUT_OUT_4_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId
	{
		LIGHTS_LEN
	};

	Knot()
	{
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(KNOB_PATTERN_SELECT_PARAM, 0.f, 128.f, 0.f, "Pattern Select");

		configInput(INPUT_IN_1_INPUT, "");
		configInput(INPUT_IN_2_INPUT, "");
		configInput(INPUT_IN_3_INPUT, "");
		configInput(INPUT_IN_4_INPUT, "");

		configInput(INPUT_PATTERN_RESET_INPUT, "");
		configInput(INPUT_PATTERN_STEP_INPUT, "");
		configInput(INPUT_CONTROL_1_2_INPUT, "");
		configInput(INPUT_CONTROL_1_3_INPUT, "");
		configInput(INPUT_CONTROL_RANDOM_INPUT, "");
		configInput(INPUT_IN_1_INPUT, "");
		configInput(INPUT_CONTROL_3_4_INPUT, "");
		configInput(INPUT_CONTROL_2_4_INPUT, "");
		configInput(INPUT_CONTROL_UNDO_INPUT, "");
		configInput(INPUT_IN_2_INPUT, "");
		configInput(INPUT_CONTROL_2_3_INPUT, "");
		configInput(INPUT_CONTROL_SHIFT_UP_INPUT, "");
		configInput(INPUT_CONTROL_REDO_INPUT, "");
		configInput(INPUT_IN_3_INPUT, "");
		configInput(INPUT_CONTROL_1_4_INPUT, "");
		configInput(INPUT_CONTROL_SHIFT_DOWN_INPUT, "");
		configInput(INPUT_CONTROL_RESET_INPUT, "");
		configInput(INPUT_IN_4_INPUT, "");

		configOutput(OUTPUT_OUT_1_OUTPUT, "");
		configOutput(OUTPUT_OUT_2_OUTPUT, "");
		configOutput(OUTPUT_OUT_3_OUTPUT, "");
		configOutput(OUTPUT_OUT_4_OUTPUT, "");
	}

	bool isInput1Connected = true;
	bool isInput2Connected = true;
	bool isInput3Connected = true;
	bool isInput4Connected = true;

	int output1Index = 0;
	int output2Index = 1;
	int output3Index = 2;
	int output4Index = 3;

	// manual control gate detectors
	GateDetector shiftUpDetector;
	GateDetector shiftDownDetector;
	GateDetector resetDetector;
	GateDetector swap12Detector;
	GateDetector swap13Detector;
	GateDetector swap14Detector;
	GateDetector swap23Detector;
	GateDetector swap24Detector;
	GateDetector swap34Detector;
	GateDetector randomDetector;
	GateDetector undoDetector;
	GateDetector redoDetector;

	// preset patterns gate detectors
	GateDetector patternStepDetector;
	GateDetector patternResetDetector;

	int selectedPattern = 0;
	bool presetPatternsDisabled = true;

	// undo and redo stacks
	const size_t MAX_STACK_SIZE = 128;

	std::deque<KnotUndoState> undoStack;
	std::deque<KnotUndoState> redoStack;

	// pattern dictionary. might be nice to store this in json or something later
	KnotPattern patterns[129] = {
		KnotPattern(""), // empty pattern 0 because pattern zero is unused
		KnotPattern("Ss"),
		KnotPattern("XU"),
		KnotPattern("XRU"),
		KnotPattern("5RU"),
		KnotPattern("5U"),
		KnotPattern("7U"),
		KnotPattern("Uu6"),
		KnotPattern("4RU"),
		KnotPattern("X4SU"),
		KnotPattern("78U"),
		KnotPattern("8U"),
		KnotPattern("3X7U"),
		KnotPattern("79"),
		KnotPattern("72"),
		KnotPattern("78"),
		KnotPattern("857"),
		KnotPattern("956"),
		KnotPattern("35"),
		KnotPattern("4716"),
		KnotPattern("945"),
		KnotPattern("93"),
		KnotPattern("317"),
		KnotPattern("61"),
		KnotPattern("87"),
		KnotPattern("648"),
		KnotPattern("73"),
		KnotPattern("37"),
		KnotPattern("9542"),
		KnotPattern("49"),
		KnotPattern("18"),
		KnotPattern("142"),
		KnotPattern("94"),
		KnotPattern("45"),
		KnotPattern("672"),
		KnotPattern("157"),
		KnotPattern("34"),
		KnotPattern("421"),
		KnotPattern("48"),
		KnotPattern("519"),
		KnotPattern("9286"),
		KnotPattern("462"),
		KnotPattern("7s"),
		KnotPattern("7S"),
		KnotPattern("7s7S"),
		KnotPattern("8SR"),
		KnotPattern("9s7"),
		KnotPattern("4S5"),
		KnotPattern("5s2"),
		KnotPattern("6S1"),
		KnotPattern("1s3"),
		KnotPattern("5s5"),
		KnotPattern("8s"),
		KnotPattern("7sS"),
		KnotPattern("5S8"),
		KnotPattern("5S4"),
		KnotPattern("2s1"),
		KnotPattern("9S9"),
		KnotPattern("4RU"),
		KnotPattern("R51"),
		KnotPattern("R79"),
		KnotPattern("RS1"),
		KnotPattern("R8"),
		KnotPattern("R3U"),
		KnotPattern("R5u"),
		KnotPattern("RU5"),
		KnotPattern("R6u"),
		KnotPattern("R1S"),
		KnotPattern("R7u"),
		KnotPattern("R9s"),
		KnotPattern("R86"),
		KnotPattern("567"),
		KnotPattern("5s2R"),
		KnotPattern("5252"),
		KnotPattern("1234"),
		KnotPattern("sS13"),
		KnotPattern("65sS"),
		KnotPattern("sSR"),
		KnotPattern("1542"),
		KnotPattern("98s"),
		KnotPattern("4sS"),
		KnotPattern("21R"),
		KnotPattern("3sS"),
		KnotPattern("765"),
		KnotPattern("163"),
		KnotPattern("58s"),
		KnotPattern("41S"),
		KnotPattern("X5R"),
		KnotPattern("X58"),
		KnotPattern("X4"),
		KnotPattern("X67"),
		KnotPattern("X5U"),
		KnotPattern("Xs"),
		KnotPattern("XS"),
		KnotPattern("XR5"),
		KnotPattern("XUu"),
		KnotPattern("X6s"),
		KnotPattern("X4u"),
		KnotPattern("X8S"),
		KnotPattern("X54"),
		KnotPattern("X13"),
		KnotPattern("X8u"),
		KnotPattern("RXU"),
		KnotPattern("XXXUUUuuuUUUuuu"),
		KnotPattern("XRXUUUuuuUUUuuu"),
		KnotPattern("XUuUu"),
		KnotPattern("XsssSSS"),
		KnotPattern("X1313"),
		KnotPattern("XR7"),
		KnotPattern("XR67"),
		KnotPattern("XRXUUUuuuUUUuuu"),
		KnotPattern("XXUU"),
		KnotPattern("X56UUU"),
		KnotPattern("XsSUUU"),
		KnotPattern("XssUUU"),
		KnotPattern("XSSUUU"),
		KnotPattern("XSSSUUUUuuuu"),
		KnotPattern("XSSSUUUUX"),
		KnotPattern("XXUu"),
		KnotPattern("X6611"),
		KnotPattern("X7788"),
		KnotPattern("X7788XUUuu"),
		KnotPattern("X6611UUuu"),
		KnotPattern("7XUXUuU7"),
		KnotPattern("7XUXUuU8"),
		KnotPattern("13XUXUuU13"),
		KnotPattern("XRUUuu"),
		KnotPattern("XRUUuuUUuuUUuu"),
		KnotPattern("X8UUuuUUuuUUuu")};

	void addCurrentStateToUndoStack()
	{
		if (undoStack.size() == MAX_STACK_SIZE)
		{
			undoStack.pop_front();
		}
		undoStack.push_back(KnotUndoState(output1Index, output2Index, output3Index, output4Index));
		redoStack.clear();
	}

	json_t *getUndoStackJson()
	{
		json_t *undoStackJson = json_array();
		for (std::size_t i = 0; i < undoStack.size(); i++)
		{
			KnotUndoState undoState = undoStack[i];
			json_t *undoStateJson = json_array();
			json_array_append_new(undoStateJson, json_integer(undoState.output1Index));
			json_array_append_new(undoStateJson, json_integer(undoState.output2Index));
			json_array_append_new(undoStateJson, json_integer(undoState.output3Index));
			json_array_append_new(undoStateJson, json_integer(undoState.output4Index));
			json_array_append_new(undoStackJson, undoStateJson);
		}
		return undoStackJson;
	}

	void setUndoStackFromJson(json_t *undoStackJson)
	{
		undoStack.clear();
		for (std::size_t i = 0; i < json_array_size(undoStackJson); i++)
		{
			json_t *undoStateJson = json_array_get(undoStackJson, i);
			int output1Index = json_integer_value(json_array_get(undoStateJson, 0));
			int output2Index = json_integer_value(json_array_get(undoStateJson, 1));
			int output3Index = json_integer_value(json_array_get(undoStateJson, 2));
			int output4Index = json_integer_value(json_array_get(undoStateJson, 3));
			undoStack.push_back(KnotUndoState(output1Index, output2Index, output3Index, output4Index));
		}
	}

	json_t *getRedoStackJson()
	{
		json_t *redoStackJson = json_array();
		for (std::size_t i = 0; i < redoStack.size(); i++)
		{
			KnotUndoState undoState = redoStack[i];
			json_t *undoStateJson = json_array();
			json_array_append_new(undoStateJson, json_integer(undoState.output1Index));
			json_array_append_new(undoStateJson, json_integer(undoState.output2Index));
			json_array_append_new(undoStateJson, json_integer(undoState.output3Index));
			json_array_append_new(undoStateJson, json_integer(undoState.output4Index));
			json_array_append_new(redoStackJson, undoStateJson);
		}
		return redoStackJson;
	}

	void setRedoStackFromJson(json_t *redoStackJson)
	{
		redoStack.clear();
		for (std::size_t i = 0; i < json_array_size(redoStackJson); i++)
		{
			json_t *undoStateJson = json_array_get(redoStackJson, i);
			int output1Index = json_integer_value(json_array_get(undoStateJson, 0));
			int output2Index = json_integer_value(json_array_get(undoStateJson, 1));
			int output3Index = json_integer_value(json_array_get(undoStateJson, 2));
			int output4Index = json_integer_value(json_array_get(undoStateJson, 3));
			redoStack.push_back(KnotUndoState(output1Index, output2Index, output3Index, output4Index));
		}
	}

	float getInputVoltage(int inputIndex)
	{
		if (inputIndex == 0)
		{
			return inputs[INPUT_IN_1_INPUT].getVoltage();
		}
		if (inputIndex == 1)
		{
			return inputs[INPUT_IN_2_INPUT].getVoltage();
		}
		if (inputIndex == 2)
		{
			return inputs[INPUT_IN_3_INPUT].getVoltage();
		}
		if (inputIndex == 3)
		{
			return inputs[INPUT_IN_4_INPUT].getVoltage();
		}
		return 0.f;
	}

	int getInputId(int inputIndex)
	{
		if (inputIndex == 0)
		{
			return INPUT_IN_1_INPUT;
		}
		if (inputIndex == 1)
		{
			return INPUT_IN_2_INPUT;
		}
		if (inputIndex == 2)
		{
			return INPUT_IN_3_INPUT;
		}
		if (inputIndex == 3)
		{
			return INPUT_IN_4_INPUT;
		}
		return -1;
	}

	// handle control inputs:
	void handleShiftDown()
	{
		addCurrentStateToUndoStack();
		int originalOutput1Index = output1Index;
		int originalOutput2Index = output2Index;
		int originalOutput3Index = output3Index;
		int originalOutput4Index = output4Index;

		output1Index = originalOutput2Index;
		output2Index = originalOutput3Index;
		output3Index = originalOutput4Index;
		output4Index = originalOutput1Index;
	}

	void handleShiftUp()
	{	
		addCurrentStateToUndoStack();
		int originalOutput1Index = output1Index;
		int originalOutput2Index = output2Index;
		int originalOutput3Index = output3Index;
		int originalOutput4Index = output4Index;
		
		output1Index = originalOutput4Index;
		output2Index = originalOutput1Index;
		output3Index = originalOutput2Index;
		output4Index = originalOutput3Index;
	}

	void handleReset()
	{
		addCurrentStateToUndoStack();
		output1Index = 0;
		output2Index = 1;
		output3Index = 2;
		output4Index = 3;
	}

	void handleSwap(int *outputIndex1, int *outputIndex2)
	{
		addCurrentStateToUndoStack();
		std::swap(*outputIndex1, *outputIndex2);
	}

	void handleRandom(bool shouldAddToUndoStack = true)
	{
		addCurrentStateToUndoStack();
		int indexes[4] = {0, 1, 2, 3};
		std::random_shuffle(std::begin(indexes), std::end(indexes));
		output1Index = indexes[0];
		output2Index = indexes[1];
		output3Index = indexes[2];
		output4Index = indexes[3];
	}

	void handleUndo()
	{
		if (undoStack.empty())
			return;

		KnotUndoState undoState = undoStack.back();
		undoStack.pop_back();
		redoStack.push_back(undoState);

		output1Index = undoState.output1Index;
		output2Index = undoState.output2Index;
		output3Index = undoState.output3Index;
		output4Index = undoState.output4Index;
	}

	void handleRedo()
	{
		if (redoStack.empty())
			return;

		KnotUndoState undoState = redoStack.back();
		redoStack.pop_back();
		undoStack.push_back(undoState);

		output1Index = undoState.output1Index;
		output2Index = undoState.output2Index;
		output3Index = undoState.output3Index;
		output4Index = undoState.output4Index;
	}
	// end handle control inputs

	void handlePatternStep(KnotControl control)
	{
		switch (control)
		{
		case ShiftDown:
			handleShiftDown();
			break;
		case ShiftUp:
			handleShiftUp();
			break;
		case Reset:
			handleReset();
			break;
		case Swap12:
			handleSwap(&output1Index, &output2Index);
			break;
		case Swap34:
			handleSwap(&output3Index, &output4Index);
			break;
		case Swap23:
			handleSwap(&output2Index, &output3Index);
			break;
		case Swap14:
			handleSwap(&output1Index, &output4Index);
			break;
		case Swap13:
			handleSwap(&output1Index, &output3Index);
			break;
		case Swap24:
			handleSwap(&output2Index, &output4Index);
			break;
		case Swap1234:
			handleSwap(&output1Index, &output2Index);
			handleSwap(&output3Index, &output4Index);
			break;
		case Swap1423:
			handleSwap(&output1Index, &output4Index);
			handleSwap(&output2Index, &output3Index);
			break;
		case Swap1324:
			handleSwap(&output1Index, &output3Index);
			handleSwap(&output2Index, &output4Index);
			break;
		case Random:
			handleRandom();
			break;
		case Undo:
			handleUndo();
			break;
		case Redo:
			handleRedo();
			break;
		}
	}

	json_t *getInputMappingJson()
	{
		json_t *root = json_object();
		json_object_set(root, "1", json_integer(output1Index));
		json_object_set(root, "2", json_integer(output2Index));
		json_object_set(root, "3", json_integer(output3Index));
		json_object_set(root, "4", json_integer(output4Index));
		return root;
	}

	void setInputMappingFromJson(json_t *root)
	{
		output1Index = json_integer_value(json_object_get(root, "1"));
		output2Index = json_integer_value(json_object_get(root, "2"));
		output3Index = json_integer_value(json_object_get(root, "3"));
		output4Index = json_integer_value(json_object_get(root, "4"));
	}

	json_t *getPatternStateJson()
	{
		json_t *root = json_object();
		json_object_set(root, "selectedPattern", json_integer(selectedPattern));
		json_object_set(root, "patternStep", json_integer(patterns[selectedPattern].patternIndex));
		return root;
	}

	void setPatternStateFromJson(json_t *root)
	{
		selectedPattern = json_integer_value(json_object_get(root, "selectedPattern"));
		patterns[selectedPattern].patternIndex = json_integer_value(json_object_get(root, "patternStep"));
	}

	void process(const ProcessArgs &args) override
	{

		isInput1Connected = false;
		isInput2Connected = false;
		isInput3Connected = false;
		isInput4Connected = false;
		if (inputs[INPUT_IN_1_INPUT].isConnected())
		{
			isInput1Connected = true;
		}
		if (inputs[INPUT_IN_2_INPUT].isConnected())
		{
			isInput2Connected = true;
		}
		if (inputs[INPUT_IN_3_INPUT].isConnected())
		{
			isInput3Connected = true;
		}
		if (inputs[INPUT_IN_4_INPUT].isConnected())
		{
			isInput4Connected = true;
		}

		if (inputs[INPUT_CONTROL_SHIFT_DOWN_INPUT].isConnected() && shiftDownDetector.check(inputs[INPUT_CONTROL_SHIFT_DOWN_INPUT].getVoltage()))
		{
			handleShiftDown();
		}

		if (inputs[INPUT_CONTROL_SHIFT_UP_INPUT].isConnected() && shiftUpDetector.check(inputs[INPUT_CONTROL_SHIFT_UP_INPUT].getVoltage()))
		{
			handleShiftUp();
		}

		if (inputs[INPUT_CONTROL_RESET_INPUT].isConnected() && resetDetector.check(inputs[INPUT_CONTROL_RESET_INPUT].getVoltage()))
		{
			handleReset();
		}

		// handle 1-2 switch
		if (inputs[INPUT_CONTROL_1_2_INPUT].isConnected() && swap12Detector.check(inputs[INPUT_CONTROL_1_2_INPUT].getVoltage()))
		{
			handleSwap(&output1Index, &output2Index);
		}

		// handle 3-4 switch
		if (inputs[INPUT_CONTROL_3_4_INPUT].isConnected() && swap34Detector.check(inputs[INPUT_CONTROL_3_4_INPUT].getVoltage()))
		{
			handleSwap(&output3Index, &output4Index);
		}

		// handle 2-3 switch
		if (inputs[INPUT_CONTROL_2_3_INPUT].isConnected() && swap23Detector.check(inputs[INPUT_CONTROL_2_3_INPUT].getVoltage()))
		{
			handleSwap(&output2Index, &output3Index);
		}

		// handle 1-4 switch
		if (inputs[INPUT_CONTROL_1_4_INPUT].isConnected() && swap14Detector.check(inputs[INPUT_CONTROL_1_4_INPUT].getVoltage()))
		{
			handleSwap(&output1Index, &output4Index);
		}

		// handle 1-3 switch
		if (inputs[INPUT_CONTROL_1_3_INPUT].isConnected() && swap13Detector.check(inputs[INPUT_CONTROL_1_3_INPUT].getVoltage()))
		{
			handleSwap(&output1Index, &output3Index);
		}

		// handle 2-4 switch
		if (inputs[INPUT_CONTROL_2_4_INPUT].isConnected() && swap24Detector.check(inputs[INPUT_CONTROL_2_4_INPUT].getVoltage()))
		{
			handleSwap(&output2Index, &output4Index);
		}

		// handle random
		if (inputs[INPUT_CONTROL_RANDOM_INPUT].isConnected() && randomDetector.check(inputs[INPUT_CONTROL_RANDOM_INPUT].getVoltage()))
		{
			handleRandom();
		}

		// handle undo
		if (inputs[INPUT_CONTROL_UNDO_INPUT].isConnected() && undoDetector.check(inputs[INPUT_CONTROL_UNDO_INPUT].getVoltage()))
		{
			handleUndo();
		}

		// handle redo
		if (inputs[INPUT_CONTROL_REDO_INPUT].isConnected() && redoDetector.check(inputs[INPUT_CONTROL_REDO_INPUT].getVoltage()))
		{
			handleRedo();
		}

		// handle preset patterns
		selectedPattern = params[KNOB_PATTERN_SELECT_PARAM].getValue();
		if (selectedPattern == 0)
		{
			presetPatternsDisabled = true;
		}
		else
		{
			presetPatternsDisabled = false;
		}

		if (!presetPatternsDisabled)
		{
			// handle step
			if (inputs[INPUT_PATTERN_STEP_INPUT].isConnected() && patternStepDetector.check(inputs[INPUT_PATTERN_STEP_INPUT].getVoltage()))
			{
				handlePatternStep(patterns[selectedPattern].getNextControl());
			}
			// handle reset
			if (inputs[INPUT_PATTERN_RESET_INPUT].isConnected() && patternResetDetector.check(inputs[INPUT_PATTERN_RESET_INPUT].getVoltage()))
			{
				patterns[selectedPattern].reset();
				handleReset();
			}
		}

		// map inputs to outputs
		int out1in = getInputId(output1Index);
		int out2in = getInputId(output2Index);
		int out3in = getInputId(output3Index);
		int out4in = getInputId(output4Index);

		if (inputs[out1in].isConnected())
		{
			outputs[OUTPUT_OUT_1_OUTPUT].setVoltage(inputs[out1in].getVoltage());
		}
		if (inputs[out2in].isConnected())
		{
			outputs[OUTPUT_OUT_2_OUTPUT].setVoltage(inputs[out2in].getVoltage());
		}
		if (inputs[out3in].isConnected())
		{
			outputs[OUTPUT_OUT_3_OUTPUT].setVoltage(inputs[out3in].getVoltage());
		}
		if (inputs[out4in].isConnected())
		{
			outputs[OUTPUT_OUT_4_OUTPUT].setVoltage(inputs[out4in].getVoltage());
		}
	}

	json_t *dataToJson() override
	{
		json_t *rootJ = json_object();

		json_t *undoStackJ = getUndoStackJson();
		json_object_set_new(rootJ, "undoStack", undoStackJ);

		json_t *redoStackJ = getRedoStackJson();
		json_object_set_new(rootJ, "redoStack", redoStackJ);

		json_t *patternStateJ = getPatternStateJson();
		json_object_set_new(rootJ, "patternState", patternStateJ);

		json_t *inputMapJson = getInputMappingJson();
		json_object_set_new(rootJ, "inputMap", inputMapJson);

		return rootJ;
	}

	void dataFromJson(json_t *rootJ) override
	{
		json_t *undoStackJ = json_object_get(rootJ, "undoStack");
		if (undoStackJ)
		{
			setUndoStackFromJson(undoStackJ);
		}

		json_t *redoStackJ = json_object_get(rootJ, "redoStack");
		if (redoStackJ)
		{
			setRedoStackFromJson(redoStackJ);
		}

		json_t *patternStateJ = json_object_get(rootJ, "patternState");
		if (patternStateJ)
		{
			setPatternStateFromJson(patternStateJ);
		}

		json_t *inputMapJson = json_object_get(rootJ, "inputMap");
		if (inputMapJson)
		{
			setInputMappingFromJson(inputMapJson);
		}
	}
};

struct KnotWidget : ModuleWidget
{
	bool matchCableColors = true;
	KnotWidget(Knot *module)
	{
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/panels/light/Knot.svg"),asset::plugin(pluginInstance, "res/panels/dark/Knot.svg")));

		addChild(createWidget<ThemedScrew>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ThemedScrew>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ThemedScrew>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ThemedScrew>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<SteppedRedKnob>(mm2px(Vec(45.509, 16.557)), module, Knot::KNOB_PATTERN_SELECT_PARAM));

		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(75.716, 16.557)), module, Knot::INPUT_PATTERN_RESET_INPUT));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(90.819, 16.557)), module, Knot::INPUT_PATTERN_STEP_INPUT));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(9.996, 38.971)), module, Knot::INPUT_CONTROL_1_2_INPUT));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(25.53, 38.971)), module, Knot::INPUT_CONTROL_1_3_INPUT));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(41.063, 38.971)), module, Knot::INPUT_CONTROL_RANDOM_INPUT));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(68.063, 38.971)), module, Knot::INPUT_IN_1_INPUT));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(9.996, 59.803)), module, Knot::INPUT_CONTROL_3_4_INPUT));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(25.53, 59.803)), module, Knot::INPUT_CONTROL_2_4_INPUT));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(41.063, 59.803)), module, Knot::INPUT_CONTROL_UNDO_INPUT));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(68.063, 59.803)), module, Knot::INPUT_IN_2_INPUT));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(9.996, 80.635)), module, Knot::INPUT_CONTROL_2_3_INPUT));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(25.53, 80.635)), module, Knot::INPUT_CONTROL_SHIFT_UP_INPUT));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(41.063, 80.635)), module, Knot::INPUT_CONTROL_REDO_INPUT));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(68.063, 80.635)), module, Knot::INPUT_IN_3_INPUT));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(9.996, 101.467)), module, Knot::INPUT_CONTROL_1_4_INPUT));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(25.53, 101.467)), module, Knot::INPUT_CONTROL_SHIFT_DOWN_INPUT));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(41.063, 101.467)), module, Knot::INPUT_CONTROL_RESET_INPUT));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(68.063, 101.467)), module, Knot::INPUT_IN_4_INPUT));

		addOutput(createOutputCentered<ThemedPJ301MPort>(mm2px(Vec(140.366, 38.971)), module, Knot::OUTPUT_OUT_1_OUTPUT));
		addOutput(createOutputCentered<ThemedPJ301MPort>(mm2px(Vec(140.366, 59.803)), module, Knot::OUTPUT_OUT_2_OUTPUT));
		addOutput(createOutputCentered<ThemedPJ301MPort>(mm2px(Vec(140.366, 80.635)), module, Knot::OUTPUT_OUT_3_OUTPUT));
		addOutput(createOutputCentered<ThemedPJ301MPort>(mm2px(Vec(140.366, 101.467)), module, Knot::OUTPUT_OUT_4_OUTPUT));

		if (module)
		{	
			LineDisplay *lineDisplay = createWidget<LineDisplay>(mm2px(Vec(75.696, 30.732)));
			lineDisplay->initialize();
			lineDisplay->in1connected = &module->isInput1Connected;
			lineDisplay->in2connected = &module->isInput2Connected;
			lineDisplay->in3connected = &module->isInput3Connected;
			lineDisplay->in4connected = &module->isInput4Connected;

			lineDisplay->output1Index = &module->output1Index;
			lineDisplay->output2Index = &module->output2Index;
			lineDisplay->output3Index = &module->output3Index;
			lineDisplay->output4Index = &module->output4Index;

			lineDisplay->input1portId = Knot::INPUT_IN_1_INPUT;
			lineDisplay->input2portId = Knot::INPUT_IN_2_INPUT;
			lineDisplay->input3portId = Knot::INPUT_IN_3_INPUT;
			lineDisplay->input4portId = Knot::INPUT_IN_4_INPUT;

			lineDisplay->matchCableColors = &matchCableColors;

			lineDisplay->moduleWidget = this;

			addChild(lineDisplay);

			ThreeDigitDisplay *patternSelectDisplay = new ThreeDigitDisplay();
			patternSelectDisplay->box.pos = mm2px(Vec(54.496, 14.018));
			patternSelectDisplay->value = &module->selectedPattern;
			patternSelectDisplay->showDashes = &module->presetPatternsDisabled;
			addChild(patternSelectDisplay);
		}
	}

	void appendContextMenu(Menu *menu) override
	{
		struct ToggleMatchCableColors : MenuItem
		{	
			bool *matchCableColors;
			void onAction(const event::Action &e) override
			{
				*matchCableColors = !*matchCableColors;
			}
		};

		menu->addChild(new MenuSeparator());
		ToggleMatchCableColors *matchCableColorsToggle = createMenuItem<ToggleMatchCableColors>("Match cable colors");
		matchCableColorsToggle->matchCableColors = &matchCableColors;
		matchCableColorsToggle->rightText = CHECKMARK(matchCableColors == true);
		menu->addChild(matchCableColorsToggle);
	}
};

Model *modelKnot = createModel<Knot, KnotWidget>("Knot");