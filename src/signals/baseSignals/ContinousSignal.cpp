
#include "signals/baseSignals/ContinousSignal.h"

ContinousSignal::ContinousSignal(double time0, double dur) : SignalStrategy(time0, dur) {}

Signal &ContinousSignal::getSignal() {
    calculateSignal();
    return SignalStrategy::getSignal();
}




