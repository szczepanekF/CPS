#pragma once

#include "vector"

class Signal {


public:
    const std::vector<double> &getTimeValues() const;

    const std::vector<double> &getSignalValues() const;

    Signal operator-(const Signal &s) const;

    Signal operator+(const Signal &s) const;

    Signal operator/(const Signal &s) const;

    Signal operator*(const Signal &s) const;

    double mean() const;

    double absMean() const;

    double variance() const;

    double meanPower() const;

    double rms() const;

    double meanSquaredError(Signal other) const;

    double signalToNoiseRatio(Signal other) const;

    double peakSignalToNoiseRatio(Signal other) const;

    double maxDifference(Signal other) const;

    void push_back(double value, double time);

    size_t size() const;

    bool empty() const;

    void resize(size_t newSize);

    void setValues(const std::vector<double> &sigVals, const std::vector<double> &timeVals);

//    void convertToFloat(float *vals, float *time) const;


private:
    std::vector<double> timeValues;
    std::vector<double> signalValues;
};
