#pragma once
#include <array>
struct SequelSaveInterface
{
    std::array<std::array<double, 16>, 3> knobVals = {{0.f}};
    std::array<std::array<bool, 16>, 3> switchVals = {{false}};
    std::array<double, 3> clockDivideVals = {1.f, 1.f, 1.f};

    double speed = 0.5f;
    int stepCount = 8;
    bool triggerMode = true;

    bool isDirty = false;
};