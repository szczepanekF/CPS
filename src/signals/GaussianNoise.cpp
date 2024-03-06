#include "signals/GaussianNoise.h"
#include <random>


double GaussianNoise::calculateSignalAt(double) {
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::normal_distribution <double> distr{0, 1.0};
    return distr(generator);
}

GaussianNoise::GaussianNoise(double amp, double time0, double dur) : SignalStrategy(amp, time0, dur) {
}
