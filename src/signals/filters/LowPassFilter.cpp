#include <cmath>
#include "signals/filters/LowPassFilter.h"

double LowPassFilter::calculateSignalAtSample(int n) {

    int halfM = (M - 1) / 2;
    if (n == halfM) {
        return (2.0 / K) * window->w(n);
    }

    return (sin(2.0 * M_PI * (n - halfM) / K) / (M_PI * (n - halfM))) * window->w(n);
}

LowPassFilter::LowPassFilter(int M, double f0, double freq, std::unique_ptr<Window> window)
        : DiscreteSignal(0, M, freq), M(M), K(freq / f0),
          window(std::move(window)) {


}
