
#pragma once

#include "LowPassFilter.h"
class BandPassFilter : public LowPassFilter {
public:
    BandPassFilter(int m, double f0, double freq, std::unique_ptr<Window> window);

    double calculateSignalAtSample(int n) override;
};
