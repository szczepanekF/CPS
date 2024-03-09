#include <memory>
#include <iostream>
#include "signals/SignalStrategy.h"

class Calculator {
public:
    std::pair<std::vector<double>, std::vector<double>> getCalculatedSignal(std::string operationType);

private:
    double calculateSignalsValues(std::string operationType, std::vector<double> calculatedValues);
    double calculateSignalValue(std::string operationType, double firstValue, double secondValue);
    std::vector<SignalStrategy *> signals;
};

