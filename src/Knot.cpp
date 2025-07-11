#include "plugin.hpp"
#include <algorithm>

struct KnotModule : Module {
	enum ParamId {
		PARAMS_LEN
	};
	enum InputId {
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

	KnotModule() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configInput(INPUT_IN_1_INPUT, "");
		configInput(INPUT_IN_2_INPUT, "");
		configInput(INPUT_IN_3_INPUT, "");
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

	int getInputIndexControl(int inputIndex) {
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

		// handle shift down
		if (inputs[INPUT_CONTROL_SHIFT_DOWN_INPUT].isConnected() &&shiftDownDetector.check(inputs[INPUT_CONTROL_SHIFT_DOWN_INPUT].getVoltage())) {
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

		// handle shift up
		if (inputs[INPUT_CONTROL_SHIFT_UP_INPUT].isConnected() && shiftUpDetector.check(inputs[INPUT_CONTROL_SHIFT_UP_INPUT].getVoltage())) {
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

		// handle reset
		if (inputs[INPUT_CONTROL_RESET_INPUT].isConnected() && resetDetector.check(inputs[INPUT_CONTROL_RESET_INPUT].getVoltage())) {
			output1Index = 0;
			output2Index = 1;
			output3Index = 2;
			output4Index = 3;
		}

		// handle 1-2 switch
		if (inputs[INPUT_CONTROL_1_2_INPUT].isConnected() && swap12Detector.check(inputs[INPUT_CONTROL_1_2_INPUT].getVoltage())) {
			std::swap(output1Index, output2Index);
		}

		// handle 3-4 switch
		if (inputs[INPUT_CONTROL_3_4_INPUT].isConnected() && swap34Detector.check(inputs[INPUT_CONTROL_3_4_INPUT].getVoltage())) {
			std::swap(output3Index, output4Index);
		}

		// handle 2-3 switch
		if (inputs[INPUT_CONTROL_2_3_INPUT].isConnected() && swap23Detector.check(inputs[INPUT_CONTROL_2_3_INPUT].getVoltage())) {
			std::swap(output2Index, output3Index);
		}

		// handle 1-4 switch
		if (inputs[INPUT_CONTROL_1_4_INPUT].isConnected() && swap14Detector.check(inputs[INPUT_CONTROL_1_4_INPUT].getVoltage())) {
			std::swap(output1Index, output4Index);
		}

		// handle 1-3 switch
		if (inputs[INPUT_CONTROL_1_3_INPUT].isConnected() && swap13Detector.check(inputs[INPUT_CONTROL_1_3_INPUT].getVoltage())) {
			std::swap(output1Index, output3Index);
		}

		// handle 2-4 switch
		if (inputs[INPUT_CONTROL_2_4_INPUT].isConnected() && swap24Detector.check(inputs[INPUT_CONTROL_2_4_INPUT].getVoltage())) {
			std::swap(output2Index, output4Index);
		}

		// handle random
		if (inputs[INPUT_CONTROL_RANDOM_INPUT].isConnected() && randomDetector.check(inputs[INPUT_CONTROL_RANDOM_INPUT].getVoltage())) {
			int indexes[4] = { 0, 1, 2, 3 };
			std::random_shuffle(std::begin(indexes), std::end(indexes));
			output1Index = indexes[0];
			output2Index = indexes[1];
			output3Index = indexes[2];
			output4Index = indexes[3];
		}

		int out1in = getInputIndexControl(output1Index);
		int out2in = getInputIndexControl(output2Index);
		int out3in = getInputIndexControl(output3Index);
		int out4in = getInputIndexControl(output4Index);

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


struct KnotModuleWidget : ModuleWidget {
	KnotModuleWidget(KnotModule* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/Knot.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(9.996, 36.583)), module, KnotModule::INPUT_CONTROL_1_2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(25.53, 36.583)), module, KnotModule::INPUT_CONTROL_1_3_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(41.063, 36.583)), module, KnotModule::INPUT_CONTROL_RANDOM_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(68.063, 36.583)), module, KnotModule::INPUT_IN_1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(9.996, 57.415)), module, KnotModule::INPUT_CONTROL_3_4_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(25.53, 57.415)), module, KnotModule::INPUT_CONTROL_2_4_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(41.063, 57.415)), module, KnotModule::INPUT_CONTROL_UNDO_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(68.063, 57.415)), module, KnotModule::INPUT_IN_2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(9.996, 78.247)), module, KnotModule::INPUT_CONTROL_2_3_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(25.53, 78.247)), module, KnotModule::INPUT_CONTROL_SHIFT_UP_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(41.063, 78.247)), module, KnotModule::INPUT_CONTROL_REDO_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(68.063, 78.247)), module, KnotModule::INPUT_IN_3_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(9.996, 99.079)), module, KnotModule::INPUT_CONTROL_1_4_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(25.53, 99.079)), module, KnotModule::INPUT_CONTROL_SHIFT_DOWN_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(41.063, 99.079)), module, KnotModule::INPUT_CONTROL_RESET_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(68.063, 99.079)), module, KnotModule::INPUT_IN_4_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(139.837, 36.583)), module, KnotModule::OUTPUT_OUT_1_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(139.837, 57.415)), module, KnotModule::OUTPUT_OUT_2_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(139.837, 78.247)), module, KnotModule::OUTPUT_OUT_3_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(139.837, 99.079)), module, KnotModule::OUTPUT_OUT_4_OUTPUT));

		if(module) {
			LineDisplay* lineDisplay = createWidget<LineDisplay>(mm2px(Vec(75.696, 28.087)));
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
		}

	}
};


Model* modelKnot = createModel<KnotModule, KnotModuleWidget>("Knot");