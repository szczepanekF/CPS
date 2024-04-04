#include "frontend/ToDrawSignal.h"
#include <vector>

class PlotComponent {
public:
    static PlotComponent* getInstance();
    void drawPlotPanel();
    void addToDrawSignal(ToDrawSignal &toDrawSignal);
private:
    PlotComponent();
    void drawPlot(float* xData, float *yData, int dataSize, int bins, std::string name);
    void binInput(int bins);
    static PlotComponent* instance;
    std::vector<ToDrawSignal> toDrawSignals;
};

