
#include "signals/DiscreteSignal.h"

DiscreteSignal::DiscreteSignal(double amp, double time0, double dur, double frequency)
        : SignalStrategy(amp, time0, dur), frequency(frequency) {
}

Signal DiscreteSignal::getSignal() {
    double diff = 1 / frequency;
    double time = getBeginTime();
    Signal signal;
    while (time < getBeginTime() + getDuration()) {
        signal.signalValues.push_back(calculateSignalAt(time));
        signal.timeValues.push_back(time);
        time += diff;
    }
    return signal;

}
