#include "Calculator.h"


std::pair<std::vector<double>, std::vector<double>> Calculator::getCalculatedSignal(std::string operationType) {
    std::vector<double> calculatedValues = signals[0]->getSignal().first;
    std::vector<double> finalTimeInterval = signals[0]->getSignal().second;
    calculatedValues = calculateSignalsValues(operationType, calculatedValues);
    return std::make_pair(calculatedValues, finalTimeInterval);
}

std::vector<double> Calculator::calculateSignalsValues(std::string operationType, std::vector<double> calculatedValues) {
    int signalsAmount = static_cast<int>(signals.size());
    for(int i=1; i<signalsAmount; i++) {
        std::vector<double> signalValues = signals[i]->getSignal().first;
        int valuesAmount = static_cast<int>(signalValues.size());
        for(int j=0; j<valuesAmount; j++) {
            double calculatedValue =  calculateSignalValue(operationType,
                                                           calculatedValues[j],
                                                           signalValues[j]);
            calculatedValues[j] = calculatedValue;
        }
    }
    return calculatedValues;
}

double Calculator::calculateSignalValue(std::string operationType, double firstValue, double secondValue) {
    if(operationType == "add") {
        return firstValue + secondValue;
    } else if(operationType == "subtract") {
        return firstValue - secondValue;
    } else if(operationType == "multiply") {
        return  firstValue * secondValue;
    } else if(operationType == "divide") {
        return firstValue / secondValue;
    }
}



