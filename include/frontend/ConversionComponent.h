#include <vector>
#include <string>
#include <memory>
#include "Operation.h"
#include "signals/baseSignals/SignalStrategy.h"

class ConversionComponent {

public:
    ConversionComponent();

    void show();
    static void setMainSignalStrategy(std::unique_ptr<SignalStrategy> signalStrategy);
private:
    void drawOperationChoicePanel();
    void drawInputParametersPanel();
    void drawCalculatedMeasuresPanel() const;
    void initializeOperations();
    void drawRadioButton(size_t operationInd);
    bool isOperationDiscrete(OPERATION_TYPE type);
    OPERATION_TYPE getSelectedOperationType();
    bool isOperationSelected();
    void setConversionSignal();
    void setChosenDacStrategy();
    void setChosenAdcStrategy();

    void unsetMeasures();
    void setMeasures();

    std::vector<Operation> operations;
    int sampleCount;
    double samplingFrequency;
    int quantizationLimit;
    double MSE;
    double SNR;
    double PSNR;
    double MD;

    static bool isMainSignalStrategyDiscrete();
    static std::unique_ptr<SignalStrategy> mainSignalStrategy;
};


