
#pragma once

#include <random>
#include "SignalStrategy.h"

class UniformNoise : public SignalStrategy {
public:
    UniformNoise(double amp, double time0, double dur);

    double calculateSignalAt(double time) override;

    ~UniformNoise() override = default;
};



