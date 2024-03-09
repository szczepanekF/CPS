#pragma once

#include "RectangularSignal.h"

class TriangularSignal : public RectangularSignal {
public:
    double calculateSignalAt(double time) override;

public:
    TriangularSignal(double amp, double time0, double dur, double basePeriod, double fillFactor);

};


