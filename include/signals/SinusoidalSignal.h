#pragma once

#include <random>
#include "SignalStrategy.h"

class SinusoidalSignal : public SignalStrategy {
public:
    SinusoidalSignal(double amp, double time0, double dur, double basePeriod);

    double calculateSignalAt(double time) override;

    ~SinusoidalSignal() override = default;
private:
    double basePeriod;
};
