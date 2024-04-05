
#include <cmath>
#include "signals/signalConversion/ADC/QuantizationClipped.h"

QuantizationClipped::QuantizationClipped(std::unique_ptr<Sampling> strategy, int quantizationLevels)
        : Quantization(std::move(strategy), quantizationLevels) {}

int QuantizationClipped::typicalFunction(double value) {
    return static_cast<int>(std::floor(value));
}
