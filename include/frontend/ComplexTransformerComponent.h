
#pragma once

#include "Component.h"
#include "signals/baseSignals/OperationResultSignal.h"
#include "signals/transformers/SignalTransformer.h"

class ComplexTransformerComponent : public Component {

public:
    explicit ComplexTransformerComponent(std::shared_ptr<Mediator> mediator);

    void show() override;

private:
    void showSignalChoice();

    void showTransformerChoice();

    void drawTransformation();

    void drawSignal();
    void clearTransformSignals();
    void tranformSampledSignal(std::unique_ptr<Sampling> signal);
    void plotTransformedSignal();
    void updateComplexSignal();
    bool isChosenComplexTrasform() const;
    void transformToComplex(std::unique_ptr<Sampling> signal);
    void transformToReal(std::unique_ptr<Sampling> signal);
    void drawComplexFileOperations();
    void showFileOperations();
    void definePopups();
    std::unique_ptr<OperationResultSignal> getChosenSignal() const;


    int signalChoice;
    int transformerChoice;
    double SAMPLING_FREQUENCY;
    SignalTransformer transformer;
    std::unique_ptr<DiscreteSignal> realTransform;
    std::unique_ptr<DiscreteComplexSignal> complexTransform;
    bool firstComplexVisualModeOn;
    char filename[256];


};


