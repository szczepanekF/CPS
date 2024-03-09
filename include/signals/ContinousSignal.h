#pragma once

#include "SignalStrategy.h"

class ContinousSignal : public SignalStrategy {
public:
    ContinousSignal(double amp, double time0, double dur);

    std::pair<std::vector<double>, std::vector<double>> getSignal() override;

private:
    static const int SAMPLE_COUNT = 10000;
};
