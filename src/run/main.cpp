#include <iostream>
#include "matplotlibcpp.h"
#include "signals/ImpulseNoise.h"

namespace plt = matplotlibcpp;

int main() {
    ImpulseNoise* noise = new ImpulseNoise(10, 0, 10, 0.2, 0.5);
    plt::hist<int>({2,2,2,3,3,1,1,1,1,1,5,2,3,8,8,9,4});
    plt::show();
    delete noise;
}
