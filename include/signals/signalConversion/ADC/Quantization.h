
#pragma once

#include "signals/baseSignals/DiscreteSignal.h"
#include "Sampling.h"
#include <memory>

class Quantization : public DiscreteSignal {
public:
    Quantization(std::unique_ptr<Sampling> strategy, int quantizationLevels);


    double calculateSignalAtSample(int n) override;

private:
    virtual double typicalFunction(double& value) = 0;
    void initQuantizationLevels(int levels);
    std::vector<double> levels;
    std::unique_ptr<Sampling> strategy;
};
