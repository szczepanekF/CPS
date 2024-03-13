#include <memory>
#include <iostream>
#include "signals/SignalStrategy.h"

class Calculator {
public:
    Signal getCalculatedSignal(std::string operationType);
    Calculator(std::vector<SignalStrategy*>signals);
private:
    void calculateSignalsValues(std::string operationType, std::vector<double> &calculatedValues);
    static double calculateSignalValue(std::string operationType, double firstValue, double secondValue);
    std::vector<SignalStrategy *> signals;
};

