#include <iostream>
#include "matplotlibcpp.h"
#include "signals/ImpulseNoise.h"
#include "signals/RectangularSignal.h"
#include "signals/SinusoidalSignal.h"
#include "signals/SinusoidalOneHalfRectifiedSignal.h"
#include "signals/SinusoidalTwoHalfRectifiedSignal.h"
#include "signals/RectangularSymmetricSignal.h"
#include "signals/TriangularSignal.h"
#include "signals/UnitJumpSignal.h"


namespace plt = matplotlibcpp;

int main() {
//    ImpulseNoise* noise = new ImpulseNoise(10, 0, 10, 0.2, 0.5);
//    RectangularSignal* signal = new TriangularSignal(10, 10, 25, 5, 0.1);
//    SignalStrategy* signal = new SinusoidalTwoHalfRectifiedSignal(10, 0, 12 * M_PI, 2 * M_PI);
    SignalStrategy* signal = new UnitJumpSignal(5,0,10,3);
    auto data = signal->getSignal();
//    plt::hist<int>({2,2,2,3,3,1,1,1,1,1,5,2,3,8,8,9,4});
//    plt::scatter(data.first, data.second);
    plt::plot<>(data.first, data.second);
    plt::show();
    delete signal;
}
