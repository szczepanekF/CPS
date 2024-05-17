
#include <cmath>
#include "windows/BlackmanWindow.h"

double BlackmanWindow::w(int n) {
    return 0.42 - 0.5 * cos((2 * M_PI * n) / M) + 0.08 * cos((4 * M_PI * n) / M);
}

BlackmanWindow::BlackmanWindow(int m) : Window(m) {}
