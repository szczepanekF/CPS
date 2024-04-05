
#pragma once

#include "Quantization.h"

class QuantizationClipped : public Quantization {

public:
    QuantizationClipped(std::unique_ptr<Sampling> strategy, int quantizationLevels);

private:
    int typicalFunction(double value) override;

};
