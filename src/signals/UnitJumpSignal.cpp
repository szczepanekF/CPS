
#include "signals/UnitJumpSignal.h"

UnitJumpSignal::UnitJumpSignal(double amp, double time0, double dur, double jumpTime)
        : ContinousSignal(amp, time0, dur), jumpTime(jumpTime) {

}

double UnitJumpSignal::calculateSignalAt(double time) {
    if (time == jumpTime) {
        return getAmplitude() / 2;
    }
    return time > jumpTime ? getAmplitude() : 0;
}
