
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

    while (time < getBeginTime() + getDuration()) {
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

void SignalStrategy::setFrequency(double freq) {
    FREQUENCY = freq;
}

void SignalStrategy::setDuration(double newDuration) {
    duration = newDuration;
}

void SignalStrategy::setBeginTime(double time0) {
    beginTime = time0;
}



