
#include "signals/baseSignals/RectangularSymmetricSignal.h"

RectangularSymmetricSignal::RectangularSymmetricSignal(double amp, double time0, double dur, double basePeriod,
                                                       double fillFactor)
        : RectangularSignal(amp, time0, dur, basePeriod, fillFactor) {

}

double RectangularSymmetricSignal::calculateSignalAt(double time) {
    double beginTime = getBeginTime();
    double period = getBasePeriod();
    double timeToPeriodRatio = (time - beginTime) / period;
    int periodNumber = floor(timeToPeriodRatio);
    if (timeToPeriodRatio - periodNumber < getFillFactor()) {
        return getAmplitude();
    }
    return -getAmplitude();
}
