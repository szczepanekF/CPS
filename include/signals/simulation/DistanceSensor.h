
#pragma once


#include <memory>
#include "signals/baseSignals/ContinousSignal.h"
#include "signals/signalConversion/ADC/Sampling.h"
#include "signals/filters/CorrelationSignal.h"

class DistanceSensor {


public:
    DistanceSensor(double samplingFrequency, double probingSignalPeriod, int bufferLength, double reportingPeriod);

    std::unique_ptr<ContinousSignal> createProbingSignal();

    void update(std::unique_ptr<ContinousSignal> echoSignal, double timestamp, double signalVelocity);
    const Signal& getProbingSignal();
    const Signal& getEchoSignal();
    const Signal& getCorrelationSignal();
    double getMeasuredDistance() const;
private:
    void calculateDistance(std::unique_ptr<Sampling> sampledProbeSignal, std::unique_ptr<Sampling> sampledEchoSignal,
                           double signalVelocity);

    double samplingFrequency;
    double probingSignalPeriod;
    int bufferLength;
    double reportingPeriod;
    double lastMeasuermentTimestamp;

    double distance;
    Signal probingSignal;
    Signal echoSignal;
    Signal correlationSignal;


};
