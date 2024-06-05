
#include <cmath>

#include "signals/signalConversion/DAC/ReconstructionZeroOrderHold.h"

ReconstructionZeroOrderHold::ReconstructionZeroOrderHold(std::unique_ptr<DiscreteSignal> strategy)
        : Reconstruction(std::move(strategy)) {

}

double ReconstructionZeroOrderHold::calculateSignalAt(double time) {
    double period = 1 / strategy->getFrequency();
    double nearestSampleTime = std::floor((time - getBeginTime()) / period) * period + getBeginTime();
    return strategy->calculateSignalAt(nearestSampleTime);
}

