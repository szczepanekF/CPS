#include "signals/SinusoidalSignal.h"
#include <cmath>
SinusoidalSignal::SinusoidalSignal(double amp, double time0, double dur, double basePeriod)
:SignalStrategy(amp, time0, dur), basePeriod(basePeriod) {}


double SinusoidalSignal::calculateSignalAt(double time) {
    double angularSpeed = (2 * M_PI) / basePeriod;
    double timeDifference = time - beginTime;
    return amplitude * sin(angularSpeed * timeDifference);
}