#pragma once

#include <vector>
#include <stdint.h>
#include <math.h>
#include <limits>

namespace quantize
{
    template <typename T>
    T clamp(T value, T low, T high)
    {
        if (value < low)
            return low;
        if (value > high)
            return high;
        return value;
    }

    // From C to B
    // Bit 0 = C, Bit 1 = C#, ..., Bit 11 = B
    // For example, KeyMask = 0b000000000111 would mean C, C#, D are enabled.
    using KeyMask = uint16_t; // only 12 bits actually needed

    double roundToNearestAllowedDecimal(double input, const double allowedDecimals[], int numAllowedDecimals);

    std::vector<double> allowedDecimalsFromMask(KeyMask mask);
}
