
#pragma once

#include <string>
#include <memory>
#include <vector>

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

    void createCheckbox(SignalStrategy *strategy, const char *label, bool &check);

    void createButton(const char *label, int option);

    void initChecks();
    std::vector<bool> ampVisibility, time0Visibility, probVisibility, durationVisibility, basePeriodVisibility, freqVisibility, fillFactorVisibility, jumpTimeVisibility;

    bool SinusoidalSignalCheck, GaussianNoiseCheck, ImpulseNoiseCheck, RectangularSignalCheck, RectangularSymmetricSignalCheck, SinusoidalOneHalfRectifiedSignalCheck, SinusoidalTwoHalfRectifiedSignalCheck, TriangularSignalCheck, UniformNoiseCheck, UnitImpulseSignalCheck, UnitJumpSignalCheck;

    std::string filename;
    std::vector<Parameter> params;
    std::vector<Option> options;
    float *xData;
    float *yData;
    SignalStrategy *signalStrategy;
    std::vector<std::unique_ptr<SignalStrategy>> strategies;

    void cleanUp();
};
