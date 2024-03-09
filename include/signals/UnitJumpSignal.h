
#pragma once

#include "ContinousSignal.h"

class UnitJumpSignal : public ContinousSignal {
public:
    UnitJumpSignal(double amp, double time0, double dur, double jumpTime);

    double calculateSignalAt(double time) override;
private:
    double jumpTime;
};
