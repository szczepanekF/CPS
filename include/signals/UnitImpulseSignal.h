
#pragma once

#include "DiscreteSignal.h"
class UnitImpulseSignal : public DiscreteSignal {
public:
    UnitImpulseSignal(double amp, double time0, double dur, double freq, int jumpTime);

    double calculateSignalAt(double time) override;
    double getAmplitude() const;
private:
    double amplitude;
    int jumpTime;
};
