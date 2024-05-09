
#include "signals/filters/HighPassFilter.h"

double HighPassFilter::calculateSignalAtSample(int n) {
    int multiplier = n % 2 ? -1 : 1;
    return LowPassFilter::calculateSignalAtSample(n) * (n & 1) * multiplier;
}
