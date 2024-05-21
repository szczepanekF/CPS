
#include "signals/baseSignals/Signal.h"
#include <vector>
#include <memory>


class PlotComponent {
public:
    static PlotComponent* getInstance();
    void show();

    void addSignal(const Signal& signal, const std::string& signalName);
    Signal getSignal(int position = -1);
    void clearSignals();
    void setSecondPlotSignal(const Signal& secondPlotSignal, const std::string& signalName);
    void setThirdPlotSignal(const Signal& thirdPlotSignal, const std::string& signalName);
    void setHeight(float newHeight);
    void resetHeight();
    void stylePlot();

private:
    PlotComponent();

    void showPlotPanel();
    void showSignals();
    void showSignal(const std::pair<Signal, std::string>& signalNamePair);
    void drawDataPlots(float* xData, float *yData, int dataSize, const std::string& signalName);
    void showScatterPlot(float* xData, float *yData, int dataSize, const std::string& signalName);
    void binInput();

    static PlotComponent* instance;
    std::vector<std::pair<Signal, std::string>> signalsNamesPairList;
    std::pair<Signal, std::string> secondPlotSignalNamePair;
    std::pair<Signal, std::string> thirdPlotSignalNamePair;
    int bins;
    float componentHeight;
    float componentPlacementY;
};

