
#include "signals/SignalStrategy.h"
#include <memory>
#include <string>
#include <unordered_map>

class SignalProcesor {
public:
    SignalProcesor(std::unique_ptr<SignalStrategy> signalStrategy);

    Signal getCalculatedSignal(std::string &operationType);

private:

    void addNewSignal(const Signal &signal);

    void removeSignal(int i);

    static Signal
    calculateSignalOperation(std::string &operationType, const Signal &firstSig, const Signal &secondSig);

    std::unique_ptr<SignalStrategy> strategy;
    std::vector<Signal> signalValues;
};

