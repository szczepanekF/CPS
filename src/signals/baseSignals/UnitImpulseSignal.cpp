

#include <cmath>
#include "signals/baseSignals/UnitImpulseSignal.h"

UnitImpulseSignal::UnitImpulseSignal(double amp, double time0, double dur, double freq, int jumpTime)
        : DiscreteSignal(time0, dur, freq), amplitude(amp), jumpTime(jumpTime) {

}

double UnitImpulseSignal::calculateSignalAtSample(int n) {
    return n == (jumpTime - 1) ? amplitude : 0;
}



