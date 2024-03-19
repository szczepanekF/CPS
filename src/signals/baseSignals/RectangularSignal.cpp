#include "signals/baseSignals/RectangularSignal.h"

#include <cmath>

RectangularSignal::RectangularSignal(double amp, double time0, double dur, double basePeriod, double fillFactor)
        : ContinousSignal(time0, dur),amplitude(amp), basePeriod(basePeriod), fillFactor(fillFactor) {

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

double RectangularSignal::getAmplitude() const {
    return amplitude;
}
