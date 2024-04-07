
#include <iostream>
#include <cmath>
#include "signals/signalConversion/ADC/Sampling.h"

Sampling::Sampling(std::unique_ptr<ContinousSignal> strategy, double sampleRate)
: DiscreteSignal(strategy->getBeginTime(), strategy->getDuration(), sampleRate),
    strategy(std::move(strategy)) {

}


double Sampling::calculateSignalAt(double time) {
    double period = 1 / getFrequency();
    int nearestSample = round((time - getBeginTime()) / period );
    return strategy->calculateSignalAt(nearestSample * period + getBeginTime());
}

