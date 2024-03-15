
#pragma once


class MainApp {

public:
    void run();
private:
    void clear();

    static void glfw_error_callback(int error, const char *description);

    bool isFrameInitSuccessful();

    void configureWindow();

    void render();
};
