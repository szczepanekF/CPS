#include "imgui.h"
#include <stdio.h>
#include <fstream>
#include <GLFW/glfw3.h>
#include <implot.h>
#include <vector>
#include <iostream>
#include "../bindings/imgui_impl_opengl3.h"
#include "../bindings/imgui_impl_glfw.h"
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

GLFWwindow *window;
const char *glsl_version;
ImVec4 clear_color;

double amp;
double time0;
double prob;
double duration;
double basePeriod;
double freq;
double fillFactor;
double jumpTime;
//Signal* signal1;
std::vector<SignalStrategy *> signalStrategies;
SignalStrategy *signalStrategy;

static void glfw_error_callback(int error, const char *description) {
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

void setValue(double *var, double *value = nullptr) {
    var = value;
};

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

void createButton(const char *label, SignalStrategy *strategy) {
    ImGui::SetNextItemWidth(500);
//    ImGui::Begin("Button");
    if (ImGui::Button(label)) {
        delete signalStrategy;
        signalStrategy = strategy;
    }
//    ImGui::End();
}

void createButton(const char *label, bool save) {
    ImGui::SetNextItemWidth(500);
//    ImGui::Begin("Button");
    if (ImGui::Button(label)) {
        std::unique_ptr<SignalStrategy> sharedPtr(signalStrategy);
        SignalProcesor signalProcesor(std::move(sharedPtr));
        if(save){
            signalProcesor.saveSignalToBinary(signalStrategy->getSignal(), "file.bin");
        } else {
            signalStrategy = signalProcesor.readSignalFromBinary("file.bin");
        }
    }
//    ImGui::End();
}

void createPlot() {
    if (signalStrategy != nullptr) {
        if (ImPlot::BeginPlot("My Plot")) {
            Signal signal1 = signalStrategy->getSignal();
            float *xData = new float[signal1.size()];
            float *yData = new float[signal1.size()];
            signal1.convertToFloat(yData, xData);
            ImPlot::PlotLine("My Line Plot", xData, yData, signal1.size());
            ImPlot::EndPlot();
        }
    }
}

void inputDataArea() {
    ImGui::InputDouble("Enter amp", &amp, 0.1, 0.5);
    ImGui::InputDouble("Enter duration", &duration, 0.1, 0.5);
    ImGui::InputDouble("Enter time0", &time0, 0.1, 0.5);
    ImGui::InputDouble("Enter base Period", &basePeriod, 0.1, 0.5);
    ImGui::InputDouble("Enter Jump time", &jumpTime, 0.1, 0.5);
    ImGui::InputDouble("Enter frequency", &freq, 0.1, 0.5);
    ImGui::InputDouble("Enter fill factor", &fillFactor, 0.1, 0.5);
    ImGui::InputDouble("Enter prob", &prob, 0.1, 0.5);

}

void fillTheFrame() {
//    ImGui::SetNextWindowSize(ImVec2(1200, 700));
    ImGui::Begin("CPS zadanie 1");
//    , NULL,
//                 ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
    inputDataArea();

    createButton("Sinusoidal signal", new SinusoidalSignal(amp,time0,duration,basePeriod));
    createButton("Gausian noise", new GaussianNoise(amp,time0,duration));
    createButton("Impulse noise", new ImpulseNoise(amp,time0,duration,freq,prob));
    createButton("Rectangular signal", new RectangularSignal(amp,time0,duration,basePeriod,fillFactor));
    createButton("Rectangular simetric signal", new RectangularSymmetricSignal(amp,time0,duration,basePeriod,fillFactor));
    createButton("Sinusoidal one half rectified signal", new SinusoidalOneHalfRectifiedSignal(amp,time0,duration,basePeriod));
    createButton("Sinusoidal two half rectified signal", new SinusoidalTwoHalfRectifiedSignal(amp,time0,duration,basePeriod));
    createButton("Triangular signal", new TriangularSignal(amp,time0,duration,basePeriod,fillFactor));
    createButton("Uniform Noise", new UniformNoise(amp, time0,duration));
    createButton("Unit impulse signal", new UnitImpulseSignal(amp,time0,duration,freq,jumpTime));
    createButton("Unit jump signal", new UnitJumpSignal(amp,time0,duration,jumpTime));
//    ImGui::SetNextItemWidth(ImGui::GetWindowWidth());
//    if (ImPlot::BeginPlot("Signal Plot")) {
    createPlot();

    createButton("Save", true);
    createButton("Load", false);
//    ImPlot::PlotLine(, signalStrategy->getSignal().timeValues, signalStrategy->getSignal().signalValues.size());
//        ImPlot::EndPlot();
//}
//    createTextArea();
    ImGui::End();
}

bool canBeProceeded = false;


int main() {
    if (isFrameInitSuccessful()) {
        configureWindow();
        while (!glfwWindowShouldClose(window)) {
              setFrame();
              fillTheFrame();
              render();
        }
        clearTheMess();
    }
}