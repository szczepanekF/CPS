
#include <cmath>
#include <iostream>
#include "signals/signalConversion/DAC/ReconstructionZeroOrderHold.h"
ReconstructionZeroOrderHold::ReconstructionZeroOrderHold(std::unique_ptr<DiscreteSignal> strategy)
        : ContinousSignal(strategy->getBeginTime(), strategy->getDuration()), strategy(std::move(strategy)) {

}

double ReconstructionZeroOrderHold::calculateSignalAt(double time) {


    return strategy->calculateSignalAt(time);
}

