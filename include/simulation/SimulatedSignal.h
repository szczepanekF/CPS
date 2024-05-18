
#pragma once


#include "signals/baseSignals/ContinousSignal.h"
#include "signals/baseSignals/SinusoidalSignal.h"
#include "signals/baseSignals/TriangularSignal.h"

class SimulatedSignal : public ContinousSignal{
public:
    SimulatedSignal(double beginTime, double duration, double period);

    double calculateSignalAt(double time) override;

    void setBeginTime(double beginTime) override;

private:
    SinusoidalSignal sinusoidalSignal;
//    TriangularSignal triangularSignal;
    RectangularSignal triangularSignal;

};
