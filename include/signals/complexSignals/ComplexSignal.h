
#pragma once


#include "signals/baseSignals/SignalStrategy.h"

enum ComplexSignalValueType {
    REAL,
    IMAGINARY,
    ABSOLUTE,
    ARGUMENT
};

class ComplexSignal : public SignalStrategy {


public:
    ComplexSignal(double time0, double dur);

    ComplexSignalValueType getType() const;

    void setType(ComplexSignalValueType type);

private:
    ComplexSignalValueType type;

};
