
#include "signals/Filters/ConvolutionSignal.h"

ConvolutionSignal::ConvolutionSignal(std::shared_ptr<DiscreteSignal> h, std::shared_ptr<DiscreteSignal> x)
        : DiscreteSignal(h->getBeginTime(), h->getNumberOfSamples() + x->getNumberOfSamples() - 1, h->getFrequency()),
          h(std::move(h)), x(std::move(x)) {}

double ConvolutionSignal::calculateSignalAtSample(int n) {
    double sum = 0;
    int start = std::max(0, n - x->getNumberOfSamples() + 1);
    int end = std::min(n + 1, h->getNumberOfSamples());

    for (int k = start; k < end; k++) {
        sum += h->calculateSignalAtSample(k) * x->calculateSignalAtSample(n - k);
    }
    return sum;
}






