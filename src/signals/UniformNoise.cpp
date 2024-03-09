
#include "signals/UniformNoise.h"
#include "random"

double UniformNoise::calculateSignalAt(double) {
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_real_distribution<double> distr(-getAmplitude(), getAmplitude());
    return distr(generator);
}

UniformNoise::UniformNoise(double amp, double time0, double dur) : ContinousSignal(amp, time0, dur) {
}
