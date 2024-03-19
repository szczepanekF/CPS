
#pragma once
#include "Quantization.h"

class QuantizationRounded : public Quantization{
public:
    QuantizationRounded(std::unique_ptr<Sampling> strategy, int quantizationLevels);

private:
    int typicalFunction(double value) override;
};
