
#include "frontend/Component.h"
#include <memory>
#include <utility>

Component::Component(std::shared_ptr<Mediator> mediator) : mediator(std::move(mediator)) {
}

void Component::addSignal(std::unique_ptr<SignalStrategy> strat, const Signal &sig, const std::string &signalName) {
    mediator->addSignal(this, std::move(strat), sig, signalName);
}

void Component::addSignalToConvFilterCor(std::unique_ptr<SignalStrategy> strat) {
    mediator->addSignalToConFilterConv(this, std::move(strat));
}

void Component::clearSignals() {
    mediator->clearSignals(this);
}

void Component::addToMediator() {
    mediator->addComponent(this);
}

void Component::setSecondPlotSignal(const Signal &sig, const std::string &signalName) {
    mediator->setSecondPlotSignal(sig, signalName);
}

void Component::setThirdPlotSignal(const Signal &sig, const std::string &signalName) {
    mediator->setThirdPlotSignal(sig, signalName);
}

