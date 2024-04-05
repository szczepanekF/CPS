
#pragma once
#include "signals/baseSignals/DiscreteSignal.h"
#include "signals/baseSignals/ContinousSignal.h"
#include <memory>

class Sampling : public DiscreteSignal {
public:
    Sampling(std::unique_ptr<ContinousSignal> strategy, double sampleRate);

    double calculateSignalAt(double time) override;

private:
    std::unique_ptr<ContinousSignal> strategy;

};
