
#include "signals/transformers/DiscreteFourierTransform.h"

std::vector<std::complex<double>> DiscreteFourierTransform::transform(std::vector<std::complex<double>> x) const {
    int N = x.size();

    std::complex<double> W = std::polar(1.0, 2.0 * M_PI / N);

    std::vector<std::complex<double>> X(x.size());

    for (int m = 0; m < N; m++) {
        std::complex<double> sum = {0, 0};
        for (int n = 0; n < N; n++) {
            sum += x[n] * std::pow(W, (-m * n));
        }
        X[m] = sum / static_cast<double>(N);
    }

    return X;
}
