#include "signals/Signal.h"
#include <cmath>
#include <iostream>

Signal Signal::operator-(const Signal &s) const {
    Signal ret;
    ret.timeValues = this->timeValues;
    ret.signalValues = std::vector<double>(this->signalValues.size());
    for(size_t i = 0; i < signalValues.size(); i++) {
        ret.signalValues[i] = this->signalValues[i] - s.signalValues[i];
    }
    return ret;
}


Signal Signal::operator+(const Signal &s) const {
    Signal ret;
    ret.timeValues = this->timeValues;
    ret.signalValues = std::vector<double>(this->signalValues.size());
    for(size_t i = 0; i < signalValues.size(); i++) {
        ret.signalValues[i] = this->signalValues[i] + s.signalValues[i];
    }
    return ret;
}

Signal Signal::operator/(const Signal &s) const {
    Signal ret;
    ret.timeValues = this->timeValues;
    ret.signalValues = std::vector<double>(this->signalValues.size());
    for(size_t i = 0; i < signalValues.size(); i++) {
        if (s.signalValues[i] == 0) continue;
        ret.signalValues[i] = this->signalValues[i] / s.signalValues[i];
    }
    return ret;
}


Signal Signal::operator*(const Signal &s) const {
    Signal ret;
    ret.timeValues = this->timeValues;
    ret.signalValues = std::vector<double>(this->signalValues.size());
    for(size_t i = 0; i < signalValues.size(); i++) {
        ret.signalValues[i] = this->signalValues[i] * s.signalValues[i];
    }
    return ret;
}

double Signal::mean() const {
    double sum = 0;
    for(auto val : signalValues) {
        sum += val;
    }
    return sum / signalValues.size();
}

double Signal::absMean() const {
    double sum = 0;
    for(auto val : signalValues) {
        sum += std::abs(val);
    }
    return sum / signalValues.size();
}

double Signal::variance() const {
    double meanVal = mean();
    double sum = 0;
    for(auto val : signalValues) {
        sum += std::pow(val - meanVal, 2);
    }
    return sum / signalValues.size();
}

double Signal::meanPower() const {
    double sum = 0;
    for(auto val : signalValues) {
        sum += std::pow(val, 2);
    }
    return sum / signalValues.size();
}

double Signal::rms() const {
    return std::sqrt(meanPower());
}

size_t Signal::size() const {
    return signalValues.size();
}

void Signal::convertToFloat(float *vals, float *time) const {
    for (size_t i = 0; i < size(); i++) {
        vals[i] = signalValues[i];
        time[i] = timeValues[i];
    }
}
