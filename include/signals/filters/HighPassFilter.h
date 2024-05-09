
#pragma once

#include "LowPassFilter.h"

class HighPassFilter : public LowPassFilter{
public:
    double calculateSignalAtSample(int n) override;

};
