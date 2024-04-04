#include "frontend/AcConversionComponent.h"
#include "imgui.h"


AcConversionComponent::AcConversionComponent() : samplingFrequency(0.0), quantizationLimit(0.0), MSE(0.0), SNR(0.0),
                                                 PSNR(0.0), MD(0.0) {
    initializeOperations();
}

void AcConversionComponent::initializeOperations() {
    auto *operation1 = new Operation(SAMPL, "Próbkowanie równomierne", "A/C");
    auto *operation2 = new Operation(QUANT1, "Kwantyzacja równomierna z obcięciem", "A/C");
    auto *operation3 = new Operation(QUANT2, "Kwantyzacja równomierna z zaokraglaniem", "A/C");
    auto *operation4 = new Operation(EXTRA, "Ekstrapolacja zerowego rzedu", "C/A");
    auto *operation5 = new Operation(INTER, "Interpolacja pierwszego rzedu", "C/A");
    auto *operation6 = new Operation(REC, "Rekonstrukcja w oparciu o funkcje sinc", "C/A");
    operations = {
            operation1,
            operation2,
            operation3,
            operation4,
            operation5,
            operation6,
    };
}

void AcConversionComponent::show() {
    drawOperationChoicePanel();
    drawInputParametersPanel();
    drawCalculatedMeasuresPanel();
}

void AcConversionComponent::drawOperationChoicePanel() {
    ImGui::SetNextWindowPos(ImVec2(50, 100), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_Always);
    ImGui::Begin("Operations", nullptr,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
    for (auto opeartion: operations) {
        if (ImGui::RadioButton(opeartion->getName(), opeartion->getIsActive())) {
            opeartion->setIsActive(true);
            for (auto differentOpeartion: operations) {
                if (differentOpeartion != opeartion) differentOpeartion->setIsActive(false);
            }
        }
    }
    ImGui::End();
}

void AcConversionComponent::drawInputParametersPanel() {
    ImGui::SetNextWindowPos(ImVec2(550, 100), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_Always);
    ImGui::Begin("Parametry", nullptr,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
    ImGui::SetNextItemWidth(100);
    ImGui::InputDouble("Czestotliwosc probkowania", &samplingFrequency);
    ImGui::SetNextItemWidth(100);
    ImGui::InputDouble("Próg kwantyzacji", &quantizationLimit);
    ImGui::End();
}

void AcConversionComponent::drawCalculatedMeasuresPanel() const {
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