
#pragma once

#include "Window.h"
class BlackmanWindow :public Window{
public:
    explicit BlackmanWindow(int m);

    double w(int n) override;

};
