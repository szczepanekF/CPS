
#include <iostream>
#include <algorithm>
#include <chrono>
#include "signals/transformers/SignalTransformer.h"
#include "signals/transformers/DITFastFourierTransform.h"
#include "signals/transformers/DIFFastFourierTransform.h"
#include "signals/transformers/DiscreteCosineTransform.h"
#include "signals/transformers/DiscreteFourierTransform.h"
#include "signals/transformers/FastCosineTransform.h"
#include "signals/transformers/FastWalshHadamardTransform.h"
#include "signals/transformers/WalshHadamardTransform.h"
#include "signals/transformers/WaveletTransform.h"
#include "signals/complexSignals/DiscreteComplexSignalStatic.h"
#include "signals/baseSignals/DiscreteSignalStatic.h"

std::unique_ptr<DiscreteComplexSignal> SignalTransformer::DFT(Sampling &sig) {
    DiscreteFourierTransform dft;
    return transformToComplexSignal(sig, dft);
}

std::unique_ptr<DiscreteComplexSignal> SignalTransformer::DIT_FFT(Sampling &sig) {
    DITFastFourierTransform ditfft;
    return transformToComplexSignal(sig, ditfft);
}

std::unique_ptr<DiscreteComplexSignal> SignalTransformer::DIF_FFT(Sampling &sig) {
    DIFFastFourierTransform diffft;
    return transformToComplexSignal(sig, diffft);
}

std::unique_ptr<DiscreteSignal> SignalTransformer::DCT(Sampling &sig) {
    DiscreteCosineTransform dct;
    return transformToRealSignal(sig, dct);
}

std::unique_ptr<DiscreteSignal> SignalTransformer::FCT(Sampling &sig) {
    FastCosineTransform fct;
    return transformToRealSignal(sig, fct);
}

std::unique_ptr<DiscreteSignal> SignalTransformer::Walsh_Hadamard(Sampling &sig) {
    WalshHadamardTransform wht;
    return transformToRealSignal(sig, wht);
}

std::unique_ptr<DiscreteSignal> SignalTransformer::Fast_Walsh_hadamard(Sampling &sig) {
    FastWalshHadamardTransform fwht;
    return transformToRealSignal(sig, fwht);
}

std::unique_ptr<DiscreteSignal> SignalTransformer::Wavelet(Sampling &sig, TransformOrder order) {
    WaveletTransform wave(order);
    return transformToRealSignal(sig, wave);
}

std::unique_ptr<DiscreteComplexSignal>
SignalTransformer::transformToComplexSignal(Sampling &sig, const ComplexTransform &complexTransform) {
    std::vector<double> x = sig.getSignal().getSignalValues();
    std::vector<std::complex<double>> signal(x.size());
    std::ranges::transform(x, std::back_inserter(signal),
                           [](double val) { return std::complex<double>(val, 0.0); });
    std::cout << "START\n";
    auto start = std::chrono::system_clock::now();
    std::vector<std::complex<double>> transformedValues = complexTransform.transform(signal);
    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "elapsed: " << elapsed.count();
    return std::make_unique<DiscreteComplexSignalStatic>(transformedValues, sig.getFrequency());
}

std::unique_ptr<DiscreteSignal>
SignalTransformer::transformToRealSignal(Sampling &sig, const RealTransform &realTransform) {
    std::vector<double> signal = sig.getSignal().getSignalValues();
    std::cout << "START\n";
    auto start = std::chrono::system_clock::now();
    std::vector<double> transformedValues = realTransform.transform(signal);
    auto end = std::chrono::system_clock::now();
    auto elapsed =end - start;

    std::cout << "elapsed nanos?: " << elapsed.count() << "\n";
    return std::make_unique<DiscreteSignalStatic>(transformedValues, sig.getFrequency());
}
