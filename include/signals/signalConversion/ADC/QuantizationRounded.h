
#pragma once
#include "Quantization.h"

class QuantizationRounded : public Quantization{
public:
    QuantizationRounded(std::unique_ptr<Sampling> strategy, int quantizationLevels);


private:
    double typicalFunction(double& value) override;
};
