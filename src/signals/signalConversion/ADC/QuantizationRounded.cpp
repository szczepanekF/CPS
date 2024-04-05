
#include <cmath>
#include "signals/signalConversion/ADC/QuantizationRounded.h"

QuantizationRounded::QuantizationRounded(std::unique_ptr<Sampling> strategy, int quantizationLevels)
        : Quantization(std::move(strategy), quantizationLevels) {}

int QuantizationRounded::typicalFunction(double value) {
    return static_cast<int>(std::round(value));
}
