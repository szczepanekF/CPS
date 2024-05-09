
#pragma once

#include "DiscreteSignal.h"

class ImpulseNoise : public DiscreteSignal {
public:
    ImpulseNoise(double amp, double time0, double dur, double freq, double prob);

    double calculateSignalAtSample(int n) override;

    ~ImpulseNoise() override = default;
private:
    double amplitude;
    double probability;
};


