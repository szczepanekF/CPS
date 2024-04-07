#include "signals/baseSignals/SinusoidalSignal.h"
#include <cmath>
#include <iostream>

SinusoidalSignal::SinusoidalSignal(double amp, double time0, double dur, double basePeriod)
        : ContinousSignal(time0, dur), amplitude(amp), basePeriod(basePeriod) {

}


double SinusoidalSignal::calculateSignalAt(double time) {
    std::cout<<"SINUS" << "\n";
    double angularSpeed = (2 * M_PI) / getBasePeriod();
    double timeDifference = time - getBeginTime();
    return getAmplitude() * sin(angularSpeed * timeDifference);
}

double SinusoidalSignal::getBasePeriod() const {
    return basePeriod;
}

double SinusoidalSignal::getAmplitude() const {
    return amplitude;
}
