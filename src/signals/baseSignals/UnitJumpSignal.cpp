
#include <cmath>
#include "signals/baseSignals/UnitJumpSignal.h"

UnitJumpSignal::UnitJumpSignal(double amp, double time0, double dur, double jumpTime)
        : ContinousSignal(time0, dur), amplitude(amp), jumpTime(jumpTime) {

}

double UnitJumpSignal::calculateSignalAt(double time) {
    if (std::fabs(time - jumpTime) < 0.001) {
        return amplitude / 2;
    }
    return time > jumpTime ? amplitude : 0;
}
