#include <iostream>
#include <utility>
#include "frontend/SignalManagementComponent.h"
#include "imgui.h"

#include <iostream>
#include "unordered_set"
#include "signals/allBaseSignals.h"
#include "frontend/Parameter.h"
#include "frontend/ConversionComponent.h"
#include "frontend/PlotComponent.h"
#include "simulation/SimulatedSignal.h"
#include "signals/baseSignals/OperationResultSignal.h"


SignalManagementComponent::SignalManagementComponent(std::shared_ptr<Mediator> med)
        : Component(med), filename(), signalProcesor(), drawedSignal(nullptr),
            signalForOperation1(), signalForOperation2(), isOperationChecked(false) {

    addToMediator();
    initChecks();
    params = {Parameter("Amplitude"),
              Parameter("Start time"),
              Parameter("Duration"),
              Parameter("Base period"),
              Parameter("Frequency"),
              Parameter("Probability"),
              Parameter("Fill factor"),
              Parameter("Jump time")};
}


void SignalManagementComponent::show() {
    drawSignalChoicePanel();
    drawParameterPanel();
    drawFilePanel();
    drawSignalInfoPanelIfSignalChosen();
}

void SignalManagementComponent::showSignalParameters() {
    for (Parameter &parameter: params) {
        if (parameter.isVisible) {
            ImGui::SetNextItemWidth(100);
            ImGui::InputDouble(parameter.name.c_str(), &parameter.value, 0.1, 1, "%.2f");
        }
    }
}

void SignalManagementComponent::showFileOperations() {
    ImGui::InputText("Filename", filename, sizeof(filename));
    ImGui::Spacing();

    createButton("Save to file", 0);
    ImGui::SameLine();
    createButton("Load from file", 1);
    createButton("Load signal in text format", 3);
    ImGui::Spacing();

    if (!filenames.empty()) {
        ImGui::Separator();
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f)); // Red color
        ImGui::Text("Loaded files:");

        ImGui::PopStyleColor();

        for (const std::string &loadedFilename: filenames) {
            ImGui::Text(loadedFilename.c_str());
        }
        ImGui::Separator();
        ImGui::Spacing();
        createButton("File operations", 4);
        ImGui::SameLine();
    }

    createButton("Unload files and clear signal", 5);
    ImGui::SetNextItemWidth(500);
    if (ImGui::Checkbox("Signals Operation", &isOperationChecked)) {

        signalForOperation1 = nullptr;
        signalForOperation2 = nullptr;
        cleanUp();
        clearSignals();

    }
}

void SignalManagementComponent::showSignalChoice() {
    createCheckbox(SIN, "Sinusoidal signal", SinusoidalSignalCheck);
    createCheckbox(GAUSSIAN_NOISE, "Gausian noise", GaussianNoiseCheck);
    createCheckbox(IMPULSE_NOISE, "Impulse noise", ImpulseNoiseCheck);
    createCheckbox(RECT, "Rectangular signal", RectangularSignalCheck);
    createCheckbox(RECT_SYMM, "Rectangular simetric signal", RectangularSymmetricSignalCheck);
    createCheckbox(SIN_ONE, "Sinusoidal one half rectified signal", SinusoidalOneHalfRectifiedSignalCheck);
    createCheckbox(SIN_TWO, "Sinusoidal two half rectified signal", SinusoidalTwoHalfRectifiedSignalCheck);
    createCheckbox(TRIANG, "Triangular signal", TriangularSignalCheck);
    createCheckbox(UNITFORM_NOISE, "Uniform Noise", UniformNoiseCheck);
    createCheckbox(UNIT_IMP, "Unit impulse signal", UnitImpulseSignalCheck);
    createCheckbox(UNIT_JMP, "Unit jump signal", UnitJumpSignalCheck);
}


void SignalManagementComponent::createCheckbox(SIGNAL_TYPE type, const char *label, bool &check) {
    ImGui::SetNextItemWidth(500);
    if (ImGui::Checkbox(label, &check)) {
        if (check) {
            signalType = type;
            updateCheckBoxesAndParams();

        } else {
            cleanUp();
        }
    }
}

void SignalManagementComponent::createButton(const char *label, int option) {
    ImGui::SetNextItemWidth(500);
    if (ImGui::Button(label)) {
        if (option == 0) {
            if (drawedSignal != nullptr) {
                signalProcesor.saveSignalToBinary(*drawedSignal, std::string(filename) + ".bin");
                ImGui::OpenPopup("fileSuccess");
            } else {
                ImGui::OpenPopup("fileError");
            }
        } else if (option == 3) {
            signalData = signalProcesor.readSignalFromBinaryAsString(std::string(filename) + ".bin");
            ImGui::OpenPopup("sigText");
        } else if (option == 4) {
            ImGui::OpenPopup("operationsPopup");
        } else if (option == 5) {
            cleanUp();
            signalForOperation2 = nullptr;
            signalForOperation1 = nullptr;
            filenames.clear();
            signalProcesor.clearSignals();
            clearSignals();
        } else {
            cleanUp();
            if (option == 1 && !std::string(filename).empty()) {
                if (filenames.empty()) {
                    clearSignals();
                }
                clearSignals();
                drawedSignal = signalProcesor.readSignalFromBinary(std::string(filename) + ".bin");
                signalProcesor.addNewSignal(*drawedSignal);
                addSignal(nullptr, *drawedSignal);
                filenames.push_back(std::string(filename) + ".bin");
                ImGui::OpenPopup("fileSuccess");
            } else {
                setDrawedSignalBySignalType();
            }
        }
    }
}

void SignalManagementComponent::cleanUp() {

    drawedSignal.reset();
}

void SignalManagementComponent::initChecks() {
    SinusoidalSignalCheck = false;
    GaussianNoiseCheck = false;
    ImpulseNoiseCheck = false;
    RectangularSignalCheck = false;
    RectangularSymmetricSignalCheck = false;
    SinusoidalOneHalfRectifiedSignalCheck = false;
    SinusoidalTwoHalfRectifiedSignalCheck = false;
    TriangularSignalCheck = false;
    UniformNoiseCheck = false;
    UnitImpulseSignalCheck = false;
    UnitJumpSignalCheck = false;

}

void SignalManagementComponent::handleParamsVisibility(std::unordered_set<int> &paramsToShowIndexex) {
    for (size_t i = 0; i < params.size(); i++) {
        if (paramsToShowIndexex.contains(i)) {
            params[i].isVisible = true;
            params[i].value = 0.0;
        } else {
            params[i].isVisible = false;
        }
    }
}

void SignalManagementComponent::handleChecksButtonsVisibility(bool &paramCheck) {
    for (auto check: checks) {
        if (check != &paramCheck) {
            *check = false;
        }
    }
}

void SignalManagementComponent::setDrawedSignalBySignalType() {
    SignalStrategy *strat;
    switch (signalType) {
        case SIN:
            strat = new SinusoidalSignal(params[0].value, params[1].value, params[2].value, params[3].value);

//            strat = new SimulatedSignal(params[1].value, params[2].value, params[3].value);
            break;
        case SIN_ONE:
            strat = new SinusoidalOneHalfRectifiedSignal(params[0].value, params[1].value, params[2].value,
                                                         params[3].value);
            break;
        case SIN_TWO:
            strat = new SinusoidalTwoHalfRectifiedSignal(params[0].value, params[1].value, params[2].value,
                                                         params[3].value);
            break;
        case RECT:
            strat = new RectangularSignal(params[0].value, params[1].value, params[2].value, params[3].value,
                                          params[6].value);
            break;
        case RECT_SYMM:
            strat = new RectangularSymmetricSignal(params[0].value, params[1].value, params[2].value, params[3].value,
                                                   params[6].value);
            break;
        case TRIANG:
            strat = new TriangularSignal(params[0].value, params[1].value, params[2].value, params[3].value,
                                         params[6].value);
            break;
        case UNIT_IMP:
            strat = new UnitImpulseSignal(params[0].value, params[1].value, params[2].value, params[4].value,
                                          params[7].value);
            break;
        case UNIT_JMP:
            strat = new UnitJumpSignal(params[0].value, params[1].value, params[2].value, params[7].value);
            break;
        case UNITFORM_NOISE:
            strat = new UniformNoise(params[0].value, params[1].value, params[2].value);
            break;
        case GAUSSIAN_NOISE:
            strat = new GaussianNoise(params[0].value, params[1].value, params[2].value);
            break;
        case IMPULSE_NOISE:
            strat = new ImpulseNoise(params[0].value, params[1].value, params[2].value, params[4].value,
                                     params[5].value);
            break;
        default:
            return;
    }


    drawedSignal = std::make_unique<Signal>(strat->getSignal());
    std::unique_ptr<SignalStrategy> stratUniquePtr = std::unique_ptr<SignalStrategy> (strat);
    if (!isOperationChecked) {
        clearSignals();

        addSignal(std::move(stratUniquePtr), *drawedSignal);
    } else {
        if (signalForOperation1 == nullptr) {
            signalForOperation1 = std::move(stratUniquePtr);
        } else {
            signalForOperation2 = std::move(stratUniquePtr);
        }
        addSignal(nullptr, *drawedSignal);
    }

}


void SignalManagementComponent::updateCheckBoxesAndParams() {
    std::unordered_set<int> paramsToShow;
    switch (signalType) {
        case SIN:
            paramsToShow = {0, 1, 2, 3};
            handleParamsVisibility(paramsToShow);
            handleChecksButtonsVisibility(SinusoidalSignalCheck);
            break;
        case SIN_ONE:
            paramsToShow = {0, 1, 2, 3};
            handleParamsVisibility(paramsToShow);
            handleChecksButtonsVisibility(SinusoidalOneHalfRectifiedSignalCheck);
            break;
        case SIN_TWO:
            paramsToShow = {0, 1, 2, 3};
            handleParamsVisibility(paramsToShow);
            handleChecksButtonsVisibility(SinusoidalTwoHalfRectifiedSignalCheck);
            break;
        case RECT:
            paramsToShow = {0, 1, 2, 3, 6};
            handleParamsVisibility(paramsToShow);
            handleChecksButtonsVisibility(RectangularSignalCheck);
            break;
        case RECT_SYMM:
            paramsToShow = {0, 1, 2, 3, 6};
            handleParamsVisibility(paramsToShow);
            handleChecksButtonsVisibility(RectangularSymmetricSignalCheck);
            break;
        case TRIANG:
            paramsToShow = {0, 1, 2, 3, 6};
            handleParamsVisibility(paramsToShow);
            handleChecksButtonsVisibility(TriangularSignalCheck);
            break;
        case UNIT_IMP:
            paramsToShow = {0, 1, 2, 4, 7};
            handleParamsVisibility(paramsToShow);
            handleChecksButtonsVisibility(UnitImpulseSignalCheck);
            break;
        case UNIT_JMP:
            paramsToShow = {0, 1, 2, 7};
            handleParamsVisibility(paramsToShow);
            handleChecksButtonsVisibility(UnitJumpSignalCheck);
            break;
        case UNITFORM_NOISE:
            paramsToShow = {0, 1, 2};
            handleParamsVisibility(paramsToShow);
            handleChecksButtonsVisibility(UniformNoiseCheck);
            break;
        case GAUSSIAN_NOISE:
            paramsToShow = {0, 1, 2};
            handleParamsVisibility(paramsToShow);
            handleChecksButtonsVisibility(GaussianNoiseCheck);
            break;
        case IMPULSE_NOISE:
            paramsToShow = {0, 1, 2, 4, 5};
            handleParamsVisibility(paramsToShow);
            handleChecksButtonsVisibility(ImpulseNoiseCheck);
            break;
        default:
            return;

    }

}

void SignalManagementComponent::drawSignalInfo() {
    std::string text1 = "Mean: " + std::to_string(drawedSignal->mean());
    ImGui::Text(text1.c_str());
    std::string text2 = "Absolute mean: " + std::to_string(drawedSignal->absMean());
    ImGui::Text(text2.c_str());
    std::string text3 = "Variance: " + std::to_string(drawedSignal->variance());
    ImGui::Text(text3.c_str());
    std::string text4 = "Rms: " + std::to_string(drawedSignal->rms());
    ImGui::Text(text4.c_str());
    std::string text5 = "Mean power: " + std::to_string(drawedSignal->meanPower());
    ImGui::Text(text5.c_str());
}


void SignalManagementComponent::drawSignalChoicePanel() {
    ImGui::SetNextWindowPos(ImVec2(50, 100), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_Always);
    ImGui::Begin("Signals and noises", nullptr,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
    showSignalChoice();

    ImGui::End();
}

void SignalManagementComponent::drawParameterPanel() {
    ImGui::SetNextWindowPos(ImVec2(500, 100), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_Always);
    ImGui::Begin("Signal parameters", nullptr,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
    showSignalParameters();
    if (signalForOperation2 == nullptr) {
        createButton("Draw the plot", 2);
    } else {
        createStrategyOperationButtons();
    }
    ImGui::End();
}

void
SignalManagementComponent::createPopup(const std::string &label, const std::string &info,
                                       const std::function<void()> &func) {
    if (ImGui::BeginPopup(label.c_str())) {
        ImGui::Text(info.c_str());
        func();
        if (ImGui::Button("Close")) {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}

void SignalManagementComponent::drawFilePanel() {
    ImGui::SetNextWindowPos(ImVec2(950, 100), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_Always);
    ImGui::Begin("Buttons", nullptr,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
    showFileOperations();
    createPopup("fileError", "Draw or read signal in order to save file", []() {});
    createPopup("fileSuccess", "File operation was successful on file: " + std::string(filename), []() {});
    createPopup("operationsPopup", "File operation was successful", [this]() { this->createOperationButtons(); });
    createPopup("sigText", "Signal data in text format", [this]() {
        ImGui::Text(signalData.c_str());
    });
    ImGui::End();
}

void SignalManagementComponent::drawSignalInfoPanelIfSignalChosen() {

    if (drawedSignal != nullptr) {
        ImGui::SetNextWindowPos(ImVec2(1400, 100), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(200, 200), ImGuiCond_Always);
        ImGui::Begin("Calculated signal parameters", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
        drawSignalInfo();
        ImGui::End();
    }
}


void SignalManagementComponent::createOperationButtons() {
    std::array<std::string, 4> arr = {"add", "subtract", "multiply", "divide"};
    for (auto operation: arr) {
        if (ImGui::Button(operation.c_str())) {
            Signal signal = signalProcesor.getCalculatedSignal(operation);
            if (!signal.empty()) {
                cleanUp();
                clearSignals();
                drawedSignal = std::make_unique<Signal>(signal);
                // TODO tutaj zakładamy że nie można DA/AD konwersji na wczytanych plikach robić
                addSignal(nullptr, *drawedSignal);
                ImGui::CloseCurrentPopup();
            }
        }
    }
}

void SignalManagementComponent::createStrategyOperationButtons() {
    std::array<std::string, 4> arr = {"add", "subtract", "multiply", "divide"};
    for (const auto& operation: arr) {
        if (ImGui::Button(operation.c_str())) {
            std::function<double(double, double)> operationFunction = [](double a, double b) {return a + b;};
            if (operation == "add") {
                operationFunction = [](double a, double b) {return a + b;};
            } else if (operation == "subtract") {
                operationFunction = [](double a, double b) {return a - b;};
            } else if (operation == "multiply") {
                operationFunction = [](double a, double b) {return a * b;};
            } else if (operation == "divide") {
                operationFunction = [](double a, double b) {return a / b;};
            }

            SignalStrategy* strat = new OperationResultSignal(std::move(signalForOperation1), std::move(signalForOperation2), operationFunction);
            cleanUp();
            clearSignals();

            drawedSignal = std::make_unique<Signal>(strat->getSignal());
            addSignal(std::unique_ptr<SignalStrategy> (strat), *drawedSignal);
            isOperationChecked = false;
        }
    }
}





