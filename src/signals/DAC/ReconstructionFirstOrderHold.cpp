
#include <cmath>
#include "signals/DAC/ReconstructionFirstOrderHold.h"

ReconstructionFirstOrderHold::ReconstructionFirstOrderHold(std::unique_ptr<DiscreteSignal> strategy)
        : ContinousSignal(strategy->getBeginTime(), strategy->getDuration()), strategy(std::move(strategy)) {

}

double ReconstructionFirstOrderHold::calculateSignalAt(double time) {
    double diff = 1 / strategy->getFrequency();
    double part = (time - getBeginTime()) / diff - std::floor((time - getBeginTime()) / diff);
    if (time + diff <= getDuration()) {
//TODO CHECK IT
        return (strategy->calculateSignalAt(time + diff) - strategy->calculateSignalAt(time)) * part + strategy->calculateSignalAt(time);
    }

    return strategy->calculateSignalAt(time);
}
