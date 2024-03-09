#include "signals/SquareSignal.h"

#include <cmath>

SquareSignal::SquareSignal(double amp, double time0, double dur, double basePeriod, double fillFactor)
        : SignalStrategy(amp, time0, dur), basePeriod(basePeriod), fillFactor(fillFactor) {

}


double SquareSignal::calculateSignalAt(double time) {
    if (((time - beginTime) / basePeriod - floor((time - beginTime) / basePeriod)) < fillFactor) {
        return amplitude;
    }
    return 0;
}