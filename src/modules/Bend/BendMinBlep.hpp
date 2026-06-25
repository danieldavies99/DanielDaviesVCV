#pragma once
#include <rack.hpp>
#include <dsp/minblep.hpp>

// Adapted from Fundamental/VCO. Provides both step (BLEP) and slope (BLAMP) corrections.
// Z = zero crossings, O = oversample factor
template <int Z, int O>
struct BendMinBlep {
    float impulseReordered[O][2 * Z + 4] = {};
    float rampReordered[O][2 * Z + 4] = {};

    BendMinBlep() {
        float impulse[2 * Z * O];
        rack::dsp::minBlepImpulse(Z, O, impulse);

        // Shift so the kernel goes from -1 to 0 (corrects a +1 step)
        for (int i = 0; i < 2 * Z * O; i++)
            impulse[i] -= 1.f;

        // Integrate impulse → ramp kernel (for slope/kink discontinuities)
        float ramp[2 * Z * O];
        double total = 0.0;
        for (int i = 0; i < 2 * Z * O; i++) {
            ramp[i] = total;
            total += (double)impulse[i] / O;
        }
        // Subtract ideal ramp so ramp[0] and virtual ramp[n] are both 0
        for (int i = 0; i < 2 * Z * O; i++)
            ramp[i] -= (float)i / (2 * Z * O) * (float)total;

        // Reorder: make z-values contiguous per oversampling offset
        for (int o = 0; o < O; o++)
            for (int z = 0; z < 2 * Z; z++)
                impulseReordered[o][z] = impulse[z * O + o];
        for (int o = 0; o < O; o++)
            for (int z = 0; z < 2 * Z; z++)
                rampReordered[o][z] = ramp[z * O + o];
    }

    // subsample: position of discontinuity within frame, in (0, 1] where 1 = end of frame
    // magnitude: newValue - oldValue at the jump
    void insertDiscontinuity(float subsample, float magnitude, float* out, int stride = 1) const {
        insertKernel(impulseReordered, subsample, magnitude, out, stride);
    }

    // magnitude: slopeAfter - slopeBefore (per sample)
    void insertSlopeDiscontinuity(float subsample, float magnitude, float* out, int stride = 1) const {
        insertKernel(rampReordered, subsample, magnitude, out, stride);
    }

private:
    void insertKernel(const float table[O][2 * Z + 4], float subsample, float magnitude, float* out, int stride) const {
        if (!(0.f < subsample && subsample <= 1.f))
            return;
        float t = (1.f - subsample) * O;
        int o = (int)t;
        t -= o;
        for (int z = 0; z < 2 * Z; z += 4) {
            using rack::simd::float_4;
            float_4 y1 = float_4::load(&table[o][z]);
            int o2 = (o + 1) % O;
            int z2 = z + (o + 1) / O;
            float_4 y2 = float_4::load(&table[o2][z2]);
            float_4 y = (y1 + t * (y2 - y1)) * magnitude;
            for (int zi = 0; zi < 4; zi++)
                out[(z + zi) * stride] += y[zi];
        }
    }
};


// Ring buffer that allows reading/writing up to N future correction samples.
template <int N, typename T>
struct BendMinBlepBuffer {
    T buffer[2 * N] = {};
    int32_t index = 0;

    T* startData() {
        return &buffer[index];
    }

    T shift() {
        T v = buffer[index];
        index++;
        if (index >= N) {
            std::memcpy(buffer, buffer + N, N * sizeof(T));
            std::memset(buffer + N, 0, N * sizeof(T));
            index = 0;
        }
        return v;
    }
};
