#include "frontend/PlotComponent.h"
#include "imgui.h"
#include <implot.h>
#include <iostream>

PlotComponent *PlotComponent::getInstance() {
    if(instance == nullptr) {
        instance = new PlotComponent();
    }
    return instance;
}

PlotComponent *PlotComponent::instance = nullptr;

void PlotComponent::drawPlotPanel() {

    ImGui::SetNextWindowPos(ImVec2(50, 450), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(1600, 500), ImGuiCond_Always);
    ImGui::Begin("Plot", nullptr,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
    if (ImPlot::BeginPlot("Plot")) {
        if(!toDrawSignals.empty()) {
            for(auto toDrawSignal : toDrawSignals) {
                drawPlot(toDrawSignal.getXData(), toDrawSignal.getYData(), toDrawSignal.getDataSize(), toDrawSignal.getBins(), toDrawSignal.getName());
            }
        }
        binInput(toDrawSignals.front().getBins());
        ImPlot::EndPlot();
    }
//    drawPlot(xData, yData, dataSize, bins);
//    binInput(bins);
    ImGui::End();
}

void PlotComponent::addToDrawSignal(ToDrawSignal &toDrawSignal) {
    toDrawSignals.push_back(toDrawSignal);
}

void PlotComponent::drawPlot(float* xData, float *yData, int dataSize, int bins, std::string name) {
//    if (ImPlot::BeginPlot("Plot")) {
//        ImPlot::PlotScatter("Scatter Plot", xData, yData, dataSize);
        ImPlot::PlotLine(name.c_str(), xData, yData, dataSize);
//        ImPlot::PlotHistogram("Histogram", yData, dataSize, bins);
//        ImPlot::EndPlot();
//    }
}


void PlotComponent::binInput(int bins) {
    ImGui::SetNextItemWidth(100);
    ImGui::InputInt("Bins",&bins);

    if (bins < 5) bins = 5;

    if (bins > 20) bins = 20;
}

PlotComponent::PlotComponent() = default;


