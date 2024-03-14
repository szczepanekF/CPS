
#include "signals/ContinousSignal.h"

ContinousSignal::ContinousSignal(double amp, double time0, double dur) : SignalStrategy(amp, time0, dur) {}

Signal &ContinousSignal::getSignal() {
    calculateSignal();
    return SignalStrategy::getSignal();
}



