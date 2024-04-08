
#pragma once

#include "signals/baseSignals/ContinousSignal.h"
#include "signals/baseSignals/DiscreteSignal.h"
#include "Reconstruction.h"
#include <memory>

class ReconstructionSincBased : public Reconstruction {


public:
    ReconstructionSincBased(std::unique_ptr<DiscreteSignal> strategy, int n);

    double calculateSignalAt(double time) override;

private:
    static double sinc(double time);
    int N;
};
