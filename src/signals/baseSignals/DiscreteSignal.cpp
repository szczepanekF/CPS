
#include "signals/baseSignals/DiscreteSignal.h"
#include <cmath>

DiscreteSignal::DiscreteSignal(double time0, double dur, double frequency)
        : SignalStrategy(time0, dur) {

    setFrequency(frequency);

}



Signal &DiscreteSignal::getSignal() {
    calculateSignal();
    return SignalStrategy::getSignal();
}

