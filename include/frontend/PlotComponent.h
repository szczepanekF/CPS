
#include "signals/baseSignals/Signal.h"
#include <vector>
#include <memory>

class PlotComponent {
public:
    static PlotComponent* getInstance();
    void drawPlotPanel();
    void addSignal(const Signal& signal);

private:
    PlotComponent();
    void drawPlot(float* xData, float *yData, int dataSize, int bins, std::string name);
    void binInput(int bins);
    static PlotComponent* instance;
    std::vector<Signal> signals;



};

