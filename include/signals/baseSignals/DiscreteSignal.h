#pragma once

#include "SignalStrategy.h"

class DiscreteSignal : public SignalStrategy {
public:
    DiscreteSignal(double time0, double dur, double freq);

    DiscreteSignal(double time0, int numberOfSamples, double freq);

    Signal &getSignal() override;

    void calculateSignal() override;

    virtual double calculateSignalAtSample(int n) = 0;

    virtual int getNumberOfSamples() const;

private:
    int numberOfSamples;


};
