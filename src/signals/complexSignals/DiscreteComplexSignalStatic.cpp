
#include "signals/complexSignals/DiscreteComplexSignalStatic.h"

DiscreteComplexSignalStatic::DiscreteComplexSignalStatic(const std::vector<std::complex<double>> &samples, double freq)
        : DiscreteComplexSignal(0,static_cast<int>(samples.size()), freq), samples(samples) {}

std::complex<double> DiscreteComplexSignalStatic::calculateSignalAtSample(int n) {
    return samples[n];
}

std::vector<std::complex<double>> DiscreteComplexSignalStatic::getSamples() const {
    return samples;
}
