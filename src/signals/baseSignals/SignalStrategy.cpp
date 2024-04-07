#include <iostream>
#include "signals/baseSignals/SignalStrategy.h"

SignalStrategy::SignalStrategy(double time0, double dur) : FREQUENCY(1000), duration(dur), beginTime(time0) {
}


double SignalStrategy::getBeginTime() const {
    return beginTime;
}

double SignalStrategy::getDuration() const {
    return duration;
}

Signal &SignalStrategy::getSignal() {
    return signal;
}

void SignalStrategy::calculateSignal() {
    double diff = 1 / FREQUENCY;
    double time = getBeginTime();

    while (time <= getBeginTime() + getDuration()) {
        signal.push_back(calculateSignalAt(time), time);
        time += diff;
    }
}

double SignalStrategy::calculateSignalAt(double) {
    return 0;
}

double SignalStrategy::getFrequency() const {
    return FREQUENCY;
}

void SignalStrategy::setSignal(const Signal &signal) {
    SignalStrategy::signal = signal;
}

void SignalStrategy::setFrequency(double freq) {
    FREQUENCY = freq;
}



