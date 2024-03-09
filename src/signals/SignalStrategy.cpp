#include "signals/SignalStrategy.h"

SignalStrategy::SignalStrategy(double amp, double time0, double dur):duration(dur), beginTime(time0), amplitude(amp) {}

double SignalStrategy::getAmplitude() const {
    return amplitude;
}

double SignalStrategy::getBeginTime() const {
    return beginTime;
}

double SignalStrategy::getDuration() const {
    return duration;
}
