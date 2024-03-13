#pragma once
#include <vector>

struct Signal {
    std::vector<double> timeValues;
    std::vector<double> signalValues;
};

class SignalStrategy {
public:
    SignalStrategy(double amp, double time0, double dur);
    virtual ~SignalStrategy() = default;

    virtual double calculateSignalAt(double time) = 0;
    virtual Signal getSignal() = 0;

    double getAmplitude() const;
    double getBeginTime() const;
    double getDuration() const;

private:
    double duration;
    double beginTime;
    double amplitude;

};
