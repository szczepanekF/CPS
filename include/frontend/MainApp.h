
#pragma once


#include <GLFW/glfw3.h>
#include <imgui.h>

class MainApp {

public:
    void run();

    MainApp();

private:
    void clear();

    static void glfw_error_callback(int error, const char *description);

    bool isFrameInitSuccessful();

    void configureWindow();
    static void setFrame();
    void render();
    GLFWwindow *window;
    const char *glsl_version;
    ImVec4 clear_color;
    int display_w, display_h;
    float y;
};
