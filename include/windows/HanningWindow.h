
#pragma once

#include "Window.h"

class HanningWindow : public Window{
public:
    double w(int n) override;

};
