
#pragma once

#include "Quantization.h"

class QuantizationClipped : public Quantization {

public:
    QuantizationClipped(std::unique_ptr<Sampling> strategy, int quantizationLevels);


private:
    double typicalFunction(double& value) override;

};
