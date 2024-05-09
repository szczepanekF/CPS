#include <cmath>
#include "signals/filters/BandPassFilter.h"

double BandPassFilter::calculateSignalAtSample(int n) {
    return LowPassFilter::calculateSignalAtSample(n) * 2 * sin(M_PI * n / 2);
}
