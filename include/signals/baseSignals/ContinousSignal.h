#pragma once

#include "SignalStrategy.h"

class ContinousSignal : public SignalStrategy {
public:
    ContinousSignal(double time0, double dur);

    Signal &getSignal() override;

};
