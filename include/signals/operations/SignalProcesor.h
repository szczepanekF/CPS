#pragma once
#include "signals/baseSignals/SignalStrategy.h"
#include "signals/complexSignals/DiscreteComplexSignalStatic.h"
#include <memory>
#include <string>
#include <unordered_map>

class SignalProcesor {
public:
    SignalProcesor();

    Signal getCalculatedSignal(std::string &operationType);

    void saveSignalToBinary(const Signal& sig, const std::string& filename);
    void saveComplexSignalToBinary(const DiscreteComplexSignal& sig, const std::string& filename);
    std::unique_ptr<Signal> readSignalFromBinary(const std::string& filename);
    std::unique_ptr<DiscreteComplexSignal> readComplexSignalFromBinary( const std::string &filename);

    std::string readSignalFromBinaryAsString(const std::string& filename);
    void addNewSignal(const Signal &signal);
    void clearSignals();
private:


    static Signal
    calculateSignalOperation(std::string &operationType, const Signal &firstSig, const Signal &secondSig);

    std::vector<Signal> signalValues;
};

