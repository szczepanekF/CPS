
#pragma once
#include "DiscreteSignal.h"
#include "ContinousSignal.h"
#include <memory>

class Sampling : public DiscreteSignal {


public:
    Sampling(std::unique_ptr<ContinousSignal> strategy, double sampleCount);

    double calculateSignalAt(double time) override;

private:

    std::unique_ptr<ContinousSignal> strategy;

};
