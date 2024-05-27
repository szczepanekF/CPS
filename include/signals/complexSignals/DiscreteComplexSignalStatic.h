
#pragma once


#include "DiscreteComplexSignal.h"

class DiscreteComplexSignalStatic : public DiscreteComplexSignal {
public:
    DiscreteComplexSignalStatic(const std::vector<std::complex<double>> &samples, double freq);

    std::complex<double> calculateSignalAtSample(int n) override;
    std::vector<std::complex<double>> getSamples() const override;
private:
    const std::vector<std::complex<double>> samples;

};
