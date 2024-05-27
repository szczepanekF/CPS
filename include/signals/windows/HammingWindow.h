
#pragma once

#include "Window.h"
class HammingWindow : public Window{
public:
    explicit HammingWindow(int m);

    double w(int n) override;

};

