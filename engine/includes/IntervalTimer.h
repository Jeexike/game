#ifndef GAME_INTERVALTIMER_H
#define GAME_INTERVALTIMER_H

#include <functional>

class IntervalTimer {
    static short ticksPerSec;

private:
    float intervalSeconds = 0;
    int ticksLeft = 0;
    std::function<void()> finishCallback;

public:
    IntervalTimer(float seconds, std::function<void()> onFinish);
    void tick();
    void updateInterval(float newSeconds);
};

#endif // GAME_INTERVALTIMER_H