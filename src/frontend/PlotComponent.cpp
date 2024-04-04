#include "frontend/PlotComponent.h"
#include "imgui.h"
#include "signals/baseSignals/SignalStrategy.h"
#include <implot.h>
#include <iostream>
#include <memory>

PlotComponent *PlotComponent::getInstance() {
    if(instance == nullptr) {
        instance = new PlotComponent();
    }
    return instance;
}

PlotComponent *PlotComponent::instance = nullptr;

void PlotComponent::drawPlotPanel() {
    int bins = 10;
    ImGui::SetNextWindowPos(ImVec2(50, 450), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(1600, 500), ImGuiCond_Always);
    ImGui::Begin("Plot", nullptr,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
    if (ImPlot::BeginPlot("Plot")) {
        if(!signals.empty()) {
            int iterationNumber = 0;
            for(auto toDrawSignal : signals) {
                const auto& sigVals = toDrawSignal.getSignalValues();
                const auto& timeVals = toDrawSignal.getTimeValues();

                std::vector<float> xs(timeVals.begin(), timeVals.end());
                std::vector<float> ys(sigVals.begin(), sigVals.end());
                drawPlots(xs.data(),ys.data(), toDrawSignal.size(), 10, iterationNumber);
            }
        binInput(bins);
        }
        ImPlot::EndPlot();
    }
//    drawPlot(xData, yData, dataSize, bins);
//    binInput(bins);
    ImGui::End();
}


void PlotComponent::drawPlots(float* xData, float *yData, int dataSize, int bins, int signalNumber) {
//    if (ImPlot::BeginPlot("Plot")) {
        ImPlot::PlotScatter(("Scatter Plot " + std::to_string(signalNumber)).c_str(), xData, yData, dataSize);
        ImPlot::PlotLine(("Line Plot " + std::to_string(signalNumber)).c_str(), xData, yData, dataSize);
        ImPlot::PlotHistogram(("Histogram " + std::to_string(signalNumber)).c_str(), yData, dataSize, bins);
//        ImPlot::EndPlot();s
//    }
}


void PlotComponent::binInput(int bins) {
    ImGui::SetNextItemWidth(100);
    ImGui::InputInt("Bins",&bins);

    if (bins < 5) bins = 5;

    if (bins > 20) bins = 20;
}

void PlotComponent::addSignal(const Signal& signal) {
    signals.push_back(signal);
}


PlotComponent::PlotComponent() : signals() {

};


