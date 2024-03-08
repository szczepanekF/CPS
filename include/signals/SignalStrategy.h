#pragma once
#include <vector>

class SignalStrategy {
public:
    SignalStrategy(double amp, double time0, double dur);
    virtual ~SignalStrategy() = default;
    virtual double calculateSignalAt(double time) = 0;
    std::pair<std::vector<double>, std::vector<double>> getSignal();
    double getAmplitude();

private:
    double duration;
    const static int SAMPLE_COUNT = 10;
protected:
    double beginTime;
    double amplitude;
};
