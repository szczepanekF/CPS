
#include "signals/complexSignals/ComplexSignal.h"

ComplexSignalValueType ComplexSignal::getType() const {
    return type;
}

void ComplexSignal::setType(ComplexSignalValueType newType) {
    Signal &sig = SignalStrategy::getSignal();
    sig.clear();
    ComplexSignal::type = newType;
}

ComplexSignal::ComplexSignal(double time0, double dur) : SignalStrategy(time0, dur), type(REAL) {}
