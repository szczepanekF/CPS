#include <numeric>
#include "simulation/DistanceSensor.h"
#include "simulation/SimulatedSignal.h"

DistanceSensor::DistanceSensor(double samplingFrequency, double probingSignalPeriod, int bufferLength,
                               double reportingPeriod)
        : samplingFrequency(samplingFrequency), probingSignalPeriod(probingSignalPeriod), bufferLength(bufferLength),
          reportingPeriod(reportingPeriod), lastMeasuermentTimestamp(std::numeric_limits<double>::lowest()),
          distance(0) {}

std::unique_ptr<ContinousSignal> DistanceSensor::createProbingSignal() {
    return std::make_unique<SimulatedSignal>(0, 0, probingSignalPeriod);
}

void DistanceSensor::update(std::unique_ptr<ContinousSignal> echoSignal, double timestamp, double signalVelocity) {
    double startTime = timestamp - bufferLength / samplingFrequency;
    std::unique_ptr<Sampling> sampledProbeSignal = std::make_unique<Sampling>(createProbingSignal(), samplingFrequency);
    std::unique_ptr<Sampling> sampledEchoSignal = std::make_unique<Sampling>(std::move(echoSignal), samplingFrequency);
    sampledProbeSignal->setBeginTime(startTime);
    sampledProbeSignal->setNumberOfSamples(bufferLength);
    sampledEchoSignal->setBeginTime(startTime);
    sampledEchoSignal->setNumberOfSamples(bufferLength);

    if (timestamp - lastMeasuermentTimestamp >= reportingPeriod) {
        lastMeasuermentTimestamp = timestamp;
        calculateDistance(std::move(sampledProbeSignal), std::move(sampledEchoSignal), signalVelocity);
    }
}

void DistanceSensor::calculateDistance(std::unique_ptr<Sampling> sampledProbeSignal, std::unique_ptr<Sampling> sampledEchoSignal,
                                       double signalVelocity) {
    CorrelationSignal sig(std::move(sampledEchoSignal), std::move(sampledProbeSignal));
    int maxIndex = sig.getNumberOfSamples() / 2;
    for (int i = maxIndex + 1; i < sig.getNumberOfSamples(); i++) {
        if (sig.calculateSignalAtSample(i) > sig.calculateSignalAtSample(maxIndex)) {
            maxIndex = i;
        }
    }

    double delay = (maxIndex - sig.getNumberOfSamples() / 2) / samplingFrequency;
    distance = delay * signalVelocity / 2.0;
}