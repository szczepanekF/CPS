#include <algorithm>
#include "frontend/ConversionComponent.h"
#include "imgui.h"
#include "signals/baseSignals/DiscreteSignal.h"
#include "signals/signalConversion/allConversionSignals.h"
#include "frontend/PlotComponent.h"


ConversionComponent::ConversionComponent() : samplingFrequency(0.0), quantizationLimit(0.0), MSE(0.0), SNR(0.0),
                                             PSNR(0.0), MD(0.0) {
    initializeOperations();
}


std::unique_ptr<SignalStrategy> ConversionComponent::mainSignalStrategy = nullptr;

void ConversionComponent::setMainSignalStrategy(std::unique_ptr<SignalStrategy> signalStrategy) {
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
        drawCalculatedMeasuresPanel();
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
    if (isMainSignalStrategyDiscrete() && getSelectedOperationType() == REC_SINC) {
        parameter = "N";
        ImGui::SetNextItemWidth(100);
        ImGui::InputDouble(parameter.c_str(), &samplingFrequency, 0.1, 1, "%.2f");
    } else {
        ImGui::SetNextItemWidth(100);
        ImGui::InputDouble(parameter.c_str(), &samplingFrequency, 0.1, 1, "%.2f");
        if (getSelectedOperationType() != SAMPL) {
            ImGui::SetNextItemWidth(100);
            ImGui::InputInt("Quantization limit", &quantizationLimit);
        }

    }
    if(ImGui::Button("Draw signal")) {
        setConversionSignal();
        PlotComponent::getInstance()->addSignal(mainSignalStrategy->getSignal());

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
    if (isMainSignalStrategyDiscrete()) {
        setChosenDacStrategy();
    } else {
        setChosenAdcStrategy();
    }
}

void ConversionComponent::setChosenAdcStrategy() {
    SignalStrategy *strat;
    OPERATION_TYPE type = getSelectedOperationType();
    auto *mainSignal = dynamic_cast<ContinousSignal *>(mainSignalStrategy.get());
    switch (type) {
        case SAMPL:
            strat = new Sampling(std::unique_ptr<ContinousSignal>(mainSignal), samplingFrequency);
            break;
        case QUANT_CLIPPED: {
            auto *sampling = new Sampling(std::unique_ptr<ContinousSignal>(mainSignal), samplingFrequency);
            strat = new QuantizationClipped(std::unique_ptr<Sampling>(sampling), quantizationLimit);
            break;
        }
        case QUANT_ROUND: {
            auto *sampling = new Sampling(std::unique_ptr<ContinousSignal>(mainSignal), samplingFrequency);
            strat = new QuantizationRounded(std::unique_ptr<Sampling>(sampling), quantizationLimit);
            break;
        }
        default:
            throw std::logic_error("INVALID TYPE");
    }
    mainSignalStrategy = std::unique_ptr<SignalStrategy> (strat);
}

void ConversionComponent::setChosenDacStrategy() {
    SignalStrategy *strat;
    OPERATION_TYPE type = getSelectedOperationType();
    DiscreteSignal *mainSignal = dynamic_cast<DiscreteSignal *>(mainSignalStrategy.get());
    switch (type) {
        case REC_FOH:
            strat = new ReconstructionFirstOrderHold(std::unique_ptr<DiscreteSignal>(mainSignal));
            break;
        case REC_ZOH:
            strat = new ReconstructionZeroOrderHold(std::unique_ptr<DiscreteSignal>(mainSignal));
            break;
        case REC_SINC:
            strat = new ReconstructionSincBased(std::unique_ptr<DiscreteSignal>(mainSignal),
                                                samplingFrequency);
            break;
        default:
            throw std::logic_error("INVALID TYPE");
    }
    mainSignalStrategy = std::unique_ptr<SignalStrategy> (strat);
}

bool ConversionComponent::isOperationSelected() {
    return std::ranges::any_of(operations, [] (auto& operation) {return operation.getIsActive();});
}





