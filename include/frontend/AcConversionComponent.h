#include <vector>
#include <string>
#include <memory>
#include "Operation.h"
#include "signals/baseSignals/SignalStrategy.h"

class AcConversionComponent {

public:
    AcConversionComponent();

    void show();
    static void setMainSignalStrategy(std::unique_ptr<SignalStrategy> signalStrategy);
private:
    void drawOperationChoicePanel();
    void drawInputParametersPanel();
    void drawCalculatedMeasuresPanel() const;
//    void drawPlotPanel();
    void initializeOperations();
    std::vector<Operation*> operations;
    double samplingFrequency;
    double quantizationLimit;
    double MSE;
    double SNR;
    double PSNR;
    double MD;

    static std::unique_ptr<SignalStrategy> mainSignalStrategy;
};


