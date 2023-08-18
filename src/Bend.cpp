#include "plugin.hpp"

using namespace rack;
struct Bend : Module {
	enum ParamId {
		KNOB_COARSE_PARAM,
		KNOB_PULSE_WIDTH_PARAM,
		KNOB_PORTAMENTO_PARAM,
		KNOB_SHIFT_PARAM,
		KNOB_PULSE_WIDTH_MODULATION_PARAM,
		KNOB_SHIFT_MODULATION_PARAM,
		KNOB_FREQUENCY_MODULATION_PARAM,
		KNOB_AMPLITUDE_PARAM,
		KNOB_AMPLITUDE_MODULATION_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		SYNC_IN_INPUT,
		PITCH_IN_INPUT,
		SHIFT_IN_INPUT,
		PULSE_WIDTH_MODULATION_IN_INPUT,
		FREQUENCY_MODULATION_IN_INPUT,
		AMPLITUDE_MODULATION_IN_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		SQUARE_OUT_OUTPUT,
		SIN_OUT_OUTPUT,
		TRIANGLE_OUT_OUTPUT,
		NOISE_OUT_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};


	Bend() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(KNOB_SHIFT_PARAM, 0.f, 1.f, 0.5f, "Bend");
		configParam(KNOB_COARSE_PARAM, -4.f, 4.f, 0.f, "Pitch");
		configParam(KNOB_PULSE_WIDTH_PARAM, -1.f, 1.f, 0.0f, "Pulse width");
		configParam(KNOB_PULSE_WIDTH_MODULATION_PARAM, -1.f, 1.f, 0.f, "Pulse width modulation");
		configParam(KNOB_FREQUENCY_MODULATION_PARAM, -1.f, 1.f, 0.f, "Frequency modulation");
		configParam(KNOB_SHIFT_MODULATION_PARAM, -1.f, 1.f, 0.f, "Bend modulation");
		configParam(KNOB_PORTAMENTO_PARAM, 0.2f, 1.f, 0.2f, "Bend time");
		configParam(KNOB_AMPLITUDE_PARAM, 0.f, 1.f, 1.f, "Amplitude");
		configParam(KNOB_AMPLITUDE_MODULATION_PARAM, -1.f, 1.f, 0.f, "Amplitude modulation");
		configInput(PITCH_IN_INPUT, "Pitch v/oct");
		configInput(SHIFT_IN_INPUT, "Bend modulation");
		configInput(PULSE_WIDTH_MODULATION_IN_INPUT, "Pulse width modulation");
		configInput(FREQUENCY_MODULATION_IN_INPUT, "Fequency modulation");
		configInput(AMPLITUDE_MODULATION_IN_INPUT, "Amplitude modulation");
		configInput(SYNC_IN_INPUT, "Sync");
		configOutput(SQUARE_OUT_OUTPUT, "Square");
		configOutput(SIN_OUT_OUTPUT, "Sine");
		configOutput(TRIANGLE_OUT_OUTPUT, "Tri");
		configOutput(NOISE_OUT_OUTPUT, "Noise");
	}

	float frequencyControl = 0.f;
	float portamentoVal = 0.f;


	int channels = 0;

	BendOscillatorSimd oscillators[4];

	void process(const ProcessArgs& args) override {
		float frequencyControl = params[KNOB_COARSE_PARAM].getValue();
		float portamentoVal = params[KNOB_PORTAMENTO_PARAM].getValue();

		float fmMod = params[KNOB_FREQUENCY_MODULATION_PARAM].getValue();

		float bendControl = params[KNOB_SHIFT_PARAM].getValue();
		float bendMod = params[KNOB_SHIFT_MODULATION_PARAM].getValue();

		float amplitudeControl = params[KNOB_AMPLITUDE_PARAM].getValue();;
		float amMod = params[KNOB_AMPLITUDE_MODULATION_PARAM].getValue();

		float pulseWidthControl = params[KNOB_PULSE_WIDTH_PARAM].getValue();;
		float pulseWidthMod = params[KNOB_PULSE_WIDTH_MODULATION_PARAM].getValue();

		int channels = std::max(inputs[PITCH_IN_INPUT].getChannels(), 1);
		for (int c = 0; c < channels; c += 4) {
			auto& oscillator = oscillators[c / 4];

			oscillator.amplitude = amplitudeControl + ((inputs[AMPLITUDE_MODULATION_IN_INPUT].getPolyVoltageSimd<simd::float_4>(c) / 5) * amMod);
			oscillator.amplitude = simd::clamp(oscillator.amplitude, 0.f, 1.f);

			oscillator.bend = bendControl + ((inputs[SHIFT_IN_INPUT].getPolyVoltageSimd<simd::float_4>(c) / 5) * bendMod);
			oscillator.bend = simd::clamp(oscillator.bend, 0.f, 1.f);
	
			oscillator.channels = std::min(channels - c, 4);

			simd::float_4 pitch = frequencyControl + inputs[PITCH_IN_INPUT].getPolyVoltageSimd<simd::float_4>(c);
			simd::float_4 freq = dsp::FREQ_C4 * dsp::exp2_taylor5(pitch);
			freq += dsp::FREQ_C4 * inputs[FREQUENCY_MODULATION_IN_INPUT].getPolyVoltageSimd<simd::float_4>(c) * fmMod;
		
			freq = clamp(freq, 0.f, args.sampleRate / 2.f);
			oscillator.freq = freq;

			oscillator.process(args.sampleTime);

			if (outputs[SIN_OUT_OUTPUT].isConnected())
				outputs[SIN_OUT_OUTPUT].setVoltageSimd(5.f * oscillator.sinOut, c);
			if (outputs[TRIANGLE_OUT_OUTPUT].isConnected())
				outputs[TRIANGLE_OUT_OUTPUT].setVoltageSimd(5.f * oscillator.triOut, c);
			if (outputs[SQUARE_OUT_OUTPUT].isConnected())
				outputs[SQUARE_OUT_OUTPUT].setVoltageSimd(5.f * oscillator.squareOut, c);
			if (outputs[NOISE_OUT_OUTPUT].isConnected())
				outputs[NOISE_OUT_OUTPUT].setVoltageSimd(5.f * oscillator.noiseOut, c);
		}

		outputs[TRIANGLE_OUT_OUTPUT].setChannels(channels);
		outputs[SQUARE_OUT_OUTPUT].setChannels(channels);
		outputs[SIN_OUT_OUTPUT].setChannels(channels);
		outputs[NOISE_OUT_OUTPUT].setChannels(channels);
	}
};


struct BendWidget : ModuleWidget {
	BendWidget(Bend* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/Bend.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RedSliderMedium>(mm2px(Vec(47.895, 14.38)), module, Bend::KNOB_PORTAMENTO_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(33.026, 32.229)), module, Bend::KNOB_COARSE_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(47.895, 39.713)), module, Bend::KNOB_AMPLITUDE_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(18.002, 41.613)), module, Bend::KNOB_PULSE_WIDTH_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(33.026, 66.377)), module, Bend::KNOB_SHIFT_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(12.109, 83.537)), module, Bend::KNOB_PULSE_WIDTH_MODULATION_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(26.183, 83.537)), module, Bend::KNOB_SHIFT_MODULATION_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(40.257, 83.537)), module, Bend::KNOB_FREQUENCY_MODULATION_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(54.331, 83.537)), module, Bend::KNOB_AMPLITUDE_MODULATION_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(33.02, 49.418)), module, Bend::PITCH_IN_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(12.109, 94.148)), module, Bend::PULSE_WIDTH_MODULATION_IN_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(26.183, 94.148)), module, Bend::SHIFT_IN_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(40.257, 94.148)), module, Bend::FREQUENCY_MODULATION_IN_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(54.331, 94.148)), module, Bend::AMPLITUDE_MODULATION_IN_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(8.103, 32.229)), module, Bend::SYNC_IN_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(12.109, 110.457)), module, Bend::SQUARE_OUT_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(26.183, 110.457)), module, Bend::SIN_OUT_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(40.257, 110.457)), module, Bend::TRIANGLE_OUT_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(54.331, 110.457)), module, Bend::NOISE_OUT_OUTPUT));
	}
}; 


Model* modelBend = createModel<Bend, BendWidget>("Bend");