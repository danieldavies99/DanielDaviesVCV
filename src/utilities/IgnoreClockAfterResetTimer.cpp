#include "IgnoreClockAfterResetTimer.hpp"

using namespace rack;

void IgnoreClockAfterResetTimer::resetTriggered() {
	timer.reset();
	shouldIgnore = true;
};

void IgnoreClockAfterResetTimer::process(float deltaTime) {
	timer.process(deltaTime);
	if(timer.time > 0.001) {
		shouldIgnore = false;
	}
};
