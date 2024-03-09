
#pragma once

#include "SignalStrategy.h"
class UnitImpulseSignal : public SignalStrategy {
public:
    UnitImpulseSignal(double amp, double time0, double dur, double jumpTime);

    double calculateSignalAt(double time) override;
private:
    double jumpTime;
};
