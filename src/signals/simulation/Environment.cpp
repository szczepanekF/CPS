
#include <iostream>
#include "signals/simulation/Environment.h"

Environment::Environment(double signalVelocity, double echoVelocity, double distance,
                         const float &timeStep, std::unique_ptr<DistanceSensor> distanceSensor)
        : signalVelocity(signalVelocity), echoVelocity(echoVelocity), distance(distance), timestamp(0),
          timeStep(timeStep), distanceSensor(std::move(distanceSensor)) {}

void Environment::step() {
    timestamp += timeStep;

    distance += echoVelocity * timeStep;

    double delay = distance / signalVelocity * 2.0;

    std::unique_ptr<ContinousSignal> echoSignal = distanceSensor->createProbingSignal();
    echoSignal->setBeginTime(echoSignal->getBeginTime() + delay);

    distanceSensor->update(std::move(echoSignal), timestamp, signalVelocity);
}

const Signal &Environment::getProbingSignal() {
    return distanceSensor->getProbingSignal();
}

const Signal &Environment::getEchoSignal() {
    return distanceSensor->getEchoSignal();
}

const Signal &Environment::getCorrelationSignal() {
    return distanceSensor->getCorrelationSignal();
}

double Environment::getTimestamp() const {
    return timestamp;
}

double Environment::getRealDistance() const {
    return distance;
}

double Environment::getMeasuredDistance() {
    return distanceSensor->getMeasuredDistance();
}
