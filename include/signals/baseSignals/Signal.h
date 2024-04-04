#pragma once
#include "vector"

class Signal {

public:
    std::vector<double> timeValues;
    std::vector<double> signalValues;

    Signal operator-(const Signal& s) const;
    Signal operator+(const Signal& s) const;

    Signal operator/(const Signal& s) const;
    Signal operator*(const Signal& s) const;
    double mean() const;
    double absMean() const;
    double variance() const;
    double meanPower() const;
    double rms() const;

    size_t size() const;

    void convertToFloat(float* vals, float* time) const;
};
