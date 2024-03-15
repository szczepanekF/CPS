
#pragma once

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>
#include "signals/SignalTypes.h"


class Signal;
class Parameter;

class Option;

class SignalStrategy;

class PlottingComponent {
public:
    PlottingComponent();

    virtual ~PlottingComponent();

    void show();

private:

    void drawPlotPanel();

    void drawSignalChoicePanel();
    void drawParameterPanel();
    void drawFilePanel();


    void drawSignalInfoPanelIfSignalChosen();
    void drawPlot();

    void showSignalParameters();

    void showFileOperations();

    void showSignalChoice();

    void createCheckbox(SIGNAL_TYPE type, const char *label, bool &check);

    void createButton(const char *label, int option);

    void initChecks();

    void drawSignalInfo();
    void setDrawedSignalBySignalType(SIGNAL_TYPE type);
    std::vector<bool> ampVisibility, time0Visibility, probVisibility, durationVisibility, basePeriodVisibility, freqVisibility, fillFactorVisibility, jumpTimeVisibility;

    bool SinusoidalSignalCheck, GaussianNoiseCheck, ImpulseNoiseCheck, RectangularSignalCheck, RectangularSymmetricSignalCheck, SinusoidalOneHalfRectifiedSignalCheck, SinusoidalTwoHalfRectifiedSignalCheck, TriangularSignalCheck, UniformNoiseCheck, UnitImpulseSignalCheck, UnitJumpSignalCheck;

    std::string filename;
    std::vector<Parameter> params;
    std::vector<Option> options;
    float *xData;
    float *yData;
    int dataSize;
    std::unique_ptr<Signal> drawedSignal;
    std::unique_ptr<SignalStrategy> currentStrategy;
    std::vector<std::unique_ptr<Signal>> operations;

    void cleanUp();
    void initDrawData();
};
