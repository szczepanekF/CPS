
#pragma once

#include "Window.h"

class HanningWindow : public Window{
public:
    explicit HanningWindow(int m);

    double w(int n) override;

};
