
#include "simulation/Environment.h"

Environment::Environment(double signalVelocity, double echoVelocity, double distance,
                         double timeStep, std::unique_ptr<DistanceSensor> distanceSensor)
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
