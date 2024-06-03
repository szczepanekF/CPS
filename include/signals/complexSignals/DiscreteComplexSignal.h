
#pragma once
#include "ComplexSignal.h"
#include <complex>
class DiscreteComplexSignal : public ComplexSignal{
public:
    DiscreteComplexSignal(double time0, double dur, double freq);

    DiscreteComplexSignal(double time0, int numberOfSamples, double freq);
    virtual std::complex<double> calculateSignalAtSample(int n) = 0;
    Signal &getSignal() override;

    void calculateSignal() override;
    int getNumberOfSamples() const;
    virtual std::vector<std::complex<double>> getSamples() const = 0;

private:
    int numberOfSamples;

};
