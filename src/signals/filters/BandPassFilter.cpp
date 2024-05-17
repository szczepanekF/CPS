#include <cmath>
#include "signals/filters/BandPassFilter.h"

double BandPassFilter::calculateSignalAtSample(int n) {
    return LowPassFilter::calculateSignalAtSample(n) * 2 * sin(M_PI * n / 2);
}

BandPassFilter::BandPassFilter(int m, double f0, double freq, std::unique_ptr<Window> window) : LowPassFilter(m,f0,freq,
                                                                                                                     std::move(window)) {}
