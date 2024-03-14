#include "signals/SinusoidalOneHalfRectifiedSignal.h"
#include <cmath>

SinusoidalOneHalfRectifiedSignal::SinusoidalOneHalfRectifiedSignal(double amp, double time0, double dur,
                                                                   double basePeriod)
        : SinusoidalSignal(amp, time0, dur, basePeriod) {

}

double SinusoidalOneHalfRectifiedSignal::calculateSignalAt(double time) {
    double angularSpeed = (2 * M_PI) / getBasePeriod();
    double timeDifference = time - getBeginTime();
    double sinusSum = sin(angularSpeed * timeDifference) + std::abs(sin(angularSpeed * timeDifference));
    return 0.5 * getAmplitude() * sinusSum;
}

