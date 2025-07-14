#include "GateDetector.hpp"

bool GateDetector::check(float input) {
    if (lastInput == 0.f && input != 0.f) {
        lastInput = input;
        return true;
    }
    lastInput = input;
    return false;
}