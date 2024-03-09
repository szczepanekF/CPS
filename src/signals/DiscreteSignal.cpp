
#include "signals/DiscreteSignal.h"

DiscreteSignal::DiscreteSignal(double amp, double time0, double dur, double frequency)
        : SignalStrategy(amp, time0, dur), frequency(frequency) {
}

std::pair<std::vector<double>, std::vector<double>> DiscreteSignal::getSignal() {
    double diff = 1 / frequency;
    double time = getBeginTime();
    std::vector<double> signalValues;
    std::vector<double> timeValues;
    while (time < getBeginTime() + getDuration()) {
        signalValues.push_back(calculateSignalAt(time));
        timeValues.push_back(time);
        time += diff;
    }
    return std::make_pair(timeValues, signalValues);

}
