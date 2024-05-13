
#include <algorithm>
#include "mediator/SignalMediator.h"
#include "signals/baseSignals/SignalStrategy.h"
#include "frontend/Component.h"
#include "frontend/PlotComponent.h"

#include "frontend/SignalManagementComponent.h"
#include "frontend/ConversionComponent.h"
#include "frontend/ConvFilterCorComponent.h"

void SignalMediator::addSignal(Component *comp, std::unique_ptr<SignalStrategy> strat, Signal &sig) {
    plotComponent->addSignal(sig);
    convComponent->setMainSignalStrategy(std::move(strat));
}

void SignalMediator::addSignalToConFilterConv(Component *, std::unique_ptr<SignalStrategy> strat) {
    convFilterCorComponent->addSignalStrategy(std::move(strat));
}

Signal SignalMediator::getSignal() {
    return plotComponent->getSignal();
}

void SignalMediator::clearSignals(Component *) {
    plotComponent->clearSignals();
    convComponent->setMainSignalStrategy(nullptr);
//    convFilterCorComponent->clearSignalStrategies();
}

void SignalMediator::addComponent(Component *comp) {
    if (auto convComp = dynamic_cast<ConversionComponent *> (comp)) {
        convComponent = std::shared_ptr<ConversionComponent>(convComp);
        return;
    } else if (auto managementComp = dynamic_cast<SignalManagementComponent *> (comp)) {
        managementComponent = std::shared_ptr<SignalManagementComponent>(managementComp);
        return;
    } else if (auto convFilterCorComp = dynamic_cast<ConvFilterCorComponent *> (comp)) {
        convFilterCorComponent = std::shared_ptr<ConvFilterCorComponent>(convFilterCorComp);
        return;
    } else {
        throw std::logic_error("WRONG COMPONENT TYPE");
    }

}

SignalMediator::SignalMediator() : convComponent(nullptr), plotComponent(PlotComponent::getInstance()),
                                   managementComponent(nullptr), mainStrategy(nullptr), signals(),
                                   convFilterCorComponent(nullptr) {

}




