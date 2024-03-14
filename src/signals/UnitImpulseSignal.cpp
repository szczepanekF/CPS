
#include <iostream>
#include "signals/UnitImpulseSignal.h"

UnitImpulseSignal::UnitImpulseSignal(double amp, double time0, double dur, double freq, double jumpTime)
        : DiscreteSignal(amp, time0, dur, freq), jumpTime(jumpTime) {

}

double UnitImpulseSignal::calculateSignalAt(double time) {
    std::cout<<time <<" " << jumpTime << "\n";
    return time == jumpTime ? getAmplitude() : 0;
}
