
#include "signals/baseSignals/TriangularSignal.h"

TriangularSignal::TriangularSignal(double amp, double time0, double dur, double basePeriod, double fillFactor)
        : RectangularSignal(amp, time0, dur, basePeriod, fillFactor) {}

double TriangularSignal::calculateSignalAt(double time) {
    double beginTime = getBeginTime();
    double period = getBasePeriod();
    double timeToPeriodRatio = (time - beginTime) / period;
    int periodNumber = floor(timeToPeriodRatio);
    if (timeToPeriodRatio - periodNumber < getFillFactor()) {
        return getAmplitude() * (timeToPeriodRatio - periodNumber) / getFillFactor();
    }
    double ampFillRatio = getAmplitude() / (1 - getFillFactor());
    return -1 * ampFillRatio * (timeToPeriodRatio - periodNumber) + ampFillRatio;
}
