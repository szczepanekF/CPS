
#include "signals/windows/RectangularWindow.h"

RectangularWindow::RectangularWindow(int m) : Window(m) {}

double RectangularWindow::w(int) {
    return 1;
}
