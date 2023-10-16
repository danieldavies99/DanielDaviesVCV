#include "plugin.hpp"

using namespace rack;
struct Bend : Module {
	enum ParamId {
		KNOB_COARSE_PARAM,
		KNOB_GLIDE_PARAM,
		KNOB_BEND_PARAM,
		KNOB_BEND_MODULATION_PARAM,
		KNOB_FREQUENCY_MODULATION_PARAM,
		SWITCH_LFO_PARAM,
		KNOB_AMPLITUDE_PARAM,
		KNOB_AMPLITUDE_MODULATION_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		SYNC_IN_INPUT,
		PITCH_IN_INPUT,
		BEND_IN_INPUT,
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
		LIGHT_LFO_LIGHT,
		LIGHTS_LEN
	};

	Bend() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(KNOB_BEND_PARAM, 0.f, 1.f, 0.5f, "Bend");
		configSwitch(SWITCH_LFO_PARAM, 0.f, 1.f, 0.f, "LFO mode", {"Off", "On"});
		struct FrequencyQuantity : ParamQuantity {
			float getDisplayValue() override {
				Bend* module = reinterpret_cast<Bend*>(this->module);
				if (module->lfoEnabled) {
					displayBase = 2.f;
					displayMultiplier = 1.f;
					minValue = -8.f;
					maxValue = 10.f;
					defaultValue = 1.f;
				}
				else {
					displayBase = dsp::FREQ_SEMITONE;
					displayMultiplier = dsp::FREQ_C4;
					minValue = -54.f;
					maxValue = 54.f;
					defaultValue = 0.f;
				}
				return ParamQuantity::getDisplayValue();
			}
		};
		configParam<FrequencyQuantity>(KNOB_COARSE_PARAM, -54.f, 54.f, 0.f, "Frequency", " Hz", dsp::FREQ_SEMITONE, dsp::FREQ_C4);
		configParam(KNOB_FREQUENCY_MODULATION_PARAM, -1.f, 1.f, 0.f, "Frequency modulation");
		configParam(KNOB_BEND_MODULATION_PARAM, -1.f, 1.f, 0.f, "Bend modulation");
		configParam(KNOB_GLIDE_PARAM, 0.0f, 1.f, 0.0f, "Bend time");
		configParam(KNOB_AMPLITUDE_PARAM, 0.f, 1.f, 1.f, "Amplitude");
		configParam(KNOB_AMPLITUDE_MODULATION_PARAM, -1.f, 1.f, 0.f, "Amplitude modulation");
		configInput(PITCH_IN_INPUT, "Pitch v/oct");
		configInput(BEND_IN_INPUT, "Bend modulation");
		configInput(FREQUENCY_MODULATION_IN_INPUT, "Fequency modulation");
		configInput(AMPLITUDE_MODULATION_IN_INPUT, "Amplitude modulation");
		configInput(SYNC_IN_INPUT, "Sync");
		configOutput(SQUARE_OUT_OUTPUT, "Square");
		configOutput(SIN_OUT_OUTPUT, "Sine");
		configOutput(TRIANGLE_OUT_OUTPUT, "Tri");
		configOutput(NOISE_OUT_OUTPUT, "Noise");
	}

	BendOscillatorSimd oscillators[4];
	GlideCalculator glideCalculators[4];

	bool lfoEnabled = false;

	void process(const ProcessArgs& args) override {
		float frequencyControl = params[KNOB_COARSE_PARAM].getValue() / 12.f;
		if(lfoEnabled) {
			frequencyControl = params[KNOB_COARSE_PARAM].getValue() - 1;
		}
		float glideControl = params[KNOB_GLIDE_PARAM].getValue();

		float fmMod = params[KNOB_FREQUENCY_MODULATION_PARAM].getValue();

		float bendControl = params[KNOB_BEND_PARAM].getValue();
		float bendMod = params[KNOB_BEND_MODULATION_PARAM].getValue();

		float amplitudeControl = params[KNOB_AMPLITUDE_PARAM].getValue();;
		float amMod = params[KNOB_AMPLITUDE_MODULATION_PARAM].getValue();

		bool syncEnabled = inputs[SYNC_IN_INPUT].isConnected();
		lfoEnabled = params[SWITCH_LFO_PARAM].getValue() > 0.f;

		int channels = std::max(inputs[PITCH_IN_INPUT].getChannels(), 1);

		// handle LFO indicator light
		if(lfoEnabled) {
			lights[LIGHT_LFO_LIGHT].setBrightness(1.f);
		} else {
			lights[LIGHT_LFO_LIGHT].setBrightness(0.f);
		}

		for (int c = 0; c < channels; c += 4) {
			auto& oscillator = oscillators[c / 4];
			auto& glideCalculator = glideCalculators[c / 4];

			oscillator.amplitude = amplitudeControl + ((inputs[AMPLITUDE_MODULATION_IN_INPUT].getPolyVoltageSimd<simd::float_4>(c) / 5) * amMod);
			oscillator.amplitude = simd::clamp(oscillator.amplitude, 0.f, 1.f);

			oscillator.bend = bendControl + ((inputs[BEND_IN_INPUT].getPolyVoltageSimd<simd::float_4>(c) / 5) * bendMod);
			oscillator.bend = simd::clamp(oscillator.bend, 0.02f, 0.98f);

			oscillator.channels = std::min(channels - c, 4);

			oscillator.syncEnabled = syncEnabled;
			oscillator.sync = inputs[SYNC_IN_INPUT].getPolyVoltageSimd<simd::float_4>(c);

			oscillator.unipolar = lfoEnabled;
			oscillator.usePerfectSquare = lfoEnabled;

			simd::float_4 pitch = 0.f;
			simd::float_4 freq = 0.f;
			if(!lfoEnabled) {
				pitch = frequencyControl + inputs[PITCH_IN_INPUT].getPolyVoltageSimd<simd::float_4>(c);
				freq = dsp::FREQ_C4 * dsp::exp2_taylor5(pitch);
			} else {
				pitch = frequencyControl + (inputs[FREQUENCY_MODULATION_IN_INPUT].getPolyVoltageSimd<simd::float_4>(c) * fmMod);
				freq = dsp::exp2_taylor5(pitch) * 2.f;
			}

			if(!lfoEnabled) {
				// apply glide
				if(!glideCalculator.initialized) {
					glideCalculator.initialize(freq);
				}
				glideCalculator.targetFreq = freq;
				glideCalculator.glideAmount = glideControl;
				glideCalculator.process(args.sampleTime);
				freq = glideCalculator.currentFreq;

				// apply FM
				freq += dsp::FREQ_C4 * inputs[FREQUENCY_MODULATION_IN_INPUT].getPolyVoltageSimd<simd::float_4>(c) * fmMod;
			}

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

		addParam(createParamCentered<RedSliderMedium>(mm2px(Vec(47.895, 14.38)), module, Bend::KNOB_GLIDE_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(33.026, 32.229)), module, Bend::KNOB_COARSE_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(47.895, 39.713)), module, Bend::KNOB_AMPLITUDE_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(18.002, 41.613)), module, Bend::KNOB_BEND_PARAM));
		addParam(createParamCentered<CKD6Latch>(mm2px(Vec(12.109, 79.833)), module, Bend::SWITCH_LFO_PARAM));
		addChild(createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(12.109, 79.833)), module, Bend::LIGHT_LFO_LIGHT));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(26.183, 79.833)), module, Bend::KNOB_BEND_MODULATION_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(40.257, 79.833)), module, Bend::KNOB_FREQUENCY_MODULATION_PARAM));
		addParam(createParamCentered<RedKnob>(mm2px(Vec(54.331, 79.833)), module, Bend::KNOB_AMPLITUDE_MODULATION_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(33.02, 49.418)), module, Bend::PITCH_IN_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(12.109, 94.148)), module, Bend::SYNC_IN_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(26.183, 94.148)), module, Bend::BEND_IN_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(40.257, 94.148)), module, Bend::FREQUENCY_MODULATION_IN_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(54.331, 94.148)), module, Bend::AMPLITUDE_MODULATION_IN_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(12.109, 110.457)), module, Bend::SQUARE_OUT_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(26.183, 110.457)), module, Bend::SIN_OUT_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(40.257, 110.457)), module, Bend::TRIANGLE_OUT_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(54.331, 110.457)), module, Bend::NOISE_OUT_OUTPUT));
	}
};


Model* modelBend = createModel<Bend, BendWidget>("Bend");