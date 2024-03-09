
#pragma once

#include "SignalStrategy.h"

class UnitJumpSignal : public SignalStrategy {
public:
    UnitJumpSignal(double amp, double time0, double dur, double jumpTime);

    double calculateSignalAt(double time) override;
private:
    double jumpTime;
};
