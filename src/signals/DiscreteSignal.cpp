
#include "signals/DiscreteSignal.h"
#include <cmath>
DiscreteSignal::DiscreteSignal(double amp, double time0, double dur, double frequency)
        : SignalStrategy(amp, time0, dur) {
    setFrequency(frequency);
}

Signal &DiscreteSignal::getSignal() {
    calculateSignal();
    return SignalStrategy::getSignal();
}

