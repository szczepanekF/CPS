
#include "signals/Sampling.h"

Sampling::Sampling(std::unique_ptr<ContinousSignal> strategy, double sampleRate)
: DiscreteSignal(strategy->getBeginTime(), strategy->getDuration(), sampleRate),
    strategy(std::move(strategy)) {

}

Sampling::Sampling(double time0, double dur, double freq, std::unique_ptr<ContinousSignal> strategy)
       {}

double Sampling::calculateSignalAt(double time) {
    return strategy->calculateSignalAt(time);
}

