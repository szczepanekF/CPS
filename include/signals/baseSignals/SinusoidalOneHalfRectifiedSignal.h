#pragma once

#include "SinusoidalSignal.h"

class SinusoidalOneHalfRectifiedSignal : public SinusoidalSignal {
public:
    SinusoidalOneHalfRectifiedSignal(double amp, double time0, double dur, double basePeriod);

    double calculateSignalAt(double time) override;

};



