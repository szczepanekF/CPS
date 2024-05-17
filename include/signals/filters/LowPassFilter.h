
#pragma once


#include <memory>
#include "signals/baseSignals/DiscreteSignal.h"
#include "windows/Window.h"

class LowPassFilter : public DiscreteSignal {
public:
    explicit LowPassFilter(int M, double f0, double freq, std::unique_ptr<Window> window);
    double calculateSignalAtSample(int n) override;

protected:
    int M;
    double K;
    std::unique_ptr<Window> window;


};
