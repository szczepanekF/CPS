#include "signals/SignalStrategy.h"

SignalStrategy::SignalStrategy(double amp, double time0, double dur):duration(dur), beginTime(time0), amplitude(amp) {}

std::pair<std::vector<double>, std::vector<double>> SignalStrategy::getSignal() {

    double diff = duration / SAMPLE_COUNT;
    double time = beginTime;
    std::vector<double> signalValues;
    std::vector<double> timeValues;
    while (time < beginTime + duration) {
        signalValues.push_back(calculateSignalAt(time));
        timeValues.push_back(time);
        time += diff;
    }
    return std::make_pair(timeValues, signalValues);
}

double SignalStrategy::getAmplitude() {
    return amplitude;
}
