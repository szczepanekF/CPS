
#pragma once

#include "LowPassFilter.h"
class BandPassFilter : public LowPassFilter {
public:
    double calculateSignalAtSample(int n) override;
};
