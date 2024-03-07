#include "signals/SquareSignal.h"

SquareSignal::SquareSignal(double amp, double time0, double dur, double basePeriod, double fillFactor)
:SignalStrategy(amp, time0, dur), basePeriod(basePeriod), fillFactor(fillFactor) {}


double SquareSignal::calculateSignalAt(double time) {
    int k = 2; // idk co to jest za parametr, mial nalezec do calkowitych, do ustalenia
    if(time >= k*basePeriod + startTime && time < basePeriod * fillFactor + k*basePeriod + startTime) {
        return amplitude;
    } else if(time >= fillFactor*basePeriod - k*basePeriod + startTime && time < basePeriod + k*basePeriod + startTime) {
        return 0;
    }
}