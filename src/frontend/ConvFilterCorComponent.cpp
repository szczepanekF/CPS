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
#include "windows/RectangularWindow.h"
#include "windows/BlackmanWindow.h"
#include "windows/HammingWindow.h"
#include "windows/HanningWindow.h"

ConvFilterCorComponent::ConvFilterCorComponent(std::shared_ptr<Mediator> mediator)
        : Component(std::move(mediator)), selectedOperation(-1), windowChoice(-1) {
    addToMediator();
}


void ConvFilterCorComponent::addSignalStrategy(std::unique_ptr<SignalStrategy> signalStrategy) {
    if (discreteSignals.size() < 2) {
        std::unique_ptr<DiscreteSignal> discreteSignal = std::unique_ptr<DiscreteSignal>(
                dynamic_cast<DiscreteSignal *>(signalStrategy.release()));
        discreteSignals.push_back(std::move(discreteSignal));
        std::cout << discreteSignals.size();
    } else {
        std::cout << "error";
    }
}

void ConvFilterCorComponent::clearDiscreteSignals() {
    discreteSignals.clear();
    clearSignals();
}

void ConvFilterCorComponent::show() {
    if (!discreteSignals.empty()) {
        drawOperationPanel();
        if (discreteSignals.size() == 1) {
            drawParametersPanel();
            drawFilterWindowChoicePanel();
        }
    }
}

void ConvFilterCorComponent::drawOperationPanel() {
    ImGui::SetNextWindowPos(ImVec2(100, 100), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_Always);
    ImGui::Begin("Operations", nullptr,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
    if (discreteSignals.size() == 2) {
        ImGui::RadioButton("Convolution", &selectedOperation, 0);
        ImGui::RadioButton("Correlation", &selectedOperation, 1);
    }
    if (discreteSignals.size() == 1) {
        ImGui::RadioButton("Band and pass filter", &selectedOperation, 2);
        ImGui::RadioButton("High pass filter", &selectedOperation, 3);
        ImGui::RadioButton("Low pass filter", &selectedOperation, 4);
    }

    std::unique_ptr<Window> window = getChosenWindow();

    if (ImGui::Button("Draw signal")) {
        addSignal(nullptr, discreteSignals[0]->getSignal());

        std::unique_ptr<SignalStrategy> strat;
        switch (selectedOperation) {
            case 1:
                addSignal(nullptr, discreteSignals[1]->getSignal());
                strat = std::make_unique<CorrelationSignal>(std::move(discreteSignals[0]),
                                                            std::move(discreteSignals[1]));
                break;
            case 2:
                discreteSignals.push_back(std::make_unique<BandPassFilter>(M,f0,frequency, std::move(window)));
                [[fallthrough]];
            case 3:
                discreteSignals.push_back(std::make_unique<HighPassFilter>(M,f0,frequency, std::move(window)));
                [[fallthrough]];
            case 4:
                discreteSignals.push_back(std::make_unique<LowPassFilter>(M,f0,frequency, std::move(window)));
                [[fallthrough]];
            case 0:
                addSignal(nullptr, discreteSignals[1]->getSignal());
                strat = std::make_unique<ConvolutionSignal>(std::move(discreteSignals[0]),
                                                            std::move(discreteSignals[1]));
                break;

            default:
                strat = std::move(discreteSignals[0]);

        }
        setSecondPlotSignal(strat->getSignal());

    }


    if (ImGui::Button("Clear discrete signals")) {
        clearDiscreteSignals();
        std::cout << discreteSignals.size();
    }
    ImGui::End();
}

void ConvFilterCorComponent::drawParametersPanel() {
    ImGui::SetNextWindowPos(ImVec2(1000, 100), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_Always);
    ImGui::Begin("Filter window choice", nullptr,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);

    ImGui::RadioButton("Blackman", &windowChoice, 0);
    ImGui::RadioButton("Hamming", &windowChoice, 1);
    ImGui::RadioButton("Hanning", &windowChoice, 2);
    ImGui::RadioButton("Rectangular", &windowChoice, 3);

    ImGui::End();
}

void ConvFilterCorComponent::drawFilterWindowChoicePanel() {
    ImGui::SetNextWindowPos(ImVec2(550, 100), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_Always);
    ImGui::Begin("Filter parameters", nullptr,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);

    std::string parameter1Name = "M";
    ImGui::SetNextItemWidth(100);
    ImGui::InputDouble(parameter1Name.c_str(), &M, 0.1, 1, "%.2f");

    std::string parameter2Name = "f0";
    ImGui::SetNextItemWidth(100);
    ImGui::InputDouble(parameter2Name.c_str(), &f0, 0.1, 1, "%.2f");

    std::string parameter3Name = "frequency";
    ImGui::SetNextItemWidth(100);
    ImGui::InputDouble(parameter3Name.c_str(), &frequency, 0.1, 1, "%.2f");

    std::string parameter4Name = "K";
    ImGui::SetNextItemWidth(100);
    ImGui::InputDouble(parameter4Name.c_str(), &K, 0.1, 1, "%.2f");
    ImGui::End();
}

std::unique_ptr<Window> ConvFilterCorComponent::getChosenWindow() const {
    switch (windowChoice) {

        case 0: {
            return std::make_unique<BlackmanWindow>(M);
        }
        case 1: {
            return std::make_unique<HammingWindow>(M);
        }
        case 2: {
            return std::make_unique<HanningWindow>(M);
        }
        default: {
            return std::make_unique<RectangularWindow>(M);
        }
    }

}












