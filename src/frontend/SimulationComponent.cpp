
#include <imgui.h>
#include <iostream>
#include <chrono>
#include "frontend/SimulationComponent.h"
#include "frontend/PlotComponent.h"

void SimulationComponent::show() {

    ImGui::SetNextWindowPos(ImVec2(0, 50), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(ImGui::GetContentRegionAvail().x - 250, 100), ImGuiCond_Always);
    ImGui::Begin("SimulationParameters", nullptr,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
    drawParameterOptionVertically();
    addSignalsToPlot();

    showSimulationCalculatedParameters();

    ImGui::End();
}

SimulationComponent::SimulationComponent(std::shared_ptr<Mediator> mediator) : Component(std::move(mediator)),
                                                                               signalVelocity(0), echoVelocity(0),
                                                                               samplingFrequency(0),
                                                                               probingSignalPeriod(0),
                                                                               reportingPeriod(0), bufferLength(0),
                                                                               distance(0), timeStep(0.1),
                                                                               lastExecutionTime(),
                                                                               isSimulationStarted(false),
                                                                               realDist(distance), measuredDist(0),
                                                                               timestamp(0) {

}

void SimulationComponent::drawParameterOptionVertically() {
    float spacing = 40;
    // TODO loop
    ImGui::BeginGroup();
    ImGui::SetNextItemWidth(100);
    ImGui::Text("Velocity probing");
    ImGui::SameLine(0, spacing);
    ImGui::SetNextItemWidth(100);
    ImGui::Text("Velocity echo");
    ImGui::SameLine(0, spacing);
    ImGui::SetNextItemWidth(100);
    ImGui::Text("Probing signal period");
    ImGui::SameLine(0, spacing);
    ImGui::SetNextItemWidth(100);
    ImGui::Text("Sampling Frequency");
    ImGui::SameLine(0, spacing);
    ImGui::SetNextItemWidth(100);
    ImGui::Text("Reporting Period");
    ImGui::SameLine(0, spacing);
    ImGui::SetNextItemWidth(100);
    ImGui::Text("Buffer Length");
    ImGui::SameLine(0, spacing);
    ImGui::Text("Distance");
//    ImGui::SetNextItemWidth(100);
//    ImGui::InputDouble(parameter.name.c_str(), &parameter.value, 0.1, 1, "%.2f");
//    ImGui::SetNextItemWidth(100);
//    ImGui::InputDouble(parameter.name.c_str(), &parameter.value, 0.1, 1, "%.2f");
    ImGui::EndGroup();

    ImGui::BeginGroup();
    ImGui::SetNextItemWidth(100);
    ImGui::InputDouble("##Velocity probing", &signalVelocity, 0, 0, "%.2f", ImGuiInputTextFlags_None);
    ImGui::SameLine(0, spacing + 5);
    ImGui::SetNextItemWidth(100);
    ImGui::InputDouble("##Velocity echo", &echoVelocity, 0, 0, "%.2f", ImGuiInputTextFlags_None);
    ImGui::SameLine(0, spacing + 30);

    ImGui::SetNextItemWidth(100);
    ImGui::InputDouble("##Probing signal period", &probingSignalPeriod, 0, 0, "%.2f", ImGuiInputTextFlags_None);
    ImGui::SameLine(0, spacing + 20);

    ImGui::SetNextItemWidth(100);
    ImGui::InputDouble("##Sampling Frequency", &samplingFrequency, 0, 0, "%.2f", ImGuiInputTextFlags_None);
    ImGui::SameLine(0, spacing + 20);

    ImGui::SetNextItemWidth(100);
    ImGui::InputDouble("##Reporting Period", &reportingPeriod, 0, 0, "%.2f", ImGuiInputTextFlags_None);
    ImGui::SameLine(0, spacing + 5);

    ImGui::SetNextItemWidth(100);
    ImGui::InputInt("##Buffer Length", &bufferLength, 0, 0, ImGuiInputTextFlags_None);
    ImGui::SameLine(0, spacing);
    ImGui::SetNextItemWidth(100);
    ImGui::InputDouble("##Distance", &distance, 0, 0, "%.2f", ImGuiInputTextFlags_None);
    ImGui::SameLine(0, spacing);

    startSimulationButton();
    ImGui::SameLine(0, spacing);
    if (env != nullptr && !isSimulationStarted) {
        nextStepButton();
        ImGui::SameLine(0, spacing);
    }
    resetSimulationButton();
    timeStepSlider();

    ImGui::EndGroup();

}

void SimulationComponent::startSimulationButton() {

    ImGui::SetNextItemWidth(500);
    if (ImGui::Button("Start / stop simulation")) {
        if (env == nullptr && !isSimulationStarted) {
            lastExecutionTime = std::chrono::high_resolution_clock::now();
            std::unique_ptr<DistanceSensor> sensor = std::make_unique<DistanceSensor>(samplingFrequency,
                                                                                      probingSignalPeriod, bufferLength,
                                                                                      reportingPeriod);
            env = std::make_unique<Environment>(signalVelocity, echoVelocity, distance, timeStep, std::move(sensor));
        }
        isSimulationStarted = !isSimulationStarted;
    }

}

void SimulationComponent::resetSimulationButton() {
    ImGui::SetNextItemWidth(200);
    if (ImGui::Button("Reset")) {
        clearSignals();
        env = nullptr;
        isSimulationStarted = false;
        timestamp = 0;
        realDist =  0;
        measuredDist = 0;
    }
}

void SimulationComponent::timeStepSlider() {
    ImGui::SliderFloat("Time step", &timeStep, 0, 0.3);
}


void SimulationComponent::addSignalsToPlot() {
    if (isSimulationStarted && env != nullptr) {
        env->step();
        drawSimulationPlots();
    }
}

void SimulationComponent::showSimulationCalculatedParameters() {

    ImGui::SetNextWindowPos(ImVec2(1650, 50), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(220, 100), ImGuiCond_Always);
    ImGui::Begin("Calculated signal parameters", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
    drawSumulationValues();
    ImGui::End();

}

void SimulationComponent::drawSumulationValues() {
    std::string text1 = "Time: " + std::to_string(timestamp);
    ImGui::Text(text1.c_str());
    std::string text2 = "Real distance: " + std::to_string(realDist);
    ImGui::Text(text2.c_str());
    std::string text3 = "Measured distance: " + std::to_string(measuredDist);
    ImGui::Text(text3.c_str());
}

void SimulationComponent::drawSimulationPlots() {
    timestamp = env->getTimestamp();
    realDist = env->getRealDistance();
    measuredDist = env->getMeasuredDistance();
    clearSignals();
    addSignal(nullptr, env->getProbingSignal(), "Probing signal");
    setSecondPlotSignal(env->getEchoSignal(), "Echo signal");
    setThirdPlotSignal(env->getCorrelationSignal(), "Correlation signal");
    lastExecutionTime = std::chrono::high_resolution_clock::now();
}

void SimulationComponent::nextStepButton() {
    ImGui::SetNextItemWidth(200);
    if (ImGui::Button("Next step")) {
        env->step();
        drawSimulationPlots();
    }
}

