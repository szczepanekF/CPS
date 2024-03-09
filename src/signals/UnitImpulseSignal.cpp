
#include "signals/UnitImpulseSignal.h"

UnitImpulseSignal::UnitImpulseSignal(double amp, double time0, double dur, double jumpTime)
        : SignalStrategy(amp, time0, dur), jumpTime(jumpTime) {

}

double UnitImpulseSignal::calculateSignalAt(double time) {
    return time == jumpTime ? getAmplitude() : 0;
}
