
#pragma once

#include "DiscreteSignal.h"

class DiscreteSignalStatic : public DiscreteSignal {
public:
    DiscreteSignalStatic(const std::vector<double>& samples, double frequency);

    double calculateSignalAtSample(int n) override;

private:
    const std::vector<double> samples;
};
