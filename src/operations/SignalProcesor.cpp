#include <utility>

#include "operations/SignalProcesor.h"

SignalProcesor::SignalProcesor(std::unique_ptr<SignalStrategy> signalStrategy) : strategy(std::move(signalStrategy)), signalValues() {

}



Signal SignalProcesor::getCalculatedSignal(std::string &operationType) {
    Signal baseSignal = strategy->getSignal();
    Signal value;
    value.timeValues = baseSignal.timeValues;
    value.signalValues = baseSignal.signalValues;

    for (auto& sig : signalValues) {
        value = calculateSignalOperation(operationType, value, sig);
    }
    return value;
}


Signal SignalProcesor::calculateSignalOperation(std::string &operationType, const Signal &firstSig,
                                                const Signal &secondSig) {
    if (operationType == "add") {
        return firstSig + secondSig;
    } else if (operationType == "subtract") {
        return firstSig - secondSig;
    } else if (operationType == "multiply") {
        return firstSig * secondSig;
    } else if (operationType == "divide") {

        return firstSig / secondSig;
    }

}


void SignalProcesor::removeSignal(int i) {
    signalValues.erase(signalValues.begin() + i);
}

void SignalProcesor::addNewSignal(const Signal &signal) {
    signalValues.push_back(signal);
}






