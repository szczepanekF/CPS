#include "signals/SignalStrategy.h"

SignalStrategy::SignalStrategy(double amp, double time0, double dur): FREQUENCY(1000), duration(dur), beginTime(time0), amplitude(amp) {
}

double SignalStrategy::getAmplitude() const {
    return amplitude;
}

double SignalStrategy::getBeginTime() const {
    return beginTime;
}

double SignalStrategy::getDuration() const {
    return duration;
}


Signal& SignalStrategy::getSignal() {

    return signal;
}

void SignalStrategy::calculateSignal() {
    double diff = 1 / FREQUENCY;
    double time = getBeginTime();
    while (time < getBeginTime() + getDuration()) {
        signal.signalValues.push_back(calculateSignalAt(time));
        signal.timeValues.push_back(time);
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



