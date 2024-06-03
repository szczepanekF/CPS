
#include <utility>
#include <iostream>

#include "signals/baseSignals/OperationResultSignal.h"

OperationResultSignal::OperationResultSignal(std::unique_ptr<SignalStrategy> s1, std::unique_ptr<SignalStrategy> s2,
                                             std::function<double(double, double)> func)
        : ContinousSignal(0, std::min(s1->getDuration(),s2->getDuration())), firstSignal(std::move(s1)),
        secondSignal(std::move(s2)), operation(std::move(func)){

}

double OperationResultSignal::calculateSignalAt(double time) {
    return operation(firstSignal->calculateSignalAt(time), secondSignal->calculateSignalAt(time));
}

void OperationResultSignal::setBeginTime(double beginTime) {
    SignalStrategy::setBeginTime(beginTime);
    firstSignal->setBeginTime(beginTime);
    secondSignal->setBeginTime(beginTime);
}
