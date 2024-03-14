#include "signals/SignalStrategy.h"

SignalStrategy::SignalStrategy(double amp, double time0, double dur): SAMPLE_COUNT(10000), duration(dur), beginTime(time0), amplitude(amp) {
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
    double diff = getDuration() / SAMPLE_COUNT;
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

int SignalStrategy::getSampleCount() const {
    return SAMPLE_COUNT;
}

void SignalStrategy::setSignal(const Signal &signal) {
    SignalStrategy::signal = signal;
}

void SignalStrategy::setSampleCount(int sampleCount) {
    SAMPLE_COUNT = sampleCount;
}



