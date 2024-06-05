
#pragma once

#include "signals/baseSignals/ContinousSignal.h"
#include "signals/baseSignals/DiscreteSignal.h"
#include "Reconstruction.h"
#include <memory>

class ReconstructionZeroOrderHold : public Reconstruction {

public:
    explicit ReconstructionZeroOrderHold(std::unique_ptr<DiscreteSignal> strategy);

    double calculateSignalAt(double time) override;

};
