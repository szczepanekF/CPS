
#include "signals/signalConversion//ADC/Quantization.h"
#include <limits>
#include <cmath>
#include <algorithm>


Quantization::Quantization(std::unique_ptr<Sampling> strategy, int quantLevelCount)
        : DiscreteSignal(strategy->getBeginTime(), strategy->getNumberOfSamples(), strategy->getFrequency()),
          strategy(std::move(strategy)) {
    initQuantizationLevels(quantLevelCount);
}


void Quantization::initQuantizationLevels(int quantLevelCount) {
    double max = std::numeric_limits<double>::min();
    double min = std::numeric_limits<double>::max();
    int sample = 0;

    while (sample < getNumberOfSamples()) {
        double value = strategy->calculateSignalAtSample(sample);
        max = std::max(max, value);
        min = std::min(min, value);
        sample++;
    }

    double step = (max - min) / (quantLevelCount - 1);
    levels.resize(quantLevelCount);

    std::ranges::generate(levels, [min, step, i = 0]()mutable { return min + (i++) * step; });
}

double Quantization::calculateSignalAtSample(int n) {
    double valToClip =
            (strategy->calculateSignalAtSample(n) - levels.front()) / (levels.back() - levels.front()) *
            (levels.size() - 1);

    int index = static_cast<int> (typicalFunction(valToClip));

    return levels[index];
}



