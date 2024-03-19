

#include <cmath>
#include "signals/UnitImpulseSignal.h"

UnitImpulseSignal::UnitImpulseSignal(double amp, double time0, double dur, double freq, int jumpTime)
        : DiscreteSignal(time0, dur, freq), amplitude(amp), jumpTime(jumpTime) {

}

double UnitImpulseSignal::calculateSignalAt(double time) {
    int currentJumpNumber = std::floor((time - getBeginTime()) * getFrequency());

    return currentJumpNumber == (jumpTime - 1) ? amplitude : 0;
}

