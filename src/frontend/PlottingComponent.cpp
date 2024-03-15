#include "frontend/PlottingComponent.h"
#include "imgui.h"
#include <implot.h>
#include <iostream>
#include "signals/allSignals.h"
#include "frontend/Parameter.h"
#include "frontend/Option.h"


void PlottingComponent::drawPlot() {
    if (ImPlot::BeginPlot("Plot")) {
        ImPlot::PlotLine("My Line Plot", xData, yData, dataSize);
//        ImPlot::PlotHistogram("Histogram",xData, 2);
        ImPlot::EndPlot();
    }
}

void PlottingComponent::show() {

    ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_Always);
    ImGui::Begin("Signals and noises", NULL,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
    showSignalChoice();

    ImGui::End();

    ImGui::SetNextWindowPos(ImVec2(440, 20), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_Always);
    ImGui::Begin("Parameters", NULL,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
    showSignalParameters();
    ImGui::End();

    ImGui::SetNextWindowPos(ImVec2(860, 20), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_Always);
    ImGui::Begin("Buttons", NULL,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
    showFileOperations();
    ImGui::End();

    ImGui::SetNextWindowPos(ImVec2(20, 340), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(1240, 360), ImGuiCond_Always);
    ImGui::Begin("Plot", NULL,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
    drawPlot();
    ImGui::End();
}

void PlottingComponent::showSignalParameters() {
    char *format = "%.2f";
    for (Parameter &parameter: params) {
        ImGui::InputDouble(parameter.name.c_str(), &parameter.value, 0.1, 1, format);
    }
}

void PlottingComponent::showFileOperations() {
    createButton("Save to file", 0);
    createButton("Load from file", 1);
    createButton("Draw the plot", 2);
}

void PlottingComponent::showSignalChoice() {
    createCheckbox(new SinusoidalSignal(params[0].val(), params[1].val(), params[2].val(), params[3].val()),
                   "Sinusoidal signal", SinusoidalSignalCheck);
    createCheckbox(new GaussianNoise(params[0].val(), params[1].val(), params[2].val()), "Gausian noise",
                   GaussianNoiseCheck);
    createCheckbox(
            new ImpulseNoise(params[0].val(), params[1].val(), params[2].val(), params[4].val(), params[5].val()),
            "Impulse noise", ImpulseNoiseCheck);
    createCheckbox(
            new RectangularSignal(params[0].val(), params[1].val(), params[2].val(), params[3].val(), params[6].val()),
            "Rectangular signal", RectangularSignalCheck);
    createCheckbox(
            new RectangularSymmetricSignal(params[0].val(), params[1].val(), params[2].val(), params[3].val(),
                                           params[6].val()),
            "Rectangular simetric signal", RectangularSymmetricSignalCheck);
    createCheckbox(
            new SinusoidalOneHalfRectifiedSignal(params[0].val(), params[1].val(), params[2].val(), params[3].val()),
            "Sinusoidal one half rectified signal", SinusoidalOneHalfRectifiedSignalCheck);
    createCheckbox(
            new SinusoidalTwoHalfRectifiedSignal(params[0].val(), params[1].val(), params[2].val(), params[3].val()),
            "Sinusoidal two half rectified signal", SinusoidalTwoHalfRectifiedSignalCheck);
    createCheckbox(
            new TriangularSignal(params[0].val(), params[1].val(), params[2].val(), params[3].val(), params[6].val()),
            "Triangular signal", TriangularSignalCheck);
    createCheckbox(new UniformNoise(params[0].val(), params[1].val(), params[2].val()), "Uniform Noise",
                   UniformNoiseCheck);
    createCheckbox(
            new UnitImpulseSignal(params[0].val(), params[1].val(), params[2].val(), params[4].val(), params[7].val()),
            "Unit impulse signal", UnitImpulseSignalCheck);
    createCheckbox(new UnitJumpSignal(params[0].val(), params[1].val(), params[2].val(), params[7].val()),
                   "Unit jump signal",
                   UnitJumpSignalCheck);
}


void PlottingComponent::createCheckbox(SignalStrategy *strategy, const char *label, bool &check) {
    ImGui::SetNextItemWidth(500);
    if (ImGui::Checkbox(label, &check)) {
        cleanUp();
        if (check) {
            Signal data = strategy->getSignal();
            xData = new float[data.size()];
            yData = new float[data.size()];
            data.convertToFloat(xData, yData);
            dataSize = data.size();
        }
    }
    delete strategy;
}

void PlottingComponent::createButton(const char *label, int option) {
    ImGui::SetNextItemWidth(500);
    if (ImGui::Button(label)) {
        std::unique_ptr<SignalStrategy> sharedPtr(signalStrategy);
        SignalProcesor signalProcesor(std::move(sharedPtr));
        if (option == 0) {
            signalProcesor.saveSignalToBinary(signalStrategy->getSignal(), "file.bin");
        } else if (option == 1) {
//            signalStrategy = signalProcesor.readSignalFromBinary("file.bin");
        }
    }
}

PlottingComponent::~PlottingComponent() {
    cleanUp();
}

PlottingComponent::PlottingComponent() : filename(), dataSize(10),
                                         signalStrategy(nullptr) {
    xData = new float[10]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    yData = new float[10]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    initChecks();
    params = {Parameter("Amplitude"),
              Parameter("Start time"),
              Parameter("Probabilidty"),
              Parameter("Duration"),
              Parameter("Base period"),
              Parameter("Frequency"),
              Parameter("Fill factor"),
              Parameter("Jump time")};
}

void PlottingComponent::cleanUp() {
    std::cout << "TEST\n";
    delete[] xData;
    delete[]yData;
    delete signalStrategy;
    dataSize = 10;
    xData = new float[10]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    yData = new float[10]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
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
