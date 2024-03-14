#pragma once

#include "signals/Signal.h"

class SignalStrategy {
public:
    SignalStrategy(double amp, double time0, double dur);

    virtual ~SignalStrategy() = default;

    virtual double calculateSignalAt(double time) = 0;

    Signal &getSignal();

    double getAmplitude() const;

    double getBeginTime() const;

    double getDuration() const;

protected:

    int SAMPLE_COUNT;
private:
    void calculateSignal();

    Signal signal;

    double duration;
    double beginTime;
    double amplitude;
};
