#include "frontend/ConversionComponent.h"
#include "imgui.h"
#include "signals/baseSignals/DiscreteSignal.h"
#include "signals/signalConversion/allConversionSignals.h"


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
            Operation(SAMPL, "Próbkowanie równomierne"),
            Operation(QUANT_CLIPPED, "Kwantyzacja równomierna z obcięciem"),
            Operation(QUANT_ROUND, "Kwantyzacja równomierna z zaokraglaniem"),
            Operation(REC_ZOH, "Ekstrapolacja zerowego rzedu"),
            Operation(REC_FOH, "Interpolacja pierwszego rzedu"),
            Operation(REC_SINC, "Rekonstrukcja w oparciu o funkcje sinc")
    };
}

void ConversionComponent::show() {
    if (mainSignalStrategy != nullptr) {
        drawOperationChoicePanel();
        drawInputParametersPanel();
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
    ImGui::Begin("Parametry", nullptr,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);

    std::string parameter = "Czestotliwosc probkowania";
    if (isMainSignalStrategyDiscrete()) {
        const auto& it = std::ranges::find_if(operations, [] (auto& oper) {
            return oper.getType() == REC_SINC;
        });
        if (it != operations.end() && it->getIsActive()) {
            parameter = "N";
            ImGui::SetNextItemWidth(100);
            ImGui::InputDouble(parameter.c_str(), &samplingFrequency);
        }
    } else {
        ImGui::SetNextItemWidth(100);
        ImGui::InputDouble(parameter.c_str(), &samplingFrequency);
    }

    ImGui::SetNextItemWidth(100);
    ImGui::InputDouble("Próg kwantyzacji", &quantizationLimit);
    ImGui::End();
}

void ConversionComponent::drawCalculatedMeasuresPanel() const {
    ImGui::SetNextWindowPos(ImVec2(1100, 100), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_Always);
    ImGui::Begin("Calculated Measures", nullptr,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
    ImGui::Text(("Blad sredniokwadratowy = " + std::to_string(MSE)).c_str());
    ImGui::Text(("Stosunek sygnaª - szum = " + std::to_string(SNR)).c_str());
    ImGui::Text(("Szczytowy stosunek sygnal - szum = " + std::to_string(PSNR)).c_str());
    ImGui::Text(("Maksymalna róznica = " + std::to_string(MD)).c_str());
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

void ConversionComponent::drawConvertedSignal() {
    SignalStrategy* strat;
    //TODO fix this - sampling takes continuous signal but quantization takes sampling -> discrete signal
    //TODO split this BIG if into two functions
    OPERATION_TYPE type = getSelectedOperationType();
    if (!isMainSignalStrategyDiscrete()) {
        auto* mainSignal = dynamic_cast<ContinousSignal*>(mainSignalStrategy.get());
        switch (type) {
            case SAMPL:
                strat = new Sampling(std::unique_ptr<ContinousSignal>(mainSignal), samplingFrequency);
                break;
            case QUANT_CLIPPED:
//                strat = new Sampling(std::unique_ptr<ContinousSignal>(mainSignal, samplingFrequency);
                break;
            case QUANT_ROUND:
//                strat = new Sampling(mainSignal, samplingFrequency);
                break;
            default:
                throw std::logic_error("INVALID TYPE");
                //do th
    } } else {
        DiscreteSignal* mainSignal = dynamic_cast<DiscreteSignal*>(mainSignalStrategy.get());
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
        //do sth
    }
    //do sth with strat
    }





