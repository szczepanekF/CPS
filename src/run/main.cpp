#include <iostream>
#include "matplotlibcpp.h"
#include "signals/ImpulseNoise.h"
#include "signals/SquareSignal.h"
#include "signals/SinusoidalSignal.h"


namespace plt = matplotlibcpp;

int main() {
//    ImpulseNoise* noise = new ImpulseNoise(10, 0, 10, 0.2, 0.5);
//    SquareSignal* signal = new SquareSignal(10, 0, 50, 5, 0.2);
    SinusoidalSignal* signal = new SinusoidalSignal(10, 0, 10, 0.1);
    auto data = signal->getSignal();
//    plt::hist<int>({2,2,2,3,3,1,1,1,1,1,5,2,3,8,8,9,4});
//    plt::scatter(data.first, data.second);
    plt::plot<>(data.first, data.second);
    plt::show();
    delete signal;
}
