
#pragma once
#include <vector>
#include "Mediator.h"

class ConversionComponent;
class PlotComponent;
class SignalManagementComponent;
class Signal;
class SignalMediator : public Mediator{
public:
    explicit SignalMediator();

    void addSignal(Component* comp, std::unique_ptr<SignalStrategy>  strat, Signal& sig) override;
    void clearSignals(Component* comp) override;
    void addComponent(Component* comp);
private:
    std::shared_ptr<ConversionComponent> convComponent;
    std::shared_ptr<PlotComponent> plotComponent;
    std::shared_ptr<SignalManagementComponent> managementComponent;
    std::unique_ptr<SignalStrategy> mainStrategy;
    std::unique_ptr<Signal> signals;
};
