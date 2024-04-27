#include <algorithm>
#include <iostream>
#include <utility>
#include "frontend/ConversionComponent.h"
#include "imgui.h"
#include "signals/baseSignals/DiscreteSignal.h"
#include "signals/signalConversion/allConversionSignals.h"
#include "frontend/PlotComponent.h"


ConversionComponent::ConversionComponent(std::shared_ptr<Mediator> mediator)
        : Component(std::move(mediator)), samplingFrequency(0.0), quantizationLimit(0.0),
          measuresSet(false), MSE(0.0), SNR(0.0), PSNR(0.0), MD(0.0) {
    addToMediator();
    initializeOperations();
}


void ConversionComponent::setMainSignalStrategy(std::unique_ptr<SignalStrategy> signalStrategy) {
    unsetMeasures();
    mainSignalStrategy = std::move(signalStrategy);
}


void ConversionComponent::initializeOperations() {
    operations = {
            Operation(SAMPL, "Even sampling"),
            Operation(QUANT_CLIPPED, "Even quantization with cutting"),
            Operation(QUANT_ROUND, "Even quantization with rounding"),
            Operation(REC_ZOH, "Zero-order extrapolation"),
            Operation(REC_FOH, "First-order interpolation"),
            Operation(REC_SINC, "Sin function based reconstruction")
    };
}

void ConversionComponent::show() {
    if (mainSignalStrategy != nullptr) {
        drawOperationChoicePanel();
        if (isOperationSelected()) {
            drawInputParametersPanel();
        }
        if (measuresSet) {
            drawCalculatedMeasuresPanel();
        }
    }
}

void ConversionComponent::drawOperationChoicePanel() {
    ImGui::SetNextWindowPos(ImVec2(50, 100), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_Always);
    ImGui::Begin("Operations", nullptr,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);

    for (size_t i = 0; i < operations.size(); i++) {
        bool isOperDisc = isOperationDiscrete(operations[i].getType());
        if (isMainSignalStrategyDiscrete() != isOperDisc) {
            drawRadioButton(i);
        }
    }
    ImGui::End();
}

void ConversionComponent::drawInputParametersPanel() {

    ImGui::SetNextWindowPos(ImVec2(550, 100), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_Always);
    ImGui::Begin("Conversion parameters", nullptr,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);

    std::string parameter = "Sampling frequency";
    if (getSelectedOperationType() == REC_SINC) {
        parameter = "N";
        ImGui::SetNextItemWidth(100);
        ImGui::InputDouble(parameter.c_str(), &samplingFrequency, 0.1, 1, "%.2f");
    } else if (!isMainSignalStrategyDiscrete()) {
        ImGui::SetNextItemWidth(100);
        ImGui::InputDouble(parameter.c_str(), &samplingFrequency, 0.1, 1, "%.2f");
        if (getSelectedOperationType() != SAMPL) {
            ImGui::SetNextItemWidth(100);
            ImGui::InputInt("Quantization limit", &quantizationLimit);
        }

    }
    if (ImGui::Button("Draw signal")) {
        setConversionSignal();
    }
    ImGui::End();
}

void ConversionComponent::drawCalculatedMeasuresPanel() const {
    ImGui::SetNextWindowPos(ImVec2(1100, 100), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_Always);
    ImGui::Begin("Calculated Measures", nullptr,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
    ImGui::Text(("Mean square error = " + std::to_string(MSE)).c_str());
    ImGui::Text(("Signal - noise ratio = " + std::to_string(SNR)).c_str());
    ImGui::Text(("Peaked signal - noise ratio = " + std::to_string(PSNR)).c_str());
    ImGui::Text(("Max difference = " + std::to_string(MD)).c_str());
    ImGui::End();
}

bool ConversionComponent::isMainSignalStrategyDiscrete() {
    return dynamic_cast<DiscreteSignal *> (mainSignalStrategy.get()) != nullptr;
}

bool ConversionComponent::isMainSignalStrategyReconstruction() {
    return dynamic_cast<Reconstruction *> (mainSignalStrategy.get()) != nullptr;
}


bool ConversionComponent::isOperationDiscrete(OPERATION_TYPE type) {
    switch (type) {
        case SAMPL:
        case QUANT_CLIPPED:
        case QUANT_ROUND:
            return true;
        case REC_FOH:
        case REC_ZOH:
        case REC_SINC:
            return false;
        default:
            throw std::logic_error("INVALID TYPE");

    }

}

void ConversionComponent::drawRadioButton(size_t operationInd) {
    Operation &op = operations[operationInd];
    if (ImGui::RadioButton(op.getName(), op.getIsActive())) {
        op.setIsActive(true);
        for (size_t i = 0; i < operations.size(); i++) {
            if (operationInd != i) operations[i].setIsActive(false);
        }
    }
}

OPERATION_TYPE ConversionComponent::getSelectedOperationType() {
    for (auto &operation: operations) {
        if (operation.getIsActive()) {
            return operation.getType();
        }
    }
    throw std::logic_error("Operation of unknown type");
}

void ConversionComponent::setConversionSignal() {
    std::unique_ptr<SignalStrategy> strat{};
    if (isMainSignalStrategyDiscrete()) {
        strat = getChosenDacStrategy();
    } else {
        strat = getChosenAdcStrategy();
    }

    Signal& sig = strat->getSignal();
    addSignal(std::move(strat), sig);

    if (isMainSignalStrategyReconstruction()) {
        setMeasures();

    }


    std::ranges::for_each(operations, [](auto &oper) { oper.setIsActive(false); });
}


std::unique_ptr<SignalStrategy> ConversionComponent::getChosenAdcStrategy() {
    std::unique_ptr<SignalStrategy> strat;
    OPERATION_TYPE type = getSelectedOperationType();

    baseSignal = std::make_unique<Signal>(mainSignalStrategy->getSignal());

    std::unique_ptr<ContinousSignal> mainSignal = std::unique_ptr<ContinousSignal>(
            dynamic_cast<ContinousSignal *>(mainSignalStrategy.release()));
    std::unique_ptr<Sampling> sampling = std::make_unique<Sampling>(std::move(mainSignal), samplingFrequency);
    switch (type) {
        case SAMPL:
            strat = std::move(sampling);
            break;
        case QUANT_CLIPPED: {
            strat = std::make_unique<QuantizationClipped>(std::move(sampling), quantizationLimit);
            break;
        }
        case QUANT_ROUND: {
            strat = std::make_unique<QuantizationRounded>(std::move(sampling), quantizationLimit);
            break;
        }
        default:
            baseSignal.reset();
            throw std::logic_error("INVALID TYPE");
    }
    return strat;
}


std::unique_ptr<SignalStrategy> ConversionComponent::getChosenDacStrategy() {
    std::unique_ptr<SignalStrategy> strat;
    OPERATION_TYPE type = getSelectedOperationType();
    std::unique_ptr<DiscreteSignal> mainSignal = std::unique_ptr<DiscreteSignal>(
            dynamic_cast<DiscreteSignal *>(mainSignalStrategy.release()));

    switch (type) {
        case REC_FOH:
            strat = std::make_unique<ReconstructionFirstOrderHold>(std::move(mainSignal));
            break;
        case REC_ZOH:
            strat = std::make_unique<ReconstructionZeroOrderHold>(std::move(mainSignal));
            break;
        case REC_SINC:
            strat = std::make_unique<ReconstructionSincBased>(std::move(mainSignal), samplingFrequency);
            break;
        default:
            throw std::logic_error("INVALID TYPE");
    }
    return strat;
}

bool ConversionComponent::isOperationSelected() {
    return std::ranges::any_of(operations, [](auto &operation) { return operation.getIsActive(); });
}

void ConversionComponent::unsetMeasures() {
    measuresSet = false;
    MSE = 0;
    SNR = 0;
    PSNR = 0;
    MD = 0;
}

void ConversionComponent::setMeasures() {
    auto recSig = mainSignalStrategy->getSignal();
    if (baseSignal == nullptr || recSig.empty()) {
        unsetMeasures();
        return;
    }
    measuresSet = true;
    MSE = baseSignal->meanSquaredError(recSig);
    SNR = baseSignal->signalToNoiseRatio(recSig);
    PSNR = baseSignal->peakSignalToNoiseRatio(recSig);
    MD = baseSignal->maxDifference(recSig);

}






