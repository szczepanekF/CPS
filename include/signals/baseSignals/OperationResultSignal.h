

#pragma once
#include <memory>
#include <functional>
#include "ContinousSignal.h"
class OperationResultSignal : public ContinousSignal{
public:
    OperationResultSignal(std::unique_ptr<SignalStrategy> s1, std::unique_ptr<SignalStrategy> s2, std::function<double(double, double)> func);
    double calculateSignalAt(double time) override;

private:
    std::unique_ptr<SignalStrategy> firstSignal;
    std::unique_ptr<SignalStrategy> secondSignal;
    std::function<double(double, double)> operation;
};

