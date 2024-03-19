
#pragma once

#include "ContinousSignal.h"

class UniformNoise : public ContinousSignal {
public:
    UniformNoise(double amp, double time0, double dur);

    double calculateSignalAt(double time) override;
    double getAmplitude() const;
private:
    double amplitude;
};



