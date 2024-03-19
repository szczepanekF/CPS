#pragma once

#include "SignalStrategy.h"

class ContinousSignal : public SignalStrategy {
public:
    ContinousSignal(double amp, double time0, double dur);
    double getAmplitude() const;
    Signal &getSignal() override;
private:
    double amplitude;
};
