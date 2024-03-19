
#include "signals/ContinousSignal.h"

ContinousSignal::ContinousSignal(double amp, double time0, double dur) : SignalStrategy(time0, dur), amplitude(amp) {}

Signal &ContinousSignal::getSignal() {
    calculateSignal();
    return SignalStrategy::getSignal();
}

double ContinousSignal::getAmplitude() const {
    return amplitude;
}



