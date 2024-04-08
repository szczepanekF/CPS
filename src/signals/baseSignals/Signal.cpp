#include "signals/baseSignals/Signal.h"
#include <cmath>
#include <iostream>
#include <algorithm>

Signal Signal::operator-(const Signal &s) const {
    Signal ret;
    ret.timeValues = this->timeValues;
    ret.signalValues = std::vector<double>(this->signalValues.size());
    for (size_t i = 0; i < signalValues.size(); i++) {
        ret.signalValues[i] = this->signalValues[i] - s.signalValues[i];
    }
    return ret;
}


Signal Signal::operator+(const Signal &s) const {
    Signal ret;
    ret.timeValues = this->timeValues;
    ret.signalValues = std::vector<double>(this->signalValues.size());
    for (size_t i = 0; i < signalValues.size(); i++) {
        ret.signalValues[i] = this->signalValues[i] + s.signalValues[i];
    }
    return ret;
}

Signal Signal::operator/(const Signal &s) const {
    Signal ret;
    ret.timeValues = this->timeValues;
    ret.signalValues = std::vector<double>(this->signalValues.size());
    for (size_t i = 0; i < signalValues.size(); i++) {
        if (s.signalValues[i] == 0) continue;
        ret.signalValues[i] = this->signalValues[i] / s.signalValues[i];
    }
    return ret;
}


Signal Signal::operator*(const Signal &s) const {
    Signal ret;
    ret.timeValues = this->timeValues;
    ret.signalValues = std::vector<double>(this->signalValues.size());
    for (size_t i = 0; i < signalValues.size(); i++) {
        ret.signalValues[i] = this->signalValues[i] * s.signalValues[i];
    }
    return ret;
}

double Signal::mean() const {
    double sum = 0;
    for (auto val: signalValues) {
        sum += val;
    }
    return sum / size();
}

double Signal::absMean() const {
    double sum = 0;
    for (auto val: signalValues) {
        sum += std::abs(val);
    }
    return sum / size();
}

double Signal::variance() const {
    double meanVal = mean();
    double sum = 0;
    for (auto val: signalValues) {
        sum += std::pow(val - meanVal, 2);
    }
    return sum / size();
}

double Signal::meanPower() const {
    double sum = 0;
    for (auto val: signalValues) {
        sum += std::pow(val, 2);
    }
    return sum / size();
}

double Signal::rms() const {
    return std::sqrt(meanPower());
}

size_t Signal::size() const {
    return signalValues.size();
}

double Signal::meanSquaredError(Signal other) const {
    if (other.size() != size()) {
        throw std::logic_error("Signals do not match size");
    }

    double sum = 0;
    for (size_t i = 0; i < size(); i++) {
        sum += std::pow(signalValues[i] - other.signalValues[i], 2);
    }
    return sum / size();
}

double Signal::signalToNoiseRatio(Signal other) const {
    if (other.size() != size()) {
        throw std::logic_error("Signals do not match size");
    }
    double meter = 0;
    double denominator = 0;
    for (size_t i = 0; i < size(); i++) {
        meter += std::pow(signalValues[i], 2);
        denominator += std::pow(signalValues[i] - other.signalValues[i], 2);
    }
    return 10 * std::log10(meter / denominator);
}

double Signal::peakSignalToNoiseRatio(Signal other) const {
    if (other.size() != size()) {
        throw std::logic_error("Signals do not match size");
    }
    auto maxElement = std::ranges::max_element(signalValues);
    double mse = meanSquaredError(other);
    return 10 * std::log10(*maxElement / mse);
}

double Signal::maxDifference(Signal other) const {
    if (other.size() != size()) {
        throw std::logic_error("Signals do not match size");
    }
    double max = 0;
    for (size_t i = 0; i < size(); i++) {
        max = std::max(max, std::abs(signalValues[i] - other.signalValues[i]));

    }
    return max;
}

bool Signal::empty() const {
    return size() == 0;
}

void Signal::push_back(double value, double time) {
    signalValues.push_back(value);
    timeValues.push_back(time);

}

void Signal::resize(size_t newSize) {
    signalValues.resize(newSize);
    timeValues.resize(newSize);

}

void Signal::setValues(const std::vector<double> &sigVals, const std::vector<double> &timeVals) {
    signalValues = sigVals;
    timeValues = timeVals;
}

const std::vector<double> &Signal::getTimeValues() const {
    return timeValues;
}

const std::vector<double> &Signal::getSignalValues() const {
    return signalValues;
}
