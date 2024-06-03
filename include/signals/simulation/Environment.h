
#pragma once


#include "DistanceSensor.h"
#include "memory"

class Environment {

public:
    Environment(double signalVelocity, double echoVelocity, double distance, const float& timeStep,
                std::unique_ptr<DistanceSensor> distanceSensor);

    void step();
    const Signal& getProbingSignal();
    const Signal& getEchoSignal();
    const Signal& getCorrelationSignal();
    double getTimestamp();

    double getRealDistance();
    double getMeasuredDistance();
private:
    double signalVelocity;
    double echoVelocity;
    double distance;

    double timestamp;
    const float& timeStep;

    std::unique_ptr<DistanceSensor> distanceSensor;

};
