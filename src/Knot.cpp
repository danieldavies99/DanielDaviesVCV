#include "plugin.hpp"
#include <algorithm>

struct Knot : Module {
	enum ParamId {
		KNOB_PATTERN_SELECT_PARAM,
		PARAMS_LEN
	};
	enum InputId {
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
	enum OutputId {
		OUTPUT_OUT_1_OUTPUT,
		OUTPUT_OUT_2_OUTPUT,
		OUTPUT_OUT_3_OUTPUT,
		OUTPUT_OUT_4_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};

	Knot() {
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

	int selectedPattern = 0;

	// undo and redo stacks
	const size_t MAX_STACK_SIZE = 128;

	std::deque<KnotUndoState> undoStack;
	std::deque<KnotUndoState> redoStack;

	

	void addCurrentStateToUndoStack() {
		if (undoStack.size() == MAX_STACK_SIZE) {
			undoStack.pop_front();
		}
		undoStack.push_back(KnotUndoState(output1Index, output2Index, output3Index, output4Index));
		redoStack.clear();
	}

	float getInputVoltage(int inputIndex) {
		if (inputIndex == 0) {
			return inputs[INPUT_IN_1_INPUT].getVoltage();
		}
		if (inputIndex == 1) {
			return inputs[INPUT_IN_2_INPUT].getVoltage();
		}
		if (inputIndex == 2) {
			return inputs[INPUT_IN_3_INPUT].getVoltage();
		}
		if (inputIndex == 3) {
			return inputs[INPUT_IN_4_INPUT].getVoltage();
		}
		return 0.f;
	}


	int getInputId(int inputIndex) {
		if (inputIndex == 0) {
			return INPUT_IN_1_INPUT;
		}
		if (inputIndex == 1) {
			return INPUT_IN_2_INPUT;
		}
		if (inputIndex == 2) {
			return INPUT_IN_3_INPUT;
		}
		if (inputIndex == 3) {
			return INPUT_IN_4_INPUT;
		}
		return -1;
	}

	// handle control inputs:
	void handleShiftDown() {
		addCurrentStateToUndoStack();
		output1Index += 1;
		output2Index += 1;
		output3Index += 1;
		output4Index += 1;
		if (output1Index > 3) {
			output1Index = 0;
		}
		if (output2Index > 3) {
			output2Index = 0;
		}
		if (output3Index > 3) {
			output3Index = 0;
		}
		if (output4Index > 3) {
			output4Index = 0;
		}
	}

	void handleShiftUp() {
		addCurrentStateToUndoStack();
		output1Index -= 1;
		output2Index -= 1;
		output3Index -= 1;
		output4Index -= 1;
		if (output1Index < 0) {
			output1Index = 3;
		}
		if (output2Index < 0) {
			output2Index = 3;
		}
		if (output3Index < 0) {
			output3Index = 3;
		}
		if (output4Index < 0) {
			output4Index = 3;
		}
	}

	void handleReset() {
		addCurrentStateToUndoStack();
		output1Index = 0;
		output2Index = 1;
		output3Index = 2;
		output4Index = 3;
	}

	void handleSwap(int *outputIndex1, int *outputIndex2) {
		addCurrentStateToUndoStack();
		std::swap(*outputIndex1, *outputIndex2);
	}

	void handleRandom(bool shouldAddToUndoStack = true) {
		addCurrentStateToUndoStack();
		int indexes[4] = { 0, 1, 2, 3 };
		std::random_shuffle(std::begin(indexes), std::end(indexes));
		output1Index = indexes[0];
		output2Index = indexes[1];
		output3Index = indexes[2];
		output4Index = indexes[3];
	}

	void handleUndo() {
		if (undoStack.empty()) return;

		KnotUndoState undoState = undoStack.back();
		undoStack.pop_back();
		redoStack.push_back(undoState);

		output1Index = undoState.output1Index;
		output2Index = undoState.output2Index;
		output3Index = undoState.output3Index;
		output4Index = undoState.output4Index;
	}

	void handleRedo() {
		if (redoStack.empty()) return;

		KnotUndoState undoState = redoStack.back();
		redoStack.pop_back();
		undoStack.push_back(undoState);

		output1Index = undoState.output1Index;
		output2Index = undoState.output2Index;
		output3Index = undoState.output3Index;
		output4Index = undoState.output4Index;
	}
	// end handle control inputs

	void process(const ProcessArgs& args) override {

		isInput1Connected = false;
		isInput2Connected = false;
		isInput3Connected = false;
		isInput4Connected = false;
		if(inputs[INPUT_IN_1_INPUT].isConnected()) {
			isInput1Connected = true;
		}
		if(inputs[INPUT_IN_2_INPUT].isConnected()) {
			isInput2Connected = true;
		}
		if(inputs[INPUT_IN_3_INPUT].isConnected()) {
			isInput3Connected = true;
		}
		if(inputs[INPUT_IN_4_INPUT].isConnected()) {
			isInput4Connected = true;
		}

		if (inputs[INPUT_CONTROL_SHIFT_DOWN_INPUT].isConnected() &&shiftDownDetector.check(inputs[INPUT_CONTROL_SHIFT_DOWN_INPUT].getVoltage())) {
			handleShiftDown();
		}

		if (inputs[INPUT_CONTROL_SHIFT_UP_INPUT].isConnected() && shiftUpDetector.check(inputs[INPUT_CONTROL_SHIFT_UP_INPUT].getVoltage())) {
			handleShiftUp();
		}

		if (inputs[INPUT_CONTROL_RESET_INPUT].isConnected() && resetDetector.check(inputs[INPUT_CONTROL_RESET_INPUT].getVoltage())) {
			handleReset();
		}

		// handle 1-2 switch
		if (inputs[INPUT_CONTROL_1_2_INPUT].isConnected() && swap12Detector.check(inputs[INPUT_CONTROL_1_2_INPUT].getVoltage())) {
			handleSwap(&output1Index, &output2Index);
		}

		// handle 3-4 switch
		if (inputs[INPUT_CONTROL_3_4_INPUT].isConnected() && swap34Detector.check(inputs[INPUT_CONTROL_3_4_INPUT].getVoltage())) {
			handleSwap(&output3Index, &output4Index);
		}

		// handle 2-3 switch
		if (inputs[INPUT_CONTROL_2_3_INPUT].isConnected() && swap23Detector.check(inputs[INPUT_CONTROL_2_3_INPUT].getVoltage())) {
			handleSwap(&output2Index, &output3Index);
		}

		// handle 1-4 switch
		if (inputs[INPUT_CONTROL_1_4_INPUT].isConnected() && swap14Detector.check(inputs[INPUT_CONTROL_1_4_INPUT].getVoltage())) {
			handleSwap(&output1Index, &output4Index);
		}

		// handle 1-3 switch
		if (inputs[INPUT_CONTROL_1_3_INPUT].isConnected() && swap13Detector.check(inputs[INPUT_CONTROL_1_3_INPUT].getVoltage())) {
			handleSwap(&output1Index, &output3Index);
		}

		// handle 2-4 switch
		if (inputs[INPUT_CONTROL_2_4_INPUT].isConnected() && swap24Detector.check(inputs[INPUT_CONTROL_2_4_INPUT].getVoltage())) {
			handleSwap(&output2Index, &output4Index);
		}

		// handle random
		if (inputs[INPUT_CONTROL_RANDOM_INPUT].isConnected() && randomDetector.check(inputs[INPUT_CONTROL_RANDOM_INPUT].getVoltage())) {
			handleRandom();
		}

		// handle undo
		if (inputs[INPUT_CONTROL_UNDO_INPUT].isConnected() && undoDetector.check(inputs[INPUT_CONTROL_UNDO_INPUT].getVoltage())) {
			handleUndo();
		}

		// handle redo
		if (inputs[INPUT_CONTROL_REDO_INPUT].isConnected() && redoDetector.check(inputs[INPUT_CONTROL_REDO_INPUT].getVoltage())) {
			handleRedo();
		}

		selectedPattern = params[KNOB_PATTERN_SELECT_PARAM].getValue();

		// map inputs to outputs
		int out1in = getInputId(output1Index);
		int out2in = getInputId(output2Index);
		int out3in = getInputId(output3Index);
		int out4in = getInputId(output4Index);

		if (inputs[out1in].isConnected()) {
			outputs[OUTPUT_OUT_1_OUTPUT].setVoltage(inputs[out1in].getVoltage());
		}
		if (inputs[out2in].isConnected()) {
			outputs[OUTPUT_OUT_2_OUTPUT].setVoltage(inputs[out2in].getVoltage());
		}
		if (inputs[out3in].isConnected()) {
			outputs[OUTPUT_OUT_3_OUTPUT].setVoltage(inputs[out3in].getVoltage());
		}
		if (inputs[out4in].isConnected()) {
			outputs[OUTPUT_OUT_4_OUTPUT].setVoltage(inputs[out4in].getVoltage());
		}
	}
};


struct KnotWidget : ModuleWidget {
	KnotWidget(Knot* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/Knot.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<SteppedRedKnob>(mm2px(Vec(45.509, 16.557)), module, Knot::KNOB_PATTERN_SELECT_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(75.716, 16.557)), module, Knot::INPUT_PATTERN_RESET_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(90.819, 16.557)), module, Knot::INPUT_PATTERN_STEP_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(9.996, 38.971)), module, Knot::INPUT_CONTROL_1_2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(25.53, 38.971)), module, Knot::INPUT_CONTROL_1_3_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(41.063, 38.971)), module, Knot::INPUT_CONTROL_RANDOM_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(68.063, 38.971)), module, Knot::INPUT_IN_1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(9.996, 59.803)), module, Knot::INPUT_CONTROL_3_4_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(25.53, 59.803)), module, Knot::INPUT_CONTROL_2_4_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(41.063, 59.803)), module, Knot::INPUT_CONTROL_UNDO_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(68.063, 59.803)), module, Knot::INPUT_IN_2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(9.996, 80.635)), module, Knot::INPUT_CONTROL_2_3_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(25.53, 80.635)), module, Knot::INPUT_CONTROL_SHIFT_UP_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(41.063, 80.635)), module, Knot::INPUT_CONTROL_REDO_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(68.063, 80.635)), module, Knot::INPUT_IN_3_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(9.996, 101.467)), module, Knot::INPUT_CONTROL_1_4_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(25.53, 101.467)), module, Knot::INPUT_CONTROL_SHIFT_DOWN_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(41.063, 101.467)), module, Knot::INPUT_CONTROL_RESET_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(68.063, 101.467)), module, Knot::INPUT_IN_4_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(140.366, 38.971)), module, Knot::OUTPUT_OUT_1_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(140.366, 59.803)), module, Knot::OUTPUT_OUT_2_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(140.366, 80.635)), module, Knot::OUTPUT_OUT_3_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(140.366, 101.467)), module, Knot::OUTPUT_OUT_4_OUTPUT));

		if(module) {
			LineDisplay* lineDisplay = createWidget<LineDisplay>(mm2px(Vec(75.696, 30.732)));
			lineDisplay->initialize();
			lineDisplay->in1connected = &module->isInput1Connected;
			lineDisplay->in2connected = &module->isInput2Connected;
			lineDisplay->in3connected = &module->isInput3Connected;
			lineDisplay->in4connected = &module->isInput4Connected;

			lineDisplay->output1Index = &module->output1Index;
			lineDisplay->output2Index = &module->output2Index;
			lineDisplay->output3Index = &module->output3Index;
			lineDisplay->output4Index = &module->output4Index;
			addChild(lineDisplay);

			ThreeDigitDisplay *patternSelectDisplay = new ThreeDigitDisplay();
			patternSelectDisplay->box.pos = mm2px(Vec(54.496, 14.018));
			patternSelectDisplay->value = &module->selectedPattern;
			addChild(patternSelectDisplay);
		}
	}
};


Model* modelKnot = createModel<Knot, KnotWidget>("Knot");