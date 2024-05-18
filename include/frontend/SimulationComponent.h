
#pragma once
#include "Component.h"
#include "simulation/Environment.h"
#include <chrono>
class SimulationComponent : public Component{
public:
    explicit SimulationComponent(std::shared_ptr<Mediator> mediator);
    void show() override;


private:

    void drawParameterOptionVertically();
    void drawSimulationPlots();
    void startSimulationButton();
    void nextStepButton();
    void resetSimulationButton();
    void timeStepSlider();
    void addSignalsToPlot();
    void showSimulationCalculatedParameters();
    void drawSumulationValues();
    double signalVelocity;
    double echoVelocity;

    double samplingFrequency;
    double probingSignalPeriod;
    double reportingPeriod;
    int bufferLength;

    double distance;
    float timeStep;
    std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>  lastExecutionTime;
    bool isSimulationStarted;

    double realDist;
    double measuredDist;
    double timestamp;
    std::unique_ptr<Environment> env;
};
