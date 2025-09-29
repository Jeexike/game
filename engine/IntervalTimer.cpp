#include "includes/IntervalTimer.h"
#include <iostream>

short IntervalTimer::ticksPerSec = 50;

IntervalTimer::IntervalTimer(float seconds, std::function<void()> onFinish)
    : finishCallback(std::move(onFinish)) {
    ticksLeft = seconds * ticksPerSec;
    intervalSeconds = seconds;
}

void IntervalTimer::tick() {
    ticksLeft--;
    if (ticksLeft <= 0) {
        finishCallback();
        ticksLeft = intervalSeconds * ticksPerSec;
        std::cout << "ticks left " << ticksLeft << std::endl;
    }
}

void IntervalTimer::updateInterval(float newSeconds) {
    intervalSeconds = newSeconds;
    ticksLeft = newSeconds * ticksPerSec;
}