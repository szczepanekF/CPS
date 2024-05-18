
#pragma once

#include <memory>

class Component;

class SignalStrategy;

class Signal;

class Mediator {
public:
    Mediator() = default;

    virtual ~Mediator() = default;

    virtual void addSignal(Component *, std::unique_ptr<SignalStrategy>, const Signal &, const std::string &) = 0;

    virtual void addSignalToConFilterConv(Component *, std::unique_ptr<SignalStrategy>) = 0;

    virtual void setSecondPlotSignal(const Signal &, const std::string &) = 0;
    virtual void setThirdPlotSignal(const Signal &, const std::string &) = 0;

    virtual Signal getSignal() = 0;

    virtual void clearSignals(Component *) = 0;

    virtual void addComponent(Component *) = 0;
};
