#pragma once

#include "signals/Signal.h"

class SignalStrategy {
public:
    SignalStrategy(double amp, double time0, double dur);

    virtual ~SignalStrategy() = default;

    virtual double calculateSignalAt(double time);

    virtual Signal &getSignal();
    double getAmplitude() const;
    double getBeginTime() const;
    double getDuration() const;
    int getSampleCount() const;

    void setSignal(const Signal &signal);
    void setSampleCount(int sampleCount);


protected:
    void calculateSignal();

private:

    int SAMPLE_COUNT;

    Signal signal;

    double duration;
    double beginTime;
    double amplitude;
};
