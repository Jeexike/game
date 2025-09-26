#ifndef GAME_INTERVALTIMER_H
#define GAME_INTERVALTIMER_H

#include <functional>
#include <utility>
#include <iostream>

class IntervalTimer {
    static short ticksPerSec;

private:
    float intervalSeconds = 0;
    int ticksLeft = 0;
    std::function<void()> finishCallback;

public:
    IntervalTimer(float seconds, std::function<void()> onFinish) : finishCallback(std::move(onFinish)){
        ticksLeft = seconds * ticksPerSec;
        intervalSeconds = seconds;
    }


    void tick() {
        ticksLeft--;
        if(ticksLeft <= 0){
            finishCallback();
            ticksLeft = intervalSeconds * ticksPerSec;
            std::cout << "ticks left " << ticksLeft << std::endl;

        }
    }

    void updateInterval(float newSeconds) {
        intervalSeconds = newSeconds;
        ticksLeft = newSeconds * ticksPerSec;
    }
};


#endif //GAME_INTERVALTIMER_H
