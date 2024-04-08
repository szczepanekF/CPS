
#pragma once
#include "memory"

#include "signals/baseSignals/ContinousSignal.h"
#include "signals/baseSignals/DiscreteSignal.h"


class Reconstruction : public ContinousSignal {
public:
    explicit Reconstruction(std::unique_ptr<DiscreteSignal> strategy);

protected:
    std::unique_ptr<DiscreteSignal> strategy;

};

