#include "plugin.hpp"


struct TriMorph : Module {
	enum ParamId {
		KNOB_COARSE_PARAM,
		KNOB_PULSE_WIDTH_PARAM,
		KNOB_PORTAMENTO_PARAM,
		KNOB_SHIFT_PARAM,
		KNOB_PULSE_WIDTH_MODULATION_PARAM,
		KNOB_SHIFT_MODULATION_PARAM,
		KNOB_FREQUENCY_MODULATION_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		PITCH_IN_INPUT,
		SHIFT_IN_INPUT,
		PULSE_WIDTH_MODULATION_IN_INPUT,
		FREQUENCY_MODULATION_IN_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		SQUARE_OUT_OUTPUT,
		SIN_OUT_OUTPUT,
		TRIANGLE_OUT_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};


	TriMorph() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(KNOB_SHIFT_PARAM, -0.5f, 0.5f, 0.f, "Bend");
		configParam(KNOB_COARSE_PARAM, -4.f, 4.f, 0.f, "Pitch");
		configParam(KNOB_PULSE_WIDTH_PARAM, -1.f, 1.f, 0.0f, "Pulse width");
		configParam(KNOB_PULSE_WIDTH_MODULATION_PARAM, -1.f, 1.f, 0.f, "Pulse width modulation");
		configParam(KNOB_FREQUENCY_MODULATION_PARAM, -1.f, 1.f, 0.f, "Frequency modulation");
		configParam(KNOB_SHIFT_MODULATION_PARAM, -1.f, 1.f, 0.f, "Bend modulation");
		configParam(KNOB_PORTAMENTO_PARAM, 0.2f, 1.f, 0.f, "Portamento time");
		configInput(PITCH_IN_INPUT, "Pitch v/oct");
		configInput(SHIFT_IN_INPUT, "Bend modulation");
		configInput(PULSE_WIDTH_MODULATION_IN_INPUT, "Pulse width modulation");
		configInput(FREQUENCY_MODULATION_IN_INPUT, "Fequency modulation");
		configOutput(SQUARE_OUT_OUTPUT, "Square out");
		configOutput(SIN_OUT_OUTPUT, "Sine out");
		configOutput(TRIANGLE_OUT_OUTPUT, "Tri out");
	}

	float phase = 0.f;
	float lastPitch = 0.f;
	void process(const ProcessArgs& args) override {
		// DEBUG(std::to_string(args.sampleTime).c_str());
		// Compute the frequency from the pitch parameter and input
		// float pitch = params[KNOB_COARSE_PARAM].getValue();
		float pitch = lastPitch;
		float targetPitch = params[KNOB_COARSE_PARAM].getValue() + inputs[PITCH_IN_INPUT].getVoltage();
		float portamentoVal = params[KNOB_PORTAMENTO_PARAM].getValue();
		float glideRate = (10.01 - (portamentoVal*10)) * args.sampleTime;
		if(portamentoVal == 0.2f) {
			pitch = targetPitch;
		} else {
			if(pitch < targetPitch) {
				pitch += glideRate;
				if (pitch > targetPitch) {
					pitch = targetPitch;
				}
			} else if (pitch > targetPitch) {
				pitch -= glideRate;
				if (pitch < targetPitch) {
					pitch = targetPitch;
				}
			}
		}

		// pitch += inputs[PITCH_IN_INPUT].getVoltage();
		pitch = clamp(pitch, -4.f, 4.f);
		lastPitch = pitch;
		// The default pitch is C4 = 261.6256f
		float freq = dsp::FREQ_C4 * std::pow(2.f, pitch);

		// Accumulate the phase
		phase += freq * args.sampleTime;
		if (phase >= 0.5f)
			phase -= 1.f;

		// phase oscilates between 0.5 and -0.5;
		float tri;
		float shift = params[KNOB_SHIFT_PARAM].getValue();
		shift += (inputs[SHIFT_IN_INPUT].getVoltage() / 20) * params[KNOB_SHIFT_MODULATION_PARAM].getValue();
		shift = clamp(shift, -0.5, 0.5);

		if(phase < shift) {
			tri = 4.f * phase  - (4 * (shift * ((phase + 0.5) / abs(shift - -0.5 ))) );  // -2 -> 0
		}  else {
			tri = (4.f * phase) - ( 4 * ( (shift) * (1 - ((phase - shift) / abs(0.5 - shift))) )); // 0 -> -2
			tri = -tri;
		}
		tri += 1;
		// tri oscilates between -1 and 1;

		// Audio signals are typically +/-5V
		// https://vcvrack.com/manual/VoltageStandards
		outputs[TRIANGLE_OUT_OUTPUT].setVoltage(5.f * tri);

		// Compute the sine output
		float sine = std::sin(M_PI * (tri / 2));
		// sine /= tri;
		// Audio signals are typically +/-5V
		// https://vcvrack.com/manual/VoltageStandards
		outputs[SIN_OUT_OUTPUT].setVoltage(5.f * sine);

		// Compute the square output
		float pulseWidth = params[KNOB_PULSE_WIDTH_PARAM].getValue();
		pulseWidth += (inputs[PULSE_WIDTH_MODULATION_IN_INPUT].getVoltage() / 10) * params[KNOB_PULSE_WIDTH_MODULATION_PARAM].getValue();
		pulseWidth = clamp(pulseWidth, -0.99f, 0.99f);

		float square = tri > pulseWidth ? 1 : -1;
		// sine /= tri;
		// Audio signals are typically +/-5V
		// https://vcvrack.com/manual/VoltageStandards
		outputs[SQUARE_OUT_OUTPUT].setVoltage(5.f * square);
	}
};


struct TriMorphWidget : ModuleWidget {
	TriMorphWidget(TriMorph* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/TriMorph.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RedKnob>(mm2px(Vec(33.026, 30.329)), module, TriMorph::KNOB_COARSE_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(18.002, 39.713)), module, TriMorph::KNOB_PULSE_WIDTH_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(47.895, 39.713)), module, TriMorph::KNOB_PORTAMENTO_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(33.026, 64.478)), module, TriMorph::KNOB_SHIFT_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(13.709, 81.638)), module, TriMorph::KNOB_PULSE_WIDTH_MODULATION_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(33.02, 81.638)), module, TriMorph::KNOB_SHIFT_MODULATION_PARAM)); 
		addParam(createParamCentered<RedKnob>(mm2px(Vec(52.331, 81.638)), module, TriMorph::KNOB_FREQUENCY_MODULATION_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(33.02, 47.518)), module, TriMorph::PITCH_IN_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(13.709, 93.148)), module, TriMorph::PULSE_WIDTH_MODULATION_IN_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(33.02, 93.148)), module, TriMorph::SHIFT_IN_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(52.331, 93.148)), module, TriMorph::FREQUENCY_MODULATION_IN_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(13.709, 110.457)), module, TriMorph::SQUARE_OUT_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(33.02, 110.457)), module, TriMorph::SIN_OUT_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(52.331, 110.457)), module, TriMorph::TRIANGLE_OUT_OUTPUT));
	}
}; 


Model* modelTriMorph = createModel<TriMorph, TriMorphWidget>("TriMorph");