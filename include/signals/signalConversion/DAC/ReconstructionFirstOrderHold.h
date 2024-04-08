
#pragma once

#include "signals/baseSignals/DiscreteSignal.h"
#include "signals/baseSignals/ContinousSignal.h"
#include "Reconstruction.h"
#include <memory>

class ReconstructionFirstOrderHold : public Reconstruction {
public:
    ReconstructionFirstOrderHold(std::unique_ptr<DiscreteSignal> strategy);

    double calculateSignalAt(double time) override;
};
