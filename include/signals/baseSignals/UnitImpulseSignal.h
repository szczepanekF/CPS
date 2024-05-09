
#pragma once

#include "DiscreteSignal.h"
class UnitImpulseSignal : public DiscreteSignal {
public:
    UnitImpulseSignal(double amp, double time0, double dur, double freq, int jumpTime);

    double calculateSignalAtSample(int n) override;
private:
    double amplitude;
    int jumpTime;
};
