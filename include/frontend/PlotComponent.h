
#include "signals/baseSignals/Signal.h"
#include <vector>
#include <memory>

enum PLOT_COUNT {
    ONE,
    TWO,
    THREE
};

class PlotComponent {
public:
    static PlotComponent* getInstance();
    void show();

    void addSignal(const Signal& signal);
    Signal getSignal(int position = -1);
    void clearSignals();
    void setSecondPlotSignal(const Signal &secondPlotSignal);

private:
    PlotComponent();

    void showPlotPanel();
    void showMultiplyPlotsPanel();
    void showSignals();
    void showSignal(const Signal& signal, int signalNumber=0);
    void drawDataPlots(float* xData, float *yData, size_t dataSize, size_t signalNumber);
    void showScatterPlot(float* xData, float *yData, size_t dataSize, size_t signalNumber);

    void binInput();

    static PlotComponent* instance;
    std::vector<Signal> signals;
    Signal secondPlotSignal;
    int bins;
};

