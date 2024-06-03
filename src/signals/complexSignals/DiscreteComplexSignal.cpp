
#include "signals/complexSignals/DiscreteComplexSignal.h"

DiscreteComplexSignal::DiscreteComplexSignal(double time0, double dur, double freq) : ComplexSignal(time0, dur) {
    setFrequency(freq);
    this->numberOfSamples = static_cast<int>(dur * freq);
}

DiscreteComplexSignal::DiscreteComplexSignal(double time0, int numberOfSamples, double freq)
        : ComplexSignal(time0, numberOfSamples / freq), numberOfSamples(numberOfSamples) {
    setFrequency(freq);
}

int DiscreteComplexSignal::getNumberOfSamples() const {
    return numberOfSamples;
}

Signal &DiscreteComplexSignal::getSignal() {
    if (SignalStrategy::getSignal().empty()) {
        calculateSignal();
    }
    return SignalStrategy::getSignal();
}

void DiscreteComplexSignal::calculateSignal() {
    Signal &signal = SignalStrategy::getSignal();
    int i = 0;
    double freqToSampleCountRatio = getFrequency() / getNumberOfSamples();
    while (i < getNumberOfSamples()) {
        double value;
        switch (getType()) {
            case IMAGINARY:
                value = calculateSignalAtSample(i).imag();
                break;
            case ABSOLUTE:
                value = std::abs(calculateSignalAtSample(i));

                break;
            case ARGUMENT:
                value = std::arg(calculateSignalAtSample(i));

                break;
            default:
                value = calculateSignalAtSample(i).real();

        }
        signal.push_back(value, i * freqToSampleCountRatio);
        i++;
    }
}
