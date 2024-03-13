
#include "signals/ContinousSignal.h"

ContinousSignal::ContinousSignal(double amp, double time0, double dur) : SignalStrategy(amp, time0, dur) {}

Signal ContinousSignal::getSignal() {
    double diff = getDuration() / SAMPLE_COUNT;
    double time = getBeginTime();
    Signal signal;
    while (time < getBeginTime() + getDuration()) {
        signal.signalValues.push_back(calculateSignalAt(time));
        signal.timeValues.push_back(time);
        time += diff;
    }
    return signal;

}


