#pragma once

#include <vector>
#include <string>
#include <memory>
#include "signals/baseSignals/SignalStrategy.h"
#include "signals/baseSignals/DiscreteSignal.h"
#include "Component.h"
#include "mediator/Mediator.h"
class Window;
class ConvFilterCorComponent : public Component {
public:

    explicit ConvFilterCorComponent(std::shared_ptr<Mediator> mediator);

    void show() override;
    void addSignalStrategy(std::unique_ptr<SignalStrategy> signalStrategy);
    void clearDiscreteSignals();
private:
    void drawOperationPanel();

    void drawParametersPanel();
    void drawFilterWindowChoicePanel();
    std::unique_ptr<Window> getChosenWindow() const;
    int selectedOperation;
    std::vector<std::unique_ptr<DiscreteSignal>> discreteSignals;
    double M;
    double f0;
    int windowChoice;

};


