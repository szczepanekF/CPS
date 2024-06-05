
#include <cmath>
#include "signals/signalConversion/ADC/QuantizationClipped.h"

QuantizationClipped::QuantizationClipped(std::unique_ptr<Sampling> strategy, int quantizationLevels)
        : Quantization(std::move(strategy), quantizationLevels) {}

double QuantizationClipped::typicalFunction(double &value) {
    return std::floor(value);
}
