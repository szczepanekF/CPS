
#pragma once

#include "signals/baseSignals/DiscreteSignal.h"
#include "signals/baseSignals/ContinousSignal.h"
#include <memory>

class ReconstructionFirstOrderHold : public ContinousSignal {
public:
    ReconstructionFirstOrderHold(std::unique_ptr<DiscreteSignal> strategy);

    double calculateSignalAt(double time) override;

private:
    std::unique_ptr<DiscreteSignal> strategy;

};
