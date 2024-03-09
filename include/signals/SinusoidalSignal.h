#pragma once


#include "ContinousSignal.h"

class SinusoidalSignal : public ContinousSignal {
public:
    SinusoidalSignal(double amp, double time0, double dur, double basePeriod);
    ~SinusoidalSignal() override = default;

    double calculateSignalAt(double time) override;
    double getBasePeriod() const;
private:
    double basePeriod;
};
