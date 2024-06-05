
#include <imgui.h>
#include <iostream>
#include "frontend/ComplexTransformerComponent.h"
#include "signals/baseSignals/SinusoidalSignal.h"
#include "signals/baseSignals/OperationResultSignal.h"
#include "signals/operations/SignalProcesor.h"
#include "signals/transformers/WaveletTransform.h"

ComplexTransformerComponent::ComplexTransformerComponent(std::shared_ptr<Mediator> mediator)
        : Component(std::move(mediator)), signalChoice(0), transformerChoice(0), SAMPLING_FREQUENCY(16), transformer(),
          realTransform(), complexTransform(), firstComplexVisualModeOn(true), filename() {

}

void ComplexTransformerComponent::show() {
    showSignalChoice();
    showTransformerChoice();

    drawComplexFileOperations();

}

void ComplexTransformerComponent::showSignalChoice() {
    ImGui::SetNextWindowPos(ImVec2(50, 50), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(200, 250), ImGuiCond_Always);
    ImGui::Begin("Signals", nullptr,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
    ImGui::RadioButton("S1", &signalChoice, 0);
    ImGui::RadioButton("S2", &signalChoice, 1);
    ImGui::RadioButton("S3", &signalChoice, 2);
    if (ImGui::Button("Draw signal")) {
        drawSignal();
    }
    ImGui::End();
}

void ComplexTransformerComponent::showTransformerChoice() {
    ImGui::SetNextWindowPos(ImVec2(300, 50), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(300, 325), ImGuiCond_Always);
    ImGui::Begin("Transformers", nullptr,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
    ImGui::RadioButton("DFT", &transformerChoice, 0);
    ImGui::RadioButton("DIT FFT", &transformerChoice, 1);
    ImGui::RadioButton("DIF FFT", &transformerChoice, 2);
    ImGui::RadioButton("DCT", &transformerChoice, 3);
    ImGui::RadioButton("FCT", &transformerChoice, 4);
    ImGui::RadioButton("Walsh-Hadamard transform", &transformerChoice, 5);
    ImGui::RadioButton("Fast Walsh-Hadamard transform", &transformerChoice, 6);
    if (ImGui::Button("Draw transformation")) {
        drawTransformation();
    }

    if (complexTransform != nullptr && ImGui::Button("Switch complex visual mode")) {
        firstComplexVisualModeOn = !firstComplexVisualModeOn;
        updateComplexSignal();
    }
    ImGui::End();


}

void ComplexTransformerComponent::drawTransformation() {
    firstComplexVisualModeOn = true;
    clearTransformSignals();
    std::unique_ptr<ContinousSignal> stratUniquePtr = getChosenSignal();


    std::unique_ptr<Sampling> sampl = std::make_unique<Sampling>(std::move(stratUniquePtr), SAMPLING_FREQUENCY);
    tranformSampledSignal(std::move(sampl));
    plotTransformedSignal();

}

void ComplexTransformerComponent::drawSignal() {
    clearTransformSignals();
    std::unique_ptr<SignalStrategy> stratUniquePtr = getChosenSignal();
    clearSignals();
    addSignal(nullptr, stratUniquePtr->getSignal());
}


std::unique_ptr<OperationResultSignal> ComplexTransformerComponent::getChosenSignal() const {
    std::unique_ptr<SignalStrategy> strat;
    std::unique_ptr<SignalStrategy> strat2;
    std::unique_ptr<OperationResultSignal> resultSignal;
    double signalDuration = 16;
    switch (signalChoice) {
        case 0:
            strat = std::make_unique<SinusoidalSignal>(2, -0.5, signalDuration, 2);
            strat2 = std::make_unique<SinusoidalSignal>(5, -0.125, signalDuration, 0.5);
            resultSignal = std::make_unique<OperationResultSignal>(std::move(strat), std::move(strat2),
                                                                   [](double a, double b) { return a + b; });
            break;
        case 1:
            strat = std::make_unique<SinusoidalSignal>(2, 0, signalDuration, 2);
            strat2 = std::make_unique<SinusoidalSignal>(1, 0, signalDuration, 1);
            resultSignal = std::make_unique<OperationResultSignal>(std::move(strat), std::move(strat2),
                                                                   [](double a, double b) { return a + b; });
            strat2 = std::make_unique<SinusoidalSignal>(5, 0, signalDuration, 0.5);
            resultSignal = std::make_unique<OperationResultSignal>(std::move(resultSignal), std::move(strat2),
                                                                   [](double a, double b) { return a + b; });
            break;
        case 2:
            strat = std::make_unique<SinusoidalSignal>(5, 0, signalDuration, 2);
            strat2 = std::make_unique<SinusoidalSignal>(1, 0, signalDuration, 0.25);
            resultSignal = std::make_unique<OperationResultSignal>(std::move(strat), std::move(strat2),
                                                                   [](double a, double b) { return a + b; });
            break;
        default:
            return nullptr;
    }
    return resultSignal;
}

void ComplexTransformerComponent::tranformSampledSignal(std::unique_ptr<Sampling> signal) {
    clearSignals();
    if (isChosenComplexTrasform()) {
        transformToComplex(std::move(signal));
        return;
    }
    transformToReal(std::move(signal));
}

bool ComplexTransformerComponent::isChosenComplexTrasform() const {
    return transformerChoice < 3;
}

void ComplexTransformerComponent::transformToComplex(std::unique_ptr<Sampling> signal) {
    realTransform.reset();
    switch (transformerChoice) {
        case 0:
            complexTransform = transformer.DFT(*signal);
            break;
        case 1:
            complexTransform = transformer.DIT_FFT(*signal);
            break;
        case 2:
            complexTransform = transformer.DIF_FFT(*signal);
            break;
        default:
            complexTransform.reset();
            return;
    }
}

void ComplexTransformerComponent::transformToReal(std::unique_ptr<Sampling> signal) {
    complexTransform.reset();
    switch (transformerChoice) {
        case 3:
            realTransform = transformer.DCT(*signal);
            break;
        case 4:
            realTransform = transformer.FCT(*signal);
            break;
        case 5:
            realTransform = transformer.Walsh_Hadamard(*signal);
            break;
        case 6:
            realTransform = transformer.Fast_Walsh_hadamard(*signal);
            break;
        default:
            realTransform.reset();
            return;
    }
}

void ComplexTransformerComponent::plotTransformedSignal() {
    if (complexTransform != nullptr) {
        updateComplexSignal();
    } else if (realTransform != nullptr) {
        clearSignals();
        addSignal(nullptr, realTransform->getSignal(), "Real transformed signal");
    }

}

void ComplexTransformerComponent::updateComplexSignal() {
    ComplexSignalValueType val1 = REAL;
    ComplexSignalValueType val2 = IMAGINARY;
    std::string str1 = "real values";
    std::string str2 = "imaginary values";
    if (!firstComplexVisualModeOn) {
        val1 = ABSOLUTE;
        val2 = ARGUMENT;
        str1 = "absolute values";
        str2 = "phase values";
    }


    clearSignals();
    complexTransform->setType(val1);

    addSignal(nullptr, complexTransform->getSignal(), str1);
    complexTransform->setType(val2);
    setSecondPlotSignal(complexTransform->getSignal(), str2);
}

void ComplexTransformerComponent::clearTransformSignals() {
    realTransform.reset();
    complexTransform.reset();
    firstComplexVisualModeOn = true;
}

void ComplexTransformerComponent::drawComplexFileOperations() {
    ImGui::SetNextWindowPos(ImVec2(650, 50), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(300, 150), ImGuiCond_Always);
    ImGui::Begin("FileOperations", nullptr,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
    showFileOperations();
    ImGui::End();
}

void ComplexTransformerComponent::showFileOperations() {
    ImGui::InputText("Filename", filename, sizeof(filename));
    ImGui::Spacing();
    ImGui::SetNextItemWidth(500);
    definePopups();

    if (ImGui::Button("Save to file")) {
        if (filename[0] != '\0' && complexTransform != nullptr) {
            SignalProcesor signalProcesor;
            signalProcesor.saveComplexSignalToBinary(*complexTransform, filename);
            ImGui::OpenPopup("fileSuccess");
        } else {
            ImGui::OpenPopup("FileError");
        }

    }
    ImGui::SameLine();
    if (ImGui::Button("Load from file")) {
        if (filename[0] != '\0') {
            SignalProcesor signalProcesor;
            realTransform.reset();
            complexTransform = signalProcesor.readComplexSignalFromBinary(filename);
            plotTransformedSignal();
        } else {
            ImGui::OpenPopup("FileError");
        }
    }
    ImGui::Spacing();
    if (ImGui::Button("Clear signal")) {
        clearTransformSignals();
        clearSignals();
        std::ranges::fill(filename, '\0');
    }
}

void ComplexTransformerComponent::definePopups() {
    if (ImGui::BeginPopup("fileSuccess")) {
        ImGui::Text(("File operation was successful on file: " + std::string(filename)).c_str());
        if (ImGui::Button("Close")) {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
    if (ImGui::BeginPopup("FileError")) {
        ImGui::Text("Wrong filename or not selected complex signal");
        if (ImGui::Button("Close")) {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}
