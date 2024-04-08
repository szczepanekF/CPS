
#include "signals/baseSignals/Signal.h"
#include <vector>
#include <memory>

class PlotComponent {
public:
    static PlotComponent* getInstance();
    void show();

    void addSignal(const Signal& signal);
    void clearSignals();

private:
    PlotComponent();

    void showPlotPanel();
    void showSignals();
    void drawDataPlots(float* xData, float *yData, size_t dataSize, size_t signalNumber);
    void binInput();


    static PlotComponent* instance;
    std::vector<Signal> signals;
    int bins;



};

