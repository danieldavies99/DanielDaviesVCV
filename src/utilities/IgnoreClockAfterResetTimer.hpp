#pragma once
#include <rack.hpp>

struct IgnoreClockAfterResetTimer
{

    rack::dsp::Timer timer;
    bool shouldIgnore = false;

    void resetTriggered();
    void process(float deltaTime);
};
