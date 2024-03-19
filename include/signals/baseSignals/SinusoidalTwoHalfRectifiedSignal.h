#pragma once

#include "SinusoidalSignal.h"
class SinusoidalTwoHalfRectifiedSignal : public SinusoidalSignal {
public:
    SinusoidalTwoHalfRectifiedSignal(double amp, double time0, double dur, double basePeriod);

    double calculateSignalAt(double time) override;

};
