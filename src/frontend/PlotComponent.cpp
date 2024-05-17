#include "frontend/PlotComponent.h"
#include "imgui.h"
#include "signals/baseSignals/SignalStrategy.h"
#include <implot.h>
#include <iostream>
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
    if (signals.size() == 1) {
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
    secondPlotSignal.clear();
}

void PlotComponent::showPlotPanel() {
    if (ImPlot::BeginPlot("Plot")) {
        showSignals();
        ImPlot::EndPlot();
    }
    if(!secondPlotSignal.empty()) {
        if (ImPlot::BeginPlot("Result signal")) {
            showSignal(secondPlotSignal);
            ImPlot::EndPlot();
        }
    }
}


void PlotComponent::showSignals() {
    for (size_t i = 0; i < signals.size(); i++) {
        showSignal(signals[i], i);
    }
}

void PlotComponent::showSignal(const Signal& signal, int signalNumber) {
    const auto &sigVals = signal.getSignalValues();
    const auto &timeVals = signal.getTimeValues();
    std::vector<float> xs(timeVals.begin(), timeVals.end());
    std::vector<float> ys(sigVals.begin(), sigVals.end());
    std::cout <<"\n" << signal.size() << " " << xs.size() << " " << ys.size() << "\n";
    std::cout <<"\n" << xs.front() << " " << xs.back() <<  "\n";
    drawDataPlots(xs.data(), ys.data(), signal.size(), signalNumber);
}

void PlotComponent::drawDataPlots(float *xData, float *yData, size_t dataSize, size_t signalNumber) {
    showScatterPlot(xData, yData, dataSize, signalNumber);
    ImPlot::PlotLine(("Line Plot " + std::to_string(signalNumber)).c_str(), xData, yData, dataSize);
    if(signals.size() == 1) {
        ImPlot::PlotHistogram(("Histogram " + std::to_string(signalNumber)).c_str(), yData, dataSize, bins);
    }
}

void PlotComponent::showScatterPlot(float *xData, float *yData, size_t dataSize, size_t signalNumber) {
    ImPlot::PlotScatter(("Scatter Plot " + std::to_string(signalNumber)).c_str(), xData, yData, dataSize);
}

void PlotComponent::setSecondPlotSignal(const Signal &secondPlotSignal) {
    this->secondPlotSignal = secondPlotSignal;
}



