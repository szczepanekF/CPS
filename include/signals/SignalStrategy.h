#pragma once
#include <vector>
#include "signals/Signal.h"
class SignalStrategy {
public:
    SignalStrategy(double amp, double time0, double dur);
    virtual ~SignalStrategy() = default;

    virtual double calculateSignalAt(double time) = 0;
    virtual Signal getSignal() = 0;

    double getAmplitude() const;
    double getBeginTime() const;
    double getDuration() const;

private:
    double duration;
    double beginTime;
    double amplitude;

};
