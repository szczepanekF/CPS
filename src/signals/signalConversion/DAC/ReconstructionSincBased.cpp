
#include <cmath>
#include <iostream>
#include "signals/signalConversion/DAC/ReconstructionSincBased.h"

ReconstructionSincBased::ReconstructionSincBased(std::unique_ptr<DiscreteSignal> strategy, int n)
        : ContinousSignal(strategy->getBeginTime(), strategy->getDuration()), N(n), strategy(std::move(strategy)) {

}

double ReconstructionSincBased::calculateSignalAt(double time) {
    double period = 1 / strategy->getFrequency();
    int sampleCount = static_cast<int> (getDuration() * strategy->getFrequency());
    int nearestSampleInd = static_cast<int> (std::floor(time - getBeginTime()) * strategy->getFrequency());
    int left = nearestSampleInd - N / 2;
    int right = left + N;


    if (left < 0) {
        right = right - left;
        left = 0;
        right = std::min(sampleCount, right);

    } else if (right > sampleCount) {
        left = left - (right - sampleCount);

        right = sampleCount;
        left = std::max(0, left);

    }
    double sum = 0;
    while (left <= right) {
        sum += strategy->calculateSignalAt(left * period) * sinc(time / period - left);
        left++;
    }

    return sum;
}

double ReconstructionSincBased::sinc(double time) {
    if (time == 0) {
        return 1;
    }
    return std::sin(M_PI * time) / (M_PI * time);
}


