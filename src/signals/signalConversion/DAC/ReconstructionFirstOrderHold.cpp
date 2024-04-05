
#include <cmath>
#include "signals/signalConversion/DAC/ReconstructionFirstOrderHold.h"

ReconstructionFirstOrderHold::ReconstructionFirstOrderHold(std::unique_ptr<DiscreteSignal> strategy)
        : ContinousSignal(strategy->getBeginTime(), strategy->getDuration()), strategy(std::move(strategy)) {

}

double ReconstructionFirstOrderHold::calculateSignalAt(double time) {
    double period = 1 / strategy->getFrequency();
    double part = (time - getBeginTime()) / period - std::floor((time - getBeginTime()) / period);
    if (time + period > getDuration()) {
        return strategy->calculateSignalAt(time);
    }
    return (strategy->calculateSignalAt(time + period) - strategy->calculateSignalAt(time)) * part +
           strategy->calculateSignalAt(time);
}
