#include "Quantize.hpp"

double quantize::roundToNearestAllowedDecimal(
    double input,
    const double allowedDecimals[],
    int numAllowedDecimals)
{
    double inputInt = floor(input);

    double closestValue = input;
    double minDiff = std::numeric_limits<double>::max();

    for (int i = 0; i < numAllowedDecimals; ++i)
    {
        double candidate = inputInt + allowedDecimals[i];
        double diff = fabs(candidate - input);

        if (diff < minDiff)
        {
            minDiff = diff;
            closestValue = candidate;
        }

        // Also check for wrapping from below (e.g. 0.95 rounded to 0.0)
        double wrappedCandidate = inputInt - 1.0 + allowedDecimals[i];
        diff = fabs(wrappedCandidate - input);

        if (diff < minDiff)
        {
            minDiff = diff;
            closestValue = wrappedCandidate;
        }
    }
    return closestValue;
}

std::vector<double> quantize::allowedDecimalsFromMask(KeyMask mask)
{
    static const double noteOffsets[12] = {
        0.0, 0.0833, 0.1666, 0.2500, 0.3333, 0.4166,
        0.5000, 0.5833, 0.6666, 0.7500, 0.8333, 0.9166};

    std::vector<double> result;
    for (int i = 0; i < 12; ++i)
    {
        if (mask & (1 << i))
        {
            result.push_back(noteOffsets[i]);
        }
    }
    return result;
}