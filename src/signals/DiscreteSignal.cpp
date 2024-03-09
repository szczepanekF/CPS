
#include "signals/DiscreteSignal.h"

DiscreteSignal::DiscreteSignal(double amp, double time0, double dur, double frequency)
        : SignalStrategy(amp, time0, dur), frequency(frequency) {
}
