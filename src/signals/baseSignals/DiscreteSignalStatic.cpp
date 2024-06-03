
#include "signals/baseSignals/DiscreteSignalStatic.h"

DiscreteSignalStatic::DiscreteSignalStatic(const std::vector<double> &samples, double frequency)
        : DiscreteSignal(0, static_cast<int>(samples.size()), frequency),
          samples(samples.begin(), samples.end()) {

}

double DiscreteSignalStatic::calculateSignalAtSample(int n) {
    if (n > getNumberOfSamples()) return 0;
    return samples[n];
}
