
#include "frontend/Component.h"
#include <memory>

Component::Component(std::shared_ptr<Mediator> mediator) : mediator(mediator) {
}

void Component::addSignal(std::unique_ptr<SignalStrategy> strat, Signal& sig) {
    mediator->addSignal(this, std::move(strat), sig);
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
