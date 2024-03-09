
#pragma once

#include "DiscreteSignal.h"
class UnitImpulseSignal : public DiscreteSignal {
public:
    UnitImpulseSignal(double amp, double time0, double dur, double freq, double jumpTime);

    double calculateSignalAt(double time) override;
private:
    double jumpTime;
};
