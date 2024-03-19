
#pragma once

#include "RectangularSignal.h"
class RectangularSymmetricSignal : public RectangularSignal {
public:
    RectangularSymmetricSignal(double amp, double time0, double dur, double basePeriod, double fillFactor);

    double calculateSignalAt(double time) override;

};


