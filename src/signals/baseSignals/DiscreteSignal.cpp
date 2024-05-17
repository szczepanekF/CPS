
#include "signals/baseSignals/DiscreteSignal.h"
#include <cmath>

DiscreteSignal::DiscreteSignal(double time0, double dur, double frequency)
        : SignalStrategy(time0, dur) {
    setFrequency(frequency);
    this->numberOfSamples = static_cast<int>(dur * frequency);
}


Signal &DiscreteSignal::getSignal() {
    if (SignalStrategy::getSignal().empty()) {
        calculateSignal();
    }
    return SignalStrategy::getSignal();
}

DiscreteSignal::DiscreteSignal(double time0, int numberOfSamples, double freq)
        : SignalStrategy(time0, numberOfSamples / freq) {

    setFrequency(freq);
    this->numberOfSamples = numberOfSamples;
}

int DiscreteSignal::getNumberOfSamples() const {
    return numberOfSamples;
}

void DiscreteSignal::calculateSignal() {
    Signal &signal = SignalStrategy::getSignal();
    int i = 0;
    double period = 1 / getFrequency();
    while (i < getNumberOfSamples()) {
        signal.push_back(calculateSignalAtSample(i), i * period + getBeginTime());
        i++;
    }

}



