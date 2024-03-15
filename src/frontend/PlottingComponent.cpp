#include "frontend/PlottingComponent.h"
#include "imgui.h"
#include <implot.h>
#include <iostream>
#include "unordered_set"
#include "signals/allSignals.h"
#include "frontend/Parameter.h"
#include "frontend/Option.h"


void PlottingComponent::drawPlot() {

    if (ImPlot::BeginPlot("Plot")) {
        ImPlot::PlotLine("My Line Plot", xData, yData, dataSize);
        ImPlot::PlotHistogram("Histogram", yData, dataSize, 10);
        ImPlot::EndPlot();
    }
}

void PlottingComponent::show() {


    drawSignalChoicePanel();

    drawParameterPanel();

    drawFilePanel();

    drawPlotPanel();
    drawSignalInfoPanelIfSignalChosen();
}

void PlottingComponent::showSignalParameters() {
    std::string format = "%.2f";
    for (Parameter &parameter: params) {

        if (parameter.isVisible) {
            ImGui::InputDouble(parameter.name.c_str(), &parameter.value, 0.1, 1, format.c_str());
        }

    }
}

void PlottingComponent::showFileOperations() {
    createButton("Save to file", 0);
    createButton("Load from file", 1);
    createButton("Draw the plot", 2);
}

void PlottingComponent::showSignalChoice() {
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


void PlottingComponent::createCheckbox(SIGNAL_TYPE type, const char *label, bool &check) {
    ImGui::SetNextItemWidth(500);
    if (ImGui::Checkbox(label, &check)) {
        cleanUp();
        if (check) {
            setDrawedSignalBySignalType(type);
//            xData = new float[drawedSignal->size()];
//            yData = new float[drawedSignal->size()];
//            drawedSignal->convertToFloat(yData, xData);
//            dataSize = drawedSignal->size();
        } else {
            initDrawData();
        }
    }
}

void PlottingComponent::createButton(const char *label, int option) {
    ImGui::SetNextItemWidth(500);
    if (ImGui::Button(label)) {

        SignalProcesor signalProcesor;
        if (option == 0) {
            signalProcesor.saveSignalToBinary(*currentStrategy, *drawedSignal, "file.bin");
//        } else if (option == 1) {
//            signalStrategy = signalProcesor.readSignalFromBinary("file.bin");

        } else {
            cleanUp();
            xData = new float[drawedSignal->size()];
            yData = new float[drawedSignal->size()];
            drawedSignal->convertToFloat(yData, xData);
            dataSize = drawedSignal->size();
        }
    }
}

PlottingComponent::~PlottingComponent() {
    cleanUp();
}

PlottingComponent::PlottingComponent() : filename(),
                                         drawedSignal(nullptr) {
    initDrawData();
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

void PlottingComponent::cleanUp() {
    delete[] xData;
    delete[] yData;
    dataSize = 0;
}


void PlottingComponent::initChecks() {
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

void PlottingComponent::handleParamsVisibility(std::unordered_set<int>& paramsToShowIndexex) {
    for (size_t i = 0; i < params.size(); i++) {
        if (paramsToShowIndexex.contains(i)) {
            params[i].isVisible = true;
        } else {

            params[i].isVisible = false;
        }
    }
}

void PlottingComponent::handleChecksButtonsVisibility(bool &paramCheck) {
    for (auto check: checks) {
        std::cout << *check << std::endl;
        if (check != &paramCheck) {
            *check = false;
        }
    }
}

void PlottingComponent::setDrawedSignalBySignalType(SIGNAL_TYPE type) {
    SignalStrategy *strat;
    switch (type) {
        case SIN:
            strat = new SinusoidalSignal(params[0].value, params[1].value, params[2].value, params[3].value);
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
    currentStrategy = std::unique_ptr<SignalStrategy>(strat);
}


void PlottingComponent::updateCheckBoxesAndParams(SIGNAL_TYPE type) {
    std::unordered_set<int> paramsToShow;
    switch (type) {
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

void PlottingComponent::initDrawData() {
    drawedSignal.reset();
    dataSize = 10;
    xData = new float[10]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    yData = new float[10]{1, 2, 4, 4, 4, 6, 2, 8, 2, 2};
}

void PlottingComponent::drawSignalInfo() {

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

void PlottingComponent::drawPlotPanel() {

    ImGui::SetNextWindowPos(ImVec2(20, 340), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(1240, 360), ImGuiCond_Always);
    ImGui::Begin("Plot", NULL,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
    drawPlot();
    ImGui::End();

}

void PlottingComponent::drawSignalChoicePanel() {
    ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_Always);
    ImGui::Begin("Signals and noises", nullptr,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
    showSignalChoice();

    ImGui::End();
}

void PlottingComponent::drawParameterPanel() {
    ImGui::SetNextWindowPos(ImVec2(440, 20), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_Always);
    ImGui::Begin("Parameters", nullptr,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
    showSignalParameters();
    ImGui::End();
}

void PlottingComponent::drawFilePanel() {
    ImGui::SetNextWindowPos(ImVec2(860, 20), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_Always);
    ImGui::Begin("Buttons", nullptr,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
    showFileOperations();
    ImGui::End();
}

void PlottingComponent::drawSignalInfoPanelIfSignalChosen() {

    if (drawedSignal != nullptr) {
        ImGui::SetNextWindowPos(ImVec2(1300, 340), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(ImVec2(200, 200), ImGuiCond_Always);
        ImGui::Begin("Signal values", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
        drawSignalInfo();
        ImGui::End();
    }
}
