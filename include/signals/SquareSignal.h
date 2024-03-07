#pragma once

#include <random>
#include "SignalStrategy.h"

class SquareSignal : public SignalStrategy {
public:
    SquareSignal(double amp, double time0, double dur, double basePeriod, double fillFactor);

    double calculateSignalAt(double time) override;

    ~SquareSignal() override = default;
private:
    double amplitude;
    double basePeriod;
    double startTime;
    double signalDuration;
    double fillFactor;
};
