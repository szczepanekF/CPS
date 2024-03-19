
#pragma once
#include "ContinousSignal.h"

class GaussianNoise : public ContinousSignal {
public:
    GaussianNoise(double amp, double time0, double dur);

    double calculateSignalAt(double time) override;

    ~GaussianNoise() override = default;
private:
    double amplitude;
};
