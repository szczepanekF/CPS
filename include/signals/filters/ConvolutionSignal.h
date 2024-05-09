
#pragma once

#include <memory>
#include "signals/baseSignals/DiscreteSignal.h"

class ConvolutionSignal : public DiscreteSignal {
public:
    ConvolutionSignal(std::shared_ptr<DiscreteSignal> h, std::shared_ptr<DiscreteSignal> x);

public:
    double calculateSignalAtSample(int n) override;



private:

    std::shared_ptr<DiscreteSignal> h;
    std::shared_ptr<DiscreteSignal> x;
};
