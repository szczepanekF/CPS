#include "signals/SignalStrategy.h"

SignalStrategy::SignalStrategy(double amp, double time0, double dur) {
    amplitude = amp;
    beginTime = time0;
    duration = dur;
}

std::vector<double> SignalStrategy::getSignal() {

    double diff = duration / SAMPLE_COUNT;
    double time = beginTime;
    std::vector<double> signalValues;
    while (time < beginTime + duration) {
        signalValues.push_back(calculateSignalAt(time));
        time += diff;

    }
    return signalValues;
}

double SignalStrategy::getAmplitude() {
    return amplitude;
}
