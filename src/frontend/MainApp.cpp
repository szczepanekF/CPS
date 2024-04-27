
#include "frontend/MainApp.h"
#include "frontend/SignalManagementComponent.h"
#include "frontend/ConversionComponent.h"
#include "frontend/PlotComponent.h"
#include "imgui.h"
#include <implot.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include <iostream>
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#include "mediator/SignalMediator.h"


GLFWwindow *window;
const char *glsl_version;
ImVec4 clear_color;
int display_w, display_h;



void MainApp::glfw_error_callback(int error, const char *description) {
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}



bool MainApp::isFrameInitSuccessful() {
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) {
        return false;
    }
    glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    window = glfwCreateWindow(1920, 1080, "CPS", nullptr, nullptr);
    if (window == nullptr) {
        return false;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync
    return true;
}

void MainApp::configureWindow() {
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

void MainApp::render() {
// Rendering
    ImGui::Render();
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w,
                 clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
}

void MainApp::clear() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImPlot::DestroyContext();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
}



void MainApp::setFrame() {
    glfwPollEvents();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}




void MainApp::run() {
    std::shared_ptr<SignalMediator> mediator = std::make_shared<SignalMediator>();
    SignalManagementComponent comp(mediator);
    ConversionComponent conCom(mediator);
    PlotComponent *plotComp = PlotComponent::getInstance();
    if (isFrameInitSuccessful()) {
        configureWindow();
        while (!glfwWindowShouldClose(window)) {
            setFrame();
            ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
            ImGui::SetNextWindowSize(ImVec2(display_w, 430), ImGuiCond_Always);
            ImGui::Begin("Assignments", nullptr,
                         ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
            if (ImGui::BeginTabBar("MyTabBar"))
            {
                if (ImGui::BeginTabItem("Signal creation"))
                {
                    comp.show();
                    ImGui::EndTabItem();
                }

                if (ImGui::BeginTabItem("Signal conversion"))
                {
                    conCom.show();
                    ImGui::EndTabItem();
                }
                ImGui::EndTabBar();
            }

            ImGui::End();
            float x[] = {1, 2, 3, 4, 5};
            float y[] = {1, 4, 9, 16, 25};

            plotComp->show();
            render();
        }
        clear();
    }

}
