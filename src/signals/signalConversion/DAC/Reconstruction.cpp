
#include "signals/signalConversion/DAC/Reconstruction.h"

Reconstruction::Reconstruction(std::unique_ptr<DiscreteSignal> strategy)
        : ContinousSignal(strategy->getBeginTime(), strategy->getDuration()), strategy(std::move(strategy)) {

}

