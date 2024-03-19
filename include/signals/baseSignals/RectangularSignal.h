#pragma once

#include <random>
#include "ContinousSignal.h"

class RectangularSignal : public ContinousSignal {
public:
    RectangularSignal(double amp, double time0, double dur, double basePeriod, double fillFactor);

    double calculateSignalAt(double time) override;

    ~RectangularSignal() override = default;

    double getBasePeriod() const;
    double getFillFactor() const;

    double getAmplitude() const;
private:
    double amplitude;
    double basePeriod;
    double fillFactor;
};
