#pragma once

#include "SignalStrategy.h"

class ContinousSignal : public SignalStrategy {
public:
    ContinousSignal(double amp, double time0, double dur);

    struct Signal getSignal() override;

private:
    const int SAMPLE_COUNT;
};
