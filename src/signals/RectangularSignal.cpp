#include "signals/RectangularSignal.h"

#include <cmath>

RectangularSignal::RectangularSignal(double amp, double time0, double dur, double basePeriod, double fillFactor)
        : SignalStrategy(amp, time0, dur), basePeriod(basePeriod), fillFactor(fillFactor) {

}


double RectangularSignal::calculateSignalAt(double time) {
    double beginTime = getBeginTime();
    double period = getBasePeriod();
    double timeToPeriodRatio = (time - beginTime) / period;
    int periodNumber = floor(timeToPeriodRatio);
    if (timeToPeriodRatio - periodNumber < getFillFactor()) {
        return getAmplitude();
    }
    return 0;
}

double RectangularSignal::getBasePeriod() const {
    return basePeriod;
}

double RectangularSignal::getFillFactor() const {
    return fillFactor;
}
