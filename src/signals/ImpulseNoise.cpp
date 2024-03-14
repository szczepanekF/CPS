
#include "signals/ImpulseNoise.h"
#include <random>

double ImpulseNoise::calculateSignalAt(double) {
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_real_distribution<double> distr(0.0, 1.0);
    double randomValue = distr(generator);
    return randomValue <= probability ? getAmplitude() : 0;
}

ImpulseNoise::ImpulseNoise(double amp, double time0, double dur, double freq, double prob)
    : DiscreteSignal(amp, time0, dur, freq), probability(prob){

}
