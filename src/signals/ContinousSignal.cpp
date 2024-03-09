
#include "signals/ContinousSignal.h"

ContinousSignal::ContinousSignal(double amp, double time0, double dur) : SignalStrategy(amp, time0, dur) {}

std::pair<std::vector<double>, std::vector<double>> ContinousSignal::getSignal() {
    double diff = getDuration() / SAMPLE_COUNT;
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


