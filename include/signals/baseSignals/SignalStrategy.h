#pragma once

#include "Signal.h"

class SignalStrategy {
public:
    SignalStrategy(double time0, double dur);

    virtual ~SignalStrategy() = default;

    virtual double calculateSignalAt(double time);

    virtual Signal &getSignal();

    double getBeginTime() const;
    double getDuration() const;
    double getFrequency() const;
    void setSignal(const Signal &signal);
    void setFrequency(double freq);


protected:
    void calculateSignal();

private:

    double FREQUENCY;

    Signal signal;

    double duration;
    double beginTime;

};
