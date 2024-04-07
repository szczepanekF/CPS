
#include <cmath>
#include <iostream>
#include "signals/signalConversion/DAC/ReconstructionFirstOrderHold.h"

ReconstructionFirstOrderHold::ReconstructionFirstOrderHold(std::unique_ptr<DiscreteSignal> strategy)
        : ContinousSignal(strategy->getBeginTime(), strategy->getDuration()), strategy(std::move(strategy)) {

}

double ReconstructionFirstOrderHold::calculateSignalAt(double time) {
    double period = 1 / strategy->getFrequency();
    if (time + period > getBeginTime() + getDuration()) {
        return strategy->calculateSignalAt(time);
    }
//    std::cout<<strategy->calculateSignalAt(time);
    double part = (time - getBeginTime()) / period - std::floor((time - getBeginTime()) / period);
    std::cout<<strategy->calculateSignalAt(time + period) - strategy->calculateSignalAt(time) << '\n';
    return (strategy->calculateSignalAt(time + period) - strategy->calculateSignalAt(time)) * part +
           strategy->calculateSignalAt(time);
}
