#include "imgui.h"
#include <stdio.h>
#include <fstream>
#include "signals/SignalStrategy.h"
#include "operations/SignalProcesor.h"
#include "signals/SinusoidalSignal.h"
#include "matplotlibcpp.h"
#include "../bindings/imgui_impl_opengl3.h"
#include "../bindings/imgui_impl_glfw.h"

//#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif

#include <GLFW/glfw3.h> // Will drag system OpenGL headers

//// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
//// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
//// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

//// This example can also compile and run with Emscripten! See 'Makefile.emscripten' for details.
#ifdef __EMSCRIPTEN__
#include "../libs/emscripten/emscripten_mainloop_stub.h"
#endif

static void glfw_error_callback(int error, const char *description) {
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}


void
saveVectorsToBinary(const std::vector<double> &xData, const std::vector<double> &yData, const std::string &filename) {
    // Open a binary file for writing
    std::ofstream outFile(filename, std::ios::out | std::ios::binary | std::ios::trunc);
    if (!outFile.is_open()) {
        std::cerr << "Error opening file for writing!" << std::endl;
        return;
    }

    // Write the size of the vectors
    size_t sizeX = xData.size();
    size_t sizeY = yData.size();
    outFile.write(reinterpret_cast<const char *>(&sizeX), sizeof(sizeX));
    outFile.write(reinterpret_cast<const char *>(&sizeY), sizeof(sizeY));

    // Write the data of the vectors
    outFile.write(reinterpret_cast<const char *>(xData.data()), sizeX * sizeof(double));
    outFile.write(reinterpret_cast<const char *>(yData.data()), sizeY * sizeof(double));

    // Close the file
    outFile.close();

    std::cout << "Vectors saved to file successfully." << std::endl;
}

void readVectorsFromBinary(std::vector<double> &xData, std::vector<double> &yData, const std::string &filename) {
    // Open a binary file for reading
    std::ifstream inFile(filename, std::ios::in | std::ios::binary);
    if (!inFile.is_open()) {
        std::cerr << "Error opening file for reading!" << std::endl;
        return;
    }

    // Read the size of the vectors
    size_t sizeX, sizeY;
    inFile.read(reinterpret_cast<char *>(&sizeX), sizeof(sizeX));
    inFile.read(reinterpret_cast<char *>(&sizeY), sizeof(sizeY));

    // Resize vectors to fit the read data
    xData.resize(sizeX);
    yData.resize(sizeY);

    // Read the data of the vectors
    inFile.read(reinterpret_cast<char *>(xData.data()), sizeX * sizeof(double));
    inFile.read(reinterpret_cast<char *>(yData.data()), sizeY * sizeof(double));

    // Close the file
    inFile.close();

    std::cout << "Vectors read from file successfully." << std::endl;
}


void convertDataVector(std::vector<double> doubleVector, float *tab) {
    size_t size = doubleVector.size();
    for (size_t i = 0; i < size; ++i) {
        tab[i] = static_cast<float>(doubleVector[i]);
    }
}

namespace plt = matplotlibcpp;

// Main code
int main() {
    Signal signalFromFIle;
    readVectorsFromBinary(signalFromFIle.signalValues, signalFromFIle.timeValues, "signal_data.bin");
    int size = signalFromFIle.signalValues.size();
    float *signalValues = new float[size];
    float *timeValues = new float[size];
    std::vector<float> xData = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
    std::vector<float> yData = {2.0f, 3.0f, 1.5f, 4.0f, 2.5f};

    convertDataVector(signalFromFIle.signalValues, signalValues);
    convertDataVector(signalFromFIle.timeValues, timeValues);
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char* glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char *glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    // Create window with graphics context
    GLFWwindow *window = glfwCreateWindow(1280, 720, "CPS zad1", nullptr, nullptr);
    if (window == nullptr)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
#ifdef __EMSCRIPTEN__
    ImGui_ImplGlfw_InstallEmscriptenCanvasResizeCallback("#canvas");
#endif
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Our state
    bool show_demo_window = false;
    bool show_another_window = false;
    double ampInput = 0.0;

    ImVec4 clear_color = ImVec4(0.10f, 0.40f, 0.80f, 1.00f);

//    // Main loop
#ifdef __EMSCRIPTEN__
    // For an Emscripten build we are disabling file-system access, so let's not attempt to do a fopen() of the imgui.ini file.
    // You may manually call LoadIniSettingsFromMemory() to load settings from your own storage.
    io.IniFilename = nullptr;
    EMSCRIPTEN_MAINLOOP_BEGIN
#else
    while (!glfwWindowShouldClose(window))
#endif
    {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::SetNextWindowSize(ImVec2(1200, 700));
        ImGui::Begin("CPS zadanie 1", NULL,
                     ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
//        ImGui::PlotLines("xd", (float (*)(void *,
//                                          int)) reinterpret_cast<const float *>(signalFromFIle.timeValues.data()), signalFromFIle.signalValues.data(), size);
ImVec2 plotSize(400, 300);
ImGui::PlotLines("Data Plot", signalValues, size);

        ImVec2 pos = ImGui::GetCursorScreenPos();

        ImGui::GetWindowDrawList()->AddText(pos, IM_COL32_WHITE, "X Axis", NULL);

//            if (ImGui::BeginTabItem("Tab 1")) {
//                ImGui::InputDouble("Set amplitude value", &ampInput, 0.01, 0.1, "%.2f", ImGuiInputTextFlags_CharsDecimal);
//                ImGui::Text("Amplitude for signal = %.2f", ampInput);
//                ImGui::EndTabItem();
//            }
//
//            if (ImGui::BeginTabItem("Tab 2")) {
//
//
//            }
//
//            ImGui::EndTabBar();
//        }
        ImGui::End();

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
//        // Poll and handle events (inputs, window resize, etc.)
//        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
//        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
//        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
//        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
//        glfwPollEvents();
//
//        // Start the Dear ImGui frame
//        ImGui_ImplOpenGL3_NewFrame();
//        ImGui_ImplGlfw_NewFrame();
//        ImGui::NewFrame();
//
//        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
//        if (show_demo_window)
//            ImGui::ShowDemoWindow(&show_demo_window);
//
//        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
//        {
//            static float f = 0.0f;
//            static int counter = 0;
//
//            ImGui::Begin("CPS zadanie 1");                          // Create a window called "Hello, world!" and append into it.
//
//            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
//            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
//            ImGui::Checkbox("Another Window", &show_another_window);
//
//            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
//            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
//
//            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
//                counter++;
//            ImGui::SameLine();
//            ImGui::Text("counter = %d", counter);
//
//            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", static_cast<double>(1000.0f / io.Framerate), static_cast<double>(io.Framerate));
//            ImGui::End();
//        }
//
//        // 3. Show another simple window.
//        if (show_another_window)
//        {
//            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
//            ImGui::Text("Hello from another window!");
//            if (ImGui::Button("Close Me"))
//                show_another_window = false;
//            ImGui::End();
//        }
//
//        // Rendering
//        ImGui::Render();
//        int display_w, display_h;
//        glfwGetFramebufferSize(window, &display_w, &display_h);
//        glViewport(0, 0, display_w, display_h);
//        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
//        glClear(GL_COLOR_BUFFER_BIT);
//        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//
//        glfwSwapBuffers(window);
//    }
//#ifdef __EMSCRIPTEN__
//    EMSCRIPTEN_MAINLOOP_END;
//#endif

//    // Cleanup
//    ImGui_ImplOpenGL3_Shutdown();
//    ImGui_ImplGlfw_Shutdown();
//    ImGui::DestroyContext();
//
//    glfwDestroyWindow(window);
//    glfwTerminate();
//
//    SignalStrategy* sinusoidalSignal = new SinusoidalSignal(2,2, 6, 0.4);
//    SignalStrategy* sinusoidalSignal1 = new SinusoidalSignal(1,2, 6, 0.1);
//    std::vector<SignalStrategy*>signals;
//    Signal signalData = sinusoidalSignal->getSignal();
//    saveVectorsToBinary(signalData.signalValues, signalData.timeValues, "signal_data.bin");

//    Signal signalData1 = sinusoidalSignal1->getSignal();
//    plt::plot<>(signalFromFIle.timeValues, signalFromFIle.signalValues);
//    Signal signalFromFIle;
//    readVectorsFromBinary(signalFromFIle.signalValues, signalFromFIle.timeValues, "signal_data.bin");
//    float* signalValues = new float[signalFromFIle.signalValues.size()];
//    float* timeValues = new float[signalFromFIle.timeValues.size()];
//    convertDataVector(signalFromFIle.signalValues, signalValues);
//    convertDataVector(signalFromFIle.timeValues, timeValues);


    delete[] signalValues;
    delete[] timeValues;
//    plt::plot<>(signalData1.timeValues, signalData1.signalValues);
//    signals.push_back(sinusoidalSignal);
//    signals.push_back(sinusoidalSignal1);
//    Calculator* calculator = new Calculator(signals);
//    Signal data = calculator->getCalculatedSignal("add");
//    plt::plot<>(data.timeValues, data.signalValues);
    plt::show();
//    return 0;
}