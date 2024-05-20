
#include "signals/filters/HighPassFilter.h"

double HighPassFilter::calculateSignalAtSample(int n) {
    int multiplier = n % 2 ? -1 : 1;
    return LowPassFilter::calculateSignalAtSample(n) * multiplier;
}

HighPassFilter::HighPassFilter(int m, double f0, double freq, std::unique_ptr<Window> window) : LowPassFilter(m,f0,freq,
                                                                                                              std::move(window)) {

}
