
#pragma once

#include "LowPassFilter.h"

class HighPassFilter : public LowPassFilter{
public:
    HighPassFilter(int m, double f0, double freq, std::unique_ptr<Window> window);

    double calculateSignalAtSample(int n) override;

};
