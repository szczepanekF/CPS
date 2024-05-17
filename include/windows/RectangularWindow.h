
#pragma once

#include "Window.h"
class RectangularWindow : public Window{
public:
    explicit RectangularWindow(int m);

    double w(int n) override;
};
