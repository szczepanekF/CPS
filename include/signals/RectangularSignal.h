#pragma once

#include <random>
#include "SignalStrategy.h"

class RectangularSignal : public SignalStrategy {
public:
    RectangularSignal(double amp, double time0, double dur, double basePeriod, double fillFactor);

    double calculateSignalAt(double time) override;

    ~RectangularSignal() override = default;
private:
    double basePeriod;
public:
    double getBasePeriod() const;

    double getFillFactor() const;

private:
    double fillFactor;
};
