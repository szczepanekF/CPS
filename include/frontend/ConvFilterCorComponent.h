#pragma once

#include <vector>
#include <string>
#include <memory>
#include "signals/baseSignals/SignalStrategy.h"
#include "signals/baseSignals/DiscreteSignal.h"
#include "Component.h"
#include "mediator/Mediator.h"

class ConvFilterCorComponent : public Component{
public:

    explicit ConvFilterCorComponent(std::shared_ptr<Mediator> mediator);

    void show() override;
    void addSignalStrategy(std::unique_ptr<SignalStrategy> signalStrategy);
    void clearSignalStrategies();
private:
    void drawOperationPanel();
    int selectedOperation = 0;
    std::vector<std::unique_ptr<DiscreteSignal>> signalStrategies;
};


