
#pragma once

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include "signals/SignalTypes.h"
#include "operations/SignalProcesor.h"
#include "Component.h"
#include "Parameter.h"

class Signal;


class SignalStrategy;

class SignalManagementComponent : public Component {
public:
    explicit SignalManagementComponent(std::shared_ptr<Mediator> mediator);

    void show() override;
private:

    void drawSignalChoicePanel();

    void drawParameterPanel();

    void drawFilePanel();

    void drawSignalInfoPanelIfSignalChosen();

    void showSignalParameters();

    void showFileOperations();

    void showSignalChoice();

    void createCheckbox(SIGNAL_TYPE type, const char *label, bool &check);

    void createButton(const char *label, int option);

    void handleParamsVisibility(std::unordered_set<int> &paramsToShowIndexex);

    void handleChecksButtonsVisibility(bool &paramCheck);

    void initChecks();

    void cleanUp();


    void drawSignalInfo();

    void updateCheckBoxesAndParams();

    void setDrawedSignalBySignalType();

    void createPopup(const std::string &label, const std::string &info, const std::function<void()>& func);
    void createOperationButtons();

//    void updateOtherComponents(SignalStrategy* strat);

    bool SinusoidalSignalCheck, GaussianNoiseCheck, ImpulseNoiseCheck, RectangularSignalCheck, RectangularSymmetricSignalCheck, SinusoidalOneHalfRectifiedSignalCheck, SinusoidalTwoHalfRectifiedSignalCheck, TriangularSignalCheck, UniformNoiseCheck, UnitImpulseSignalCheck, UnitJumpSignalCheck;
    std::vector<bool *> checks = {&SinusoidalSignalCheck, &GaussianNoiseCheck, &ImpulseNoiseCheck,
                                  &RectangularSignalCheck, &RectangularSymmetricSignalCheck,
                                  &SinusoidalOneHalfRectifiedSignalCheck, &SinusoidalTwoHalfRectifiedSignalCheck,
                                  &TriangularSignalCheck, &UniformNoiseCheck, &UnitImpulseSignalCheck,
                                  &UnitJumpSignalCheck};


    char filename[256];
    SignalProcesor signalProcesor;
    std::vector<std::string> filenames;
    std::vector<Parameter> params;
    std::string signalData;

    std::unique_ptr<Signal> drawedSignal;
    std::vector<std::unique_ptr<Signal>> operations;
    SIGNAL_TYPE signalType;


};
