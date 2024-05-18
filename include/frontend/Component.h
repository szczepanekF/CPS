
#pragma once
#include "mediator/Mediator.h"
#include "signals/baseSignals/SignalStrategy.h"
#include <memory>
class Component {
public:
    virtual void show() = 0;
    explicit Component(std::shared_ptr<Mediator> mediator);
    virtual ~Component() = default;

    void addToMediator();
    void clearSignals();
    void addSignal(std::unique_ptr<SignalStrategy> strat, const Signal& sig, const std::string& signalName = "");
    void addSignalToConvFilterCor(std::unique_ptr<SignalStrategy> strat);
    void setSecondPlotSignal(const Signal& signal, const std::string& signalName = "");
    void setThirdPlotSignal(const Signal& signal, const std::string& signalName = "");

private:
    std::shared_ptr<Mediator> mediator;
};
