#pragma once

#include "SignalStrategy.h"

class DiscreteSignal : public SignalStrategy {
public:
    DiscreteSignal(double amp, double time0, double dur, double freq);
    std::pair<std::vector<double>, std::vector<double>> getSignal() override;
private:
    const double frequency;
};
