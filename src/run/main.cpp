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
#include "signals/GaussianNoise.h"
#include "signals/UnitImpulseSignal.h"
#include "signals/UniformNoise.h"

namespace plt = matplotlibcpp;

int main() {
    SignalStrategy* signal = new ImpulseNoise(10, -5, 15,1, 0.4);

    auto data = signal->getSignal();
//    plt::scatter(data.first, data.second, 3);
    plt::plot<>(data.first, data.second,{{"linewidth" ,"0.5"}});
    plt::show();
    delete signal;
}
