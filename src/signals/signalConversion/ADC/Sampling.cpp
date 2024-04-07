
#include <iostream>
#include "signals/signalConversion/ADC/Sampling.h"

Sampling::Sampling(std::unique_ptr<ContinousSignal> strategy, double sampleRate)
: DiscreteSignal(strategy->getBeginTime(), strategy->getDuration(), sampleRate),
    strategy(std::move(strategy)) {

}


double Sampling::calculateSignalAt(double time) {
    std::cout<<"TEST";
    strategy->getSignal();
    return 0;
//    return strategy->calculateSignalAt(time);
}

