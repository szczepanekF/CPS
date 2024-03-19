
#include <cmath>
#include "signals/DAC/ReconstructionSincBased.h"

ReconstructionSincBased::ReconstructionSincBased(std::unique_ptr<DiscreteSignal> strategy, int n)
        : ContinousSignal(strategy->getBeginTime(), strategy->getDuration()), N(n), strategy(std::move(strategy)) {

}

double ReconstructionSincBased::calculateSignalAt(double time) {
    double diff = 1 / strategy->getFrequency();
    double endTime = getBeginTime() + getDuration();
    double left = time - diff * N / 2;
    double right = time + diff * N;
    if (left < getBeginTime()) {
        right = right - (left - getBeginTime());
        right = std::min(endTime, right);
        left = getBeginTime();
    } else if (right > endTime) {
        left = left - (right - endTime);
        left = std::max(getBeginTime(), left);
        right = getBeginTime() + getDuration();
    }
    double sum = 0;
    while (left <= right) {
        //TODO CHECK THIS AS WELL
        sum += strategy->calculateSignalAt(left) *
               sinc(time * strategy->getFrequency() - std::floor((left - getBeginTime()) * strategy->getFrequency()));
        left += diff;
    }

    return strategy->calculateSignalAt(time);
}

double ReconstructionSincBased::sinc(double time) {
    if (time == 0) {
        return 1;
    }
    return std::sin(M_PI * time) / (M_PI * time);
}


