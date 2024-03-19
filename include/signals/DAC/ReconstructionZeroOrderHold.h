
#pragma once

#include "signals/baseSignals/ContinousSignal.h"
#include "signals/baseSignals/DiscreteSignal.h"
#include <memory>

class ReconstructionZeroOrderHold : public ContinousSignal {
    ReconstructionZeroOrderHold(std::unique_ptr<DiscreteSignal> strategy);

public:
    double calculateSignalAt(double time) override;

private:
    std::unique_ptr<DiscreteSignal> strategy;
};
