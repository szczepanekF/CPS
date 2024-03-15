
#pragma once

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>
#include <unordered_set>
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
    void drawPlot();

    void showSignalParameters();

    void showFileOperations();

    void showSignalChoice();

    void createCheckbox(SIGNAL_TYPE type, const char *label, bool &check);

    void createButton(const char *label, int option);

    void handleParamsVisibility(std::unordered_set<int> paramsToShowIndexex);

    void handleChecksButtonsVisibility(bool& paramCheck);

    void initChecks();


    void setDrawedSignalBySignalType(SIGNAL_TYPE type);

    bool SinusoidalSignalCheck=true, GaussianNoiseCheck, ImpulseNoiseCheck, RectangularSignalCheck, RectangularSymmetricSignalCheck, SinusoidalOneHalfRectifiedSignalCheck, SinusoidalTwoHalfRectifiedSignalCheck, TriangularSignalCheck, UniformNoiseCheck, UnitImpulseSignalCheck, UnitJumpSignalCheck;
    std::vector<bool*>checks = {&SinusoidalSignalCheck, &GaussianNoiseCheck, &ImpulseNoiseCheck, &RectangularSignalCheck, &RectangularSymmetricSignalCheck, &SinusoidalOneHalfRectifiedSignalCheck, &SinusoidalTwoHalfRectifiedSignalCheck, &TriangularSignalCheck, &UniformNoiseCheck, &UnitImpulseSignalCheck, &UnitJumpSignalCheck};


    std::string filename;
    std::vector<Parameter> params;
    std::vector<Option> options;
    float *xData;
    float *yData;
    int dataSize;
    std::unique_ptr<Signal> drawedSignal;
    std::vector<std::unique_ptr<Signal>> operations;

    void cleanUp();
    void initDrawData();
};
