

#include <cmath>
#include "signals/windows/HanningWindow.h"

double HanningWindow::w(int n) {
    return 0.5 - 0.5 * cos(2 * M_PI * n / M);
}

HanningWindow::HanningWindow(int m) : Window(m) {}
