#include <cmath>
#include "signals/filters/LowPassFilter.h"

double LowPassFilter::calculateSignalAtSample(int n) {
    int halfM = (M - 1) / 2;
    if (n == halfM) {
        return 2.0 / K;
    }

    return sin(2 * M_PI * (n - halfM) / K) / (M_PI *  (n -halfM));
}

LowPassFilter::LowPassFilter(int M, double f0, double freq, std::shared_ptr<Window> window)
        : DiscreteSignal(0, M, freq), M(M), K(static_cast<int>(freq / f0)),
          window(std::move(window)) {


}
