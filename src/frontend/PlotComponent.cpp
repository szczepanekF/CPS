#include "frontend/PlotComponent.h"
#include "imgui.h"
#include "signals/baseSignals/SignalStrategy.h"
#include <implot.h>
#include <iostream>

PlotComponent *PlotComponent::instance = nullptr;

PlotComponent *PlotComponent::getInstance() {
    if (instance == nullptr) {
        instance = new PlotComponent();
    }
    return instance;
}

PlotComponent::PlotComponent()
        : signalsNamesPairList(), secondPlotSignalNamePair(), thirdPlotSignalNamePair(), bins(10), componentHeight(500),
          componentPlacementY(450) {

}

void PlotComponent::show() {
    ImGui::SetNextWindowPos(ImVec2(50, componentPlacementY), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(1600, componentHeight), ImGuiCond_Always);
    ImGui::Begin("Signal processing app", nullptr,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
    showPlotPanel();
    if (signalsNamesPairList.size() == 1 && secondPlotSignalNamePair.first.empty()) {
        binInput();
    }
    ImGui::End();
}


void PlotComponent::binInput() {
    ImGui::SetNextItemWidth(100);
    ImGui::InputInt("Bins", &bins);
    bins = std::max(5, std::min(20, bins));
}

void PlotComponent::addSignal(const Signal &signal, const std::string &signalName) {
    if (!signal.empty()) {
        std::string name = signalName;
        if (name.empty()) {
            name = std::to_string(signalsNamesPairList.size());
        }
        signalsNamesPairList.emplace_back(signal, name);
    }
}

Signal PlotComponent::getSignal(int position) {
    if (position == -1) {
        return signalsNamesPairList.back().first;
    } else {
        return signalsNamesPairList[position].first;
    }
}

void PlotComponent::clearSignals() {
    signalsNamesPairList.clear();
    secondPlotSignalNamePair.first.clear();
    secondPlotSignalNamePair.second.clear();
    thirdPlotSignalNamePair.first.clear();
    thirdPlotSignalNamePair.second.clear();
}

void PlotComponent::showPlotPanel() {
    if (ImPlot::BeginPlot("Main plot window", ImVec2(1550, 250))) {
        showSignals();
        ImPlot::EndPlot();
    }
    if (!secondPlotSignalNamePair.first.empty()) {
        if (ImPlot::BeginPlot("Second plot window", ImVec2(1550, 250))) {
            showSignal(secondPlotSignalNamePair);
            ImPlot::EndPlot();
        }
    }

    if (!thirdPlotSignalNamePair.first.empty()) {
        if (ImPlot::BeginPlot("Third plot window", ImVec2(1550, 250))) {
            showSignal(thirdPlotSignalNamePair);
            ImPlot::EndPlot();
        }
    }
}


void PlotComponent::showSignals() {
    for (const auto &signalNamePair: signalsNamesPairList) {
        showSignal(signalNamePair);
    }
}

void PlotComponent::showSignal(const std::pair<Signal, std::string> &signalNamePair) {
    const Signal &signal = signalNamePair.first;
    const auto &sigVals = signal.getSignalValues();
    const auto &timeVals = signal.getTimeValues();
    std::vector<float> xs(timeVals.begin(), timeVals.end());
    std::vector<float> ys(sigVals.begin(), sigVals.end());
    drawDataPlots(xs.data(), ys.data(), signal.size(), signalNamePair.second);
}

void PlotComponent::drawDataPlots(float *xData, float *yData, int dataSize, const std::string &signalName) {
    showScatterPlot(xData, yData, dataSize, signalName);
    ImPlot::PlotLine(("Line Plot " + signalName).c_str(), xData, yData, dataSize);
    if (signalsNamesPairList.size() == 1 && secondPlotSignalNamePair.first.empty()) {
        ImPlot::PlotHistogram(("Histogram " + signalName).c_str(), yData, dataSize, bins);
    }

}

void PlotComponent::showScatterPlot(float *xData, float *yData, int dataSize, const std::string &signalName) {
    ImPlot::PushStyleVar(ImPlotStyleVar_MarkerSize, 5.0f);
    ImPlot::PlotScatter(("Scatter Plot " + signalName).c_str(), xData, yData, dataSize);
    ImPlot::PopStyleVar();
}

void PlotComponent::setSecondPlotSignal(const Signal &secondPlotSignal, const std::string &signalName) {
    secondPlotSignalNamePair = {secondPlotSignal, signalName};
}

void PlotComponent::setThirdPlotSignal(const Signal &thirdPlotSignal, const std::string &signalName) {
    thirdPlotSignalNamePair = {thirdPlotSignal, signalName};
}


void PlotComponent::resetHeight() {
    componentHeight = 550;
    componentPlacementY = 450;
}

void PlotComponent::setHeight(float newHeight) {
    componentHeight = newHeight;
    componentPlacementY = 150;
}

void PlotComponent::stylePlot() {

    ImPlot::GetStyle().Colors[ImPlotCol_Line] = ImVec4(1.0f, 0.5f, 0.0f, 1.0f);
    ImPlot::GetStyle().Colors[ImPlotCol_MarkerOutline] = ImVec4(0.0f, 0.5f, 1.0f, 1.0f);
    ImPlot::GetStyle().Colors[ImPlotCol_MarkerFill] = ImVec4(0.0f, 0.5f, 1.0f, 1.0f);


    ImPlot::GetStyle().Colors[ImPlotCol_PlotBg] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    ImPlot::GetStyle().Colors[ImPlotCol_PlotBorder] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
    ImPlot::GetStyle().Colors[ImPlotCol_Line] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
    ImPlot::GetStyle().Colors[ImPlotCol_PlotBorder] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);


    ImPlot::GetStyle().Colors[ImPlotCol_AxisGrid] = ImVec4(0.7f, 0.7f, 0.7f, 1.0f);

}

