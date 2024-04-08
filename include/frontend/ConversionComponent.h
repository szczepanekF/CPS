#include <vector>
#include <string>
#include <memory>
#include "Operation.h"
#include "signals/baseSignals/SignalStrategy.h"
#include "Component.h"
#include "mediator/Mediator.h"

class ConversionComponent : public Component{
public:

    explicit ConversionComponent(std::shared_ptr<Mediator> mediator);

    void show() override;
    void setMainSignalStrategy(std::unique_ptr<SignalStrategy> signalStrategy);
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
    std::unique_ptr<SignalStrategy> getChosenDacStrategy();
    std::unique_ptr<SignalStrategy> getChosenAdcStrategy();

    void unsetMeasures();
    void setMeasures();

    bool isMainSignalStrategyDiscrete();
    bool isMainSignalStrategyReconstruction();
    std::vector<Operation> operations;
    double samplingFrequency;
    int quantizationLimit;

    bool measuresSet;
    double MSE;
    double SNR;
    double PSNR;
    double MD;

    std::unique_ptr<Signal> baseSignal;


    std::unique_ptr<SignalStrategy> mainSignalStrategy;
};


