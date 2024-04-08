
#pragma once
#include "mediator/Mediator.h"
#include "signals/baseSignals/SignalStrategy.h"
#include <memory>
class Component {
public:
    virtual void show() = 0;
    explicit Component(std::shared_ptr<Mediator> mediator);
    virtual ~Component() = default;

    virtual void addToMediator();
    virtual void clearSignals();
    virtual void addSignal(std::unique_ptr<SignalStrategy> strat, Signal& sig);

private:
    std::shared_ptr<Mediator> mediator;
};
