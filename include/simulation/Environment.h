
#pragma once


#include "DistanceSensor.h"
#include "memory"

class Environment {

public:
    Environment(double signalVelocity, double echoVelocity, double distance, double timeStep,
                std::unique_ptr<DistanceSensor> distanceSensor);

    void step();





private:
    double signalVelocity;
    double echoVelocity;
    double distance;

    double timestamp;
    double timeStep;

    std::unique_ptr<DistanceSensor> distanceSensor;

};
