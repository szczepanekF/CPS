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
    void setFrequency(double freq);


    virtual void calculateSignal();


private:
    Signal signal;
    double FREQUENCY;



    double duration;
    double beginTime;

};
