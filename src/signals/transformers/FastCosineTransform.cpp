
#include "signals/transformers/FastCosineTransform.h"

FastCosineTransform::FastCosineTransform() : ditFft() {}

std::vector<double> FastCosineTransform::transform(std::vector<double> x) const {
    int N = x.size();
    std::vector<double> y(x.size());
    for (int i = 0; i < N / 2; i++) {
        y[i] = x[2 * i];
        y[N - i - 1] = x[2 * i + 1];

    }
    std::vector<std::complex<double>> fft = ditFft.transformFromReal(y);
    std::complex<double> W = std::polar(1.0, -M_PI / (2.0 * N));
    std::vector<double> X(N);
    for (int m = 0; m < N; m++) {
        X[m] = (fft[m] * std::pow(W, m)).real();
        X[m] *= c(m, N);
    }
    return X;
}
