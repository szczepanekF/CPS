
#include <iostream>
#include "simulation/SimulatedSignal.h"

SimulatedSignal::SimulatedSignal(double beginTime, double duration, double period)
        : ContinousSignal(beginTime, duration),
          sinusoidalSignal(1, beginTime, duration, period),
          triangularSignal(2.5, beginTime, duration, period / 3.33, 0.3) {}

double SimulatedSignal::calculateSignalAt(double time) {

    return sinusoidalSignal.calculateSignalAt(time) * triangularSignal.calculateSignalAt(time);
}

