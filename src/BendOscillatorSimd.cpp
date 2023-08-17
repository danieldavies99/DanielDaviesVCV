#include "plugin.hpp"

using namespace rack;

void BendOscillatorSimd::process(float deltaTime) {
    simd::float_4 deltaPhase = simd::clamp(freq * deltaTime, 0.f, 0.35f);
    phase += deltaPhase;

    // wrap phase
    phase -= simd::floor(phase);

    float bendAmount = bendParam / 2;


    simd::float_4 bentPhase = phase;

    // given input 0 -> 1
    // will output a skewed 0 -> 1

    for(int i = 0; i < 4; i++) {   
        if(phase[i] <= 0.5) { // THIS IS SORT OF CLOSE
            if(phase[i] <= bendAmount) { // /
                float percentageToBend = phase[i] / bendAmount;
                bentPhase[i] = 0.25 * percentageToBend;
            } else { 
                float percentageToHalfWayFromBend = (phase[i] - bendAmount) / (0.5 - bendAmount);
                bentPhase[i] = 0.25+(0.25*percentageToHalfWayFromBend);
            }
        }  else {
            if(phase[i] >= 1.f - bendAmount) { // / not quite right
                float percentageToEnd = (phase[i] - (1-bendAmount)) / bendAmount;
                bentPhase[i] = 0.75 + 0.25 * percentageToEnd;
            } else {
                float percentageToPeak = (phase[i] - 0.5) / (1.f - bendAmount - 0.5);
                bentPhase[i] = 0.5+(0.25*percentageToPeak);
            }
        }
    }


    bentPhase = simd::clamp(bentPhase, 0.f, 1.f);

    simd::float_4 frames = simd::floor(bentPhase*2048);

    sinOut[0] = sinTable[(int)frames[0]];
    sinOut[1] = sinTable[(int)frames[1]];
    sinOut[2] = sinTable[(int)frames[2]];
    sinOut[3] = sinTable[(int)frames[3]];
}

void BendOscillatorSimd::generateSinTable() {
    int resolution = 2048;
    // M_PI
    float stepSize = (2*M_PI) / resolution;
    for (int i = 0; i < resolution; i++) {
        sinTable[i] = std::sin(i*stepSize);
    }
}