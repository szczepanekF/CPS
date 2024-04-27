
#include "signals/signalConversion//ADC/Quantization.h"
#include <limits>
#include <cmath>
#include <algorithm>
#include <iostream>

Quantization::Quantization(std::unique_ptr<Sampling> strategy, int quantLevelCount)
        : DiscreteSignal(strategy->getBeginTime(), strategy->getDuration(), strategy->getFrequency()),
          strategy(std::move(strategy)) {
    initQuantizationLevels(quantLevelCount);
}


double Quantization::calculateSignalAt(double time) {
    double valToClip =
            (strategy->calculateSignalAt(time) - levels.front()) / (levels.back() - levels.front()) *
            (levels.size() - 1);

    int index = static_cast<int> (typicalFunction(valToClip));
    return levels[index];
}

void Quantization::initQuantizationLevels(int quantLevelCount) {
    double max = std::numeric_limits<double>::min();
    double min = std::numeric_limits<double>::max();
    double diff = 1 / getFrequency();
    double currentTime = getBeginTime();

    while (currentTime <= getBeginTime() + getDuration()) {
        double value = strategy->calculateSignalAt(currentTime);
        max = std::max(max, value);
        min = std::min(min, value);
        currentTime += diff;
    }

    double step = (max - min) / (quantLevelCount - 1);
    levels.resize(quantLevelCount);

    std::ranges::generate(levels, [min, step, i = 0]()mutable { return min + (i++) * step; });
}



