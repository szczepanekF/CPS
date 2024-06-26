
#include <cmath>

#include "signals/signalConversion/DAC/ReconstructionFirstOrderHold.h"

ReconstructionFirstOrderHold::ReconstructionFirstOrderHold(std::unique_ptr<DiscreteSignal> strategy)
        : Reconstruction(std::move(strategy)) {

}

double ReconstructionFirstOrderHold::calculateSignalAt(double time) {

    double period = 1 / strategy->getFrequency();

    double nearestSampleTime = std::floor((time - getBeginTime()) / period) * period + getBeginTime();
    if (nearestSampleTime + period > getBeginTime() + getDuration()) {

        return strategy->calculateSignalAt(nearestSampleTime);
    }
    double part = (time - getBeginTime()) / period - std::floor((time - getBeginTime()) / period);
    return (strategy->calculateSignalAt(nearestSampleTime + period) -
            strategy->calculateSignalAt(nearestSampleTime)) * part +
           strategy->calculateSignalAt(nearestSampleTime);
}
