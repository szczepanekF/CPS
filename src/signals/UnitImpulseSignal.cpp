

#include <cmath>
#include "signals/UnitImpulseSignal.h"

UnitImpulseSignal::UnitImpulseSignal(double amp, double time0, double dur, double freq, double jumpTime)
        : DiscreteSignal(amp, time0, dur, freq), jumpTime(jumpTime) {

}

double UnitImpulseSignal::calculateSignalAt(double time) {
    return std::fabs(time - jumpTime) < 0.001  ? getAmplitude() : 0;
}
