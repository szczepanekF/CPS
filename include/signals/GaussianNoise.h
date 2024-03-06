
#pragma once

#include <random>
#include "SignalStrategy.h"

class GaussianNoise : public SignalStrategy {
public:
    GaussianNoise(double amp, double time0, double dur);

    double calculateSignalAt(double time) override;

    ~GaussianNoise() override = default;
};
