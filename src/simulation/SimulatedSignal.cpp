
#include <iostream>
#include "simulation/SimulatedSignal.h"

SimulatedSignal::SimulatedSignal(double beginTime, double duration, double period)
        : ContinousSignal(beginTime, duration),
          sinusoidalSignal(2, beginTime, duration, period),
          triangularSignal(2.5, beginTime, duration, period / 3.33, 0.3) {}
//
//          triangularSignal(0.5, beginTime, duration, period / 10) {}
double SimulatedSignal::calculateSignalAt(double time) {
    return sinusoidalSignal.calculateSignalAt(time) * triangularSignal.calculateSignalAt(time);

//    return sinusoidalSignal.calculateSignalAt(time) + triangularSignal.calculateSignalAt(time);
}

void SimulatedSignal::setBeginTime(double beginTime) {
    SignalStrategy::setBeginTime(beginTime);
    sinusoidalSignal.setBeginTime(beginTime);
    triangularSignal.setBeginTime(beginTime);
}

