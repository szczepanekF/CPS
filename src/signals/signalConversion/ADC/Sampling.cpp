
#include <cmath>
#include "signals/signalConversion/ADC/Sampling.h"

Sampling::Sampling(std::unique_ptr<ContinousSignal> strategy, double sampleRate)
        : DiscreteSignal(strategy->getBeginTime(), strategy->getDuration(), sampleRate),
          strategy(std::move(strategy)) {
}


double Sampling::calculateSignalAtSample(int n) {
    double time = n / getFrequency() + getBeginTime();
    return strategy->calculateSignalAt(time);
}

double Sampling::calculateSignalAt(double time) {
    return strategy->calculateSignalAt(time);
}


