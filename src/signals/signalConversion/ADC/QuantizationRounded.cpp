
#include <cmath>
#include "signals/signalConversion/ADC/QuantizationRounded.h"

QuantizationRounded::QuantizationRounded(std::unique_ptr<Sampling> strategy, int quantizationLevels)
        : Quantization(std::move(strategy), quantizationLevels) {}

double QuantizationRounded::typicalFunction(double& value) {
    return std::round(value);
}

