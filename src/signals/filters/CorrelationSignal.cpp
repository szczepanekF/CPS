
#include "signals/filters/CorrelationSignal.h"

CorrelationSignal::CorrelationSignal(std::shared_ptr<DiscreteSignal> h, std::shared_ptr<DiscreteSignal> x)
        : DiscreteSignal(h->getBeginTime(), h->getNumberOfSamples() + x->getNumberOfSamples() - 1, h->getFrequency()),
          h(std::move(h)), x(std::move(x)) {}

double CorrelationSignal::calculateSignalAtSample(int n) {
    n = n - (x->getNumberOfSamples() - 1);

    double sum = 0;
    int start = std::max(0, n);
    int end = std::min(n + x->getNumberOfSamples(), h->getNumberOfSamples());

    for (int k = start; k < end; k++) {
        sum += h->calculateSignalAtSample(k) * x->calculateSignalAtSample(k - n);
    }
    return sum;
}