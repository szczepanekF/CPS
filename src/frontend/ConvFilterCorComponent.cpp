#include <algorithm>

#include <utility>
#include <iostream>
#include "frontend/ConvFilterCorComponent.h"
#include "imgui.h"
#include "signals/baseSignals/DiscreteSignal.h"
#include "frontend/PlotComponent.h"
#include "signals/filters/BandPassFilter.h"
#include "signals/filters/ConvolutionSignal.h"
#include "signals/filters/CorrelationSignal.h"
#include "signals/filters/HighPassFilter.h"
#include "signals/filters/LowPassFilter.h"

ConvFilterCorComponent::ConvFilterCorComponent(std::shared_ptr<Mediator> mediator)
        : Component(std::move(mediator)) {
    addToMediator();
}


void ConvFilterCorComponent::addSignalStrategy(std::unique_ptr<SignalStrategy> signalStrategy) {
    if (signalStrategies.size() < 2) {
        std::unique_ptr<DiscreteSignal> discreteSignal = std::unique_ptr<DiscreteSignal>(
                dynamic_cast<DiscreteSignal *>(signalStrategy.release()));
        signalStrategies.push_back(std::move(discreteSignal));
    } else {
        std::cout << "error";
    }
}

void ConvFilterCorComponent::clearSignalStrategies() {
    signalStrategies.clear();
}

void ConvFilterCorComponent::show() {
    if (signalStrategies.size() == 2) {
        drawOperationPanel();
    }
}

void ConvFilterCorComponent::drawOperationPanel() {
    ImGui::SetNextWindowPos(ImVec2(100, 100), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_Always);
    ImGui::Begin("Operations", nullptr,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
    if (ImGui::RadioButton("Convolution", &selectedOperation, 0)) {
        std::cout << "option";
    }
    if (ImGui::RadioButton("Band and pass filter", &selectedOperation, 1)) {
        std::cout << "option";
    }
    if (ImGui::RadioButton("High pass filter", &selectedOperation, 2)) {
        std::cout << "option";
    }
    if (ImGui::RadioButton("Low pass filter", &selectedOperation, 3)) {
        std::cout << "option";
    }
    if (ImGui::RadioButton("Correlation", &selectedOperation, 4)) {
        std::cout << "option";
    }
    if (ImGui::Button("Draw signal")) {
        switch (selectedOperation) {
            case 0:
                auto convolutionSignal = new ConvolutionSignal(std::move(signalStrategies.at(0)),
                                                               std::move(signalStrategies.at(1)));
                addSignal(nullptr, reinterpret_cast<Signal &>(convolutionSignal));
//                case 1:
//                    auto bandAndPassFilter = new BandPassFilter(std::move(signalStrategies.at(0)), std::move(signalStrategies.at(1));
        }
    }
    ImGui::End();
}













