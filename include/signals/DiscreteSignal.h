#pragma once

#include "SignalStrategy.h"

class DiscreteSignal : public SignalStrategy {
public:
    DiscreteSignal(double amp, double time0, double dur, double freq);
    Signal &getSignal() override;
};
