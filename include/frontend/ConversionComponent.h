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
    void drawConvertedSignal();
    static bool isMainSignalStrategyDiscrete();
    std::vector<Operation> operations;
    int sampleCount;
    double samplingFrequency;
    double quantizationLimit;
    double MSE;
    double SNR;
    double PSNR;
    double MD;

    static std::unique_ptr<SignalStrategy> mainSignalStrategy;
};


