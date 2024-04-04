#include <vector>
#include <string>
#include "Operation.h"

class AcConversionComponent {

public:
    AcConversionComponent();
//    virtual ~AcConversionComponent();
    void show();
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

};


