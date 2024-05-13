#include "frontend/PlotComponent.h"
#include "imgui.h"
#include "signals/baseSignals/SignalStrategy.h"
#include <implot.h>

#include <memory>

PlotComponent *PlotComponent::instance = nullptr;

PlotComponent *PlotComponent::getInstance() {
    if (instance == nullptr) {
        instance = new PlotComponent();
    }
    return instance;
}

PlotComponent::PlotComponent() : signals(), bins(10) {

}

void PlotComponent::show() {

    ImGui::SetNextWindowPos(ImVec2(50, 450), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(1600, 500), ImGuiCond_Always);
    ImGui::Begin("Plot", nullptr,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
    showPlotPanel();
    if (!signals.empty()) {
        binInput();
    }
    ImGui::End();
}


void PlotComponent::binInput() {
    ImGui::SetNextItemWidth(100);
    ImGui::InputInt("Bins", &bins);
    bins = std::max(5, std::min(20, bins));
}

void PlotComponent::addSignal(const Signal &signal) {
    if (!signal.empty()) {
        signals.push_back(signal);
    }
}

Signal PlotComponent::getSignal(int position) {
    if(position == -1) {
        return signals.back();
    } else {
        return signals.at(position);
    }
}

void PlotComponent::clearSignals() {
    signals.clear();
}

void PlotComponent::showPlotPanel() {
    if (ImPlot::BeginPlot("Plot")) {
        showSignals();
        ImPlot::EndPlot();
    }
}

void PlotComponent::showSignals() {
    for (size_t i = 0; i < signals.size(); i++) {
        const auto &sigVals = signals[i].getSignalValues();
        const auto &timeVals = signals[i].getTimeValues();
        std::vector<float> xs(timeVals.begin(), timeVals.end());
        std::vector<float> ys(sigVals.begin(), sigVals.end());
        drawDataPlots(xs.data(), ys.data(), signals[i].size(), i);
    }
}

void PlotComponent::drawDataPlots(float *xData, float *yData, size_t dataSize, size_t signalNumber) {
    ImPlot::PlotScatter(("Scatter Plot " + std::to_string(signalNumber)).c_str(), xData, yData, dataSize);
    ImPlot::PlotLine(("Line Plot " + std::to_string(signalNumber)).c_str(), xData, yData, dataSize);
    ImPlot::PlotHistogram(("Histogram " + std::to_string(signalNumber)).c_str(), yData, dataSize, bins);
}



