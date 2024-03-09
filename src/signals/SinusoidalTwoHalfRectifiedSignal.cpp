#include "signals/SinusoidalTwoHalfRectifiedSignal.h"
#include <cmath>
SinusoidalTwoHalfRectifiedSignal::SinusoidalTwoHalfRectifiedSignal(double amp, double time0, double dur,
                                                                   double basePeriod)
        : SinusoidalSignal(amp, time0, dur, basePeriod) {}

double SinusoidalTwoHalfRectifiedSignal::calculateSignalAt(double time) {
    double angularSpeed = (2 * M_PI) / getBasePeriod();
    double timeDifference = time - getBeginTime();
    return getAmplitude() * std::abs(sin(angularSpeed * timeDifference));
}
