#include "imgui.h"
#include <stdio.h>
#include <fstream>
#include <GLFW/glfw3.h>
#include <implot.h>
#include <vector>
#include <iostream>
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#include "signals/SignalStrategy.h"
#include "signals/SinusoidalSignal.h"
#include "signals/GaussianNoise.h"
#include "signals/ImpulseNoise.h"
#include "signals/RectangularSignal.h"
#include "signals/RectangularSymmetricSignal.h"
#include "signals/SinusoidalOneHalfRectifiedSignal.h"
#include "signals/SinusoidalTwoHalfRectifiedSignal.h"
#include "signals/TriangularSignal.h"
#include "signals/UniformNoise.h"
#include "signals/UnitImpulseSignal.h"
#include "signals/UnitJumpSignal.h"
#include "operations/SignalProcesor.h"
#include "frontend/Option.h"
#include "frontend/Parameter.h"

GLFWwindow *window;
const char *glsl_version;
ImVec4 clear_color;

std::vector<SignalStrategy *> signalStrategies;
SignalStrategy *signalStrategy;

static void glfw_error_callback(int error, const char *description) {
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}


bool isFrameInitSuccessful() {
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) {
        return false;
    }
    glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    window = glfwCreateWindow(1280, 720, "CPS zad1", nullptr, nullptr);
    if (window == nullptr) {
        return false;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync
    return true;
}

void configureWindow() {
    ImGui::CreateContext();
    ImPlot::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);

    ImGui_ImplOpenGL3_Init(glsl_version);
    clear_color = ImVec4(0.10f, 0.40f, 0.80f, 1.00f);
}

void render() {
// Rendering
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w,
                 clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
}

void clearTheMess() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImPlot::DestroyContext();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
}

void setFrame() {
    glfwPollEvents();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

//void createButton(const char *label, SignalStrategy *strategy) {
//    ImGui::SetNextItemWidth(500);
////    ImGui::Begin("Button");
//    if (ImGui::Button(label)) {
//        delete signalStrategy;
//        signalStrategy = strategy;
//    }
////    ImGui::End();
//}
//
void createButton(const char *label, int option) {
    ImGui::SetNextItemWidth(500);
    if (ImGui::Button(label)) {
        std::unique_ptr<SignalStrategy> sharedPtr(signalStrategy);
        SignalProcesor signalProcesor(std::move(sharedPtr));
        if (option == 0) {
            signalProcesor.saveSignalToBinary(signalStrategy->getSignal(), "file.bin");
        } else if (option == 1) {
            signalStrategy = signalProcesor.readSignalFromBinary("file.bin");
        } else if (option == 2) {

        }
    }
}

void createPlot() {
    if (ImPlot::BeginPlot("Plot")) {
        float *xData;
        float *yData;
        int size;
        if (signalStrategy != nullptr) {
            Signal signal1 = signalStrategy->getSignal();
            xData = new float[signal1.size()];
            yData = new float[signal1.size()];
            size = signal1.size();
            signal1.convertToFloat(yData, xData);
        } else {
            size = 10;
            xData = new float[size]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
            yData = new float[size]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        }
        ImPlot::PlotLine("My Line Plot", xData, yData, size);
        ImPlot::EndPlot();
    }
}


//void fillTheFrame() {
////    ImGui::SetNextWindowSize(ImVec2(1200, 700));
//    ImGui::Begin("CPS zadanie 1");
////    , NULL,
////                 ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
//    inputDataArea();
//
//
////
////    createPlot();
////
////    createButton("Save", true);
////    createButton("Load", false);
//    if (ImGui::Checkbox("Option 1", &option1))
//    {
//        if (option1)
//        {
//            std::cout<<"active";
//        }
//    }
//
//    ImGui::End();
//}
//
//bool canBeProceeded = false;
//}

void createCheckbox(Option &option) {
    if (ImGui::Checkbox(option.title.c_str(), &option.visibility)) {
        delete signalStrategy;
        signalStrategy = option.signalStrategy;
    }
}

void createCheckbox(SignalStrategy *strategy, const char *label, bool check) {
    if (ImGui::Checkbox(label, &check)) {
        delete signalStrategy;
        signalStrategy = strategy;
    }
}


int main() {
    double amp, time0, prob, duration, basePeriod, freq, fillFactor, jumpTime;
    bool ampVisibility, time0Visibility, probVisibility, durationVisibility, basePeriodVisibility, freqVisibility, fillFactorVisibility, jumpTimeVisibility;
    bool SinusoidalSignalCheck, GaussianNoiseCheck, ImpulseNoiseCheck, RectangularSignalCheck, RectangularSymmetricSignalCheck, SinusoidalOneHalfRectifiedSignalCheck, SinusoidalTwoHalfRectifiedSignalCheck, TriangularSignalCheck, UniformNoiseCheck, UnitImpulseSignalCheck, UnitJumpSignalCheck;
    std::string filename = "";
    std::vector<Parameter> params = {
            Parameter("Amplitude", true, amp),
            Parameter("Start time", true, time0),
            Parameter("Prob", true, prob),
            Parameter("Duration", true, duration),
            Parameter("Base period", true, basePeriod),
            Parameter("Frequency", true, freq),
            Parameter("Fill factor", true, fillFactor),
            Parameter("Jump time", true, jumpTime),
    };

    std::vector<Option> options = {
            Option(new SinusoidalSignal(amp, time0, duration, basePeriod), "Sinusoidal signal"),
            Option(new GaussianNoise(amp, time0, duration), "Gausian noise"),
            Option(new ImpulseNoise(amp, time0, duration, freq, prob), "Impulse noise"),
            Option(new RectangularSignal(amp, time0, duration, basePeriod, fillFactor), "Rectangular signal"),
            Option(new RectangularSymmetricSignal(amp, time0, duration, basePeriod, fillFactor),"Rectangular simetric signal"),
            Option(new SinusoidalOneHalfRectifiedSignal(amp, time0, duration, basePeriod),"Sinusoidal one half rectified signal"),
            Option(new SinusoidalTwoHalfRectifiedSignal(amp, time0, duration, basePeriod),"Sinusoidal two half rectified signal"),
            Option(new TriangularSignal(amp, time0, duration, basePeriod, fillFactor), "Triangular signal"),
            Option(new UniformNoise(amp, time0, duration), "Uniform Noise"),
            Option(new UnitImpulseSignal(amp, time0, duration, freq, jumpTime), "Unit impulse signal"),
            Option(new UnitJumpSignal(amp, time0, duration, jumpTime), "Unit jump signal")
    };
    if (isFrameInitSuccessful()) {
        configureWindow();
        while (!glfwWindowShouldClose(window)) {
            setFrame();

            ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiCond_Always);
            ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_Always);
            ImGui::Begin("Signals and noises", NULL,
                         ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
//            for (Option &option: options) {
                createCheckbox(new SinusoidalSignal(amp, time0, duration, basePeriod), "Sinusoidal signal", SinusoidalSignalCheck);
                createCheckbox(new GaussianNoise(amp, time0, duration), "Gausian noise", GaussianNoiseCheck);
                createCheckbox(new ImpulseNoise(amp, time0, duration, freq, prob), "Impulse noise", ImpulseNoiseCheck);
                createCheckbox(new RectangularSignal(amp, time0, duration, basePeriod, fillFactor), "Rectangular signal", RectangularSignalCheck);
                createCheckbox(new RectangularSymmetricSignal(amp, time0, duration, basePeriod, fillFactor),"Rectangular simetric signal", RectangularSymmetricSignalCheck);
                createCheckbox(new SinusoidalOneHalfRectifiedSignal(amp, time0, duration, basePeriod),"Sinusoidal one half rectified signal", SinusoidalOneHalfRectifiedSignalCheck);
                createCheckbox(new SinusoidalTwoHalfRectifiedSignal(amp, time0, duration, basePeriod),"Sinusoidal two half rectified signal", SinusoidalTwoHalfRectifiedSignalCheck);
                createCheckbox(new TriangularSignal(amp, time0, duration, basePeriod, fillFactor), "Triangular signal", TriangularSignalCheck);
                createCheckbox(new UniformNoise(amp, time0, duration), "Uniform Noise", UniformNoiseCheck);
                createCheckbox(new UnitImpulseSignal(amp, time0, duration, freq, jumpTime), "Unit impulse signal", UnitImpulseSignalCheck);
                createCheckbox(new UnitJumpSignal(amp, time0, duration, jumpTime), "Unit jump signal", UnitJumpSignalCheck);
//            }
            ImGui::End();

            ImGui::SetNextWindowPos(ImVec2(440, 20), ImGuiCond_Always);
            ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_Always);
            ImGui::Begin("Parameters", NULL,
                         ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
            for (Parameter &parameter: params) {
                ImGui::InputDouble(parameter.name.c_str(), &parameter.value, 0.1, 1);
            }
            ImGui::End();

            ImGui::SetNextWindowPos(ImVec2(860, 20), ImGuiCond_Always);
            ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_Always);
            ImGui::Begin("Buttons", NULL,
                         ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
            createButton("Save to file", 0);
            createButton("Load from file", 1);
            createButton("Draw the plot", 2);
            ImGui::End();

            ImGui::SetNextWindowPos(ImVec2(20, 340), ImGuiCond_Always);
            ImGui::SetNextWindowSize(ImVec2(1240, 360), ImGuiCond_Always);
            ImGui::Begin("Plot", NULL,
                         ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
            createPlot();
            ImGui::End();

            render();
        }
        clearTheMess();
    }
}