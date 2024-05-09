#include <cmath>
#include "windows/HammingWindow.h"

double HammingWindow::w(int n) {
    return 0.53836 - 0.46164 * cos((2 * M_PI * n) / M);
}
