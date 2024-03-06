
#pragma once

#include <random>
#include "SignalStrategy.h"

class ImpulseNoise : public SignalStrategy {
public:
    ImpulseNoise(double amp, double time0, double dur, double freq, double prob);

    double calculateSignalAt(double time) override;

    ~ImpulseNoise() override = default;
private:
    double samplingFrequency;
    double probability;
};


