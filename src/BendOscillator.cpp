#include "plugin.hpp"

using namespace rack;

void BendOscillator::process(
	float sampleTime,
	float pitchInput,
	float syncIn,
	float frequencyModulationIn,
	float shiftIn,
	float amplitudeIn,
	float pulseWidthIn
) {
    	// Compute the frequency from the pitch parameter and input
		// float pitch = params[KNOB_COARSE_PARAM].getValue();
		float pitch = lastPitch;
		float targetPitch = *frequencyControl + pitchInput;
		float glideRate = (10.01 - (*portamentoVal*10)) * sampleTime;
		if(*portamentoVal == 0.2f) {
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

		// set last pitch before applying frequency modulation
		lastPitch = clamp(pitch, -4.f, 4.f);
		float frequencyModulation = frequencyModulationIn * (4.f/5.f) * *frequencyModulationMod;
		pitch += frequencyModulation;
		pitch = clamp(pitch, -4.f, 4.f);
		
		// The default pitch is C4 = 261.6256f
		float freq = dsp::FREQ_C4 * std::pow(2.f, pitch);

		// Accumulate the phase
		phase += freq * sampleTime;
		if (phase >= 0.5f)
			phase -= 1.f;

		
		if(syncIn && syncIn > 0 && lastSyncInputWasNegative) {
			phase = -0.5;
		}

		// phase oscilates between 0.5 and -0.5;
		float tri;
		float shift = *shiftControl;
		shift += (shiftIn / 20) * *shiftMod;
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

		float amplitude = *amplitudeControl;
		amplitude += (amplitudeIn / 2.f) * *amplitudeMod;
		amplitude = clamp(amplitude, 0.f, 5.f);

		triOut = amplitude * tri;

		// Compute the sine output
		float sine = std::sin(M_PI * (tri / 2));
		// sine /= tri;
		// Audio signals are typically +/-5V
		// https://vcvrack.com/manual/VoltageStandards
		sinOut = amplitude * sine;

		// Compute the square output
		float pulseWidth = *pulseWidthControl;
		pulseWidth += (pulseWidthIn / 10) * *pulseWidthMod;
		pulseWidth = clamp(pulseWidth, -0.99f, 0.99f);

		float square = tri > pulseWidth ? 1 : -1;
		// sine /= tri;
		// Audio signals are typically +/-5V
		// https://vcvrack.com/manual/VoltageStandards
		squareOut = amplitude * square;

		int frame = lastFrame + 1;
		if(frame > 0) { // make number bigger here to decrease how many times this is called

			// this is a random noise function I made up, idk if it's technically the best
			// but it sounds basically indistinguishable to other white noise generators I've used
			float random = random::uniform();
			random -= 0.5;
			if(random < 0) {
				random = -(random*random);
			} else {
				random = random*random;
			}
			noiseOut = random * amplitude * 5.0f;
			frame = 0;
		}
		lastFrame = frame;
		lastSyncInputWasNegative = syncIn < 0;
};