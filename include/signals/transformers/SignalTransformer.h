
#pragma once

#include <memory>
#include "signals/complexSignals/DiscreteComplexSignal.h"
#include "ComplexTransform.h"
#include "RealTransform.h"
#include "signals/signalConversion/ADC/Sampling.h"
#include "signals/baseSignals/DiscreteSignalStatic.h"
#include "WaveletTransform.h"

class SignalTransformer {

public:
    std::unique_ptr<DiscreteComplexSignal> DFT(Sampling& sig);
    std::unique_ptr<DiscreteComplexSignal> DIT_FFT(Sampling& sig);
    std::unique_ptr<DiscreteComplexSignal> DIF_FFT(Sampling& sig);
    std::unique_ptr<DiscreteSignal> DCT(Sampling& sig);
    std::unique_ptr<DiscreteSignal> FCT(Sampling& sig);
    std::unique_ptr<DiscreteSignal> Walsh_Hadamard(Sampling& sig);
    std::unique_ptr<DiscreteSignal> Fast_Walsh_hadamard(Sampling& sig);
    std::unique_ptr<DiscreteSignal> Wavelet(Sampling& sig, TransformOrder order);
private:
    std::unique_ptr<DiscreteComplexSignal> transformToComplexSignal(Sampling& sig, const ComplexTransform& transform);
    std::unique_ptr<DiscreteSignal> transformToRealSignal(Sampling& sig, const RealTransform& transform);
};
