#include <Arduino.h>
#ifndef TIMER_H
#define TIMER_H

    unsigned long timerStart = 0;
    unsigned long timerTarget = 0;

    void startTimer(int msec)
    {
        timerStart = millis();
        timerTarget = msec;
    }

    bool isTimerReady()
    {
        return (millis() - timerStart) > timerTarget;
    }

#endif // TIMER_H
