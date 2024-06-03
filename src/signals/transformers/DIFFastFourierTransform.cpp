#include <cmath>
#include <complex>
#include "signals/transformers/DIFFastFourierTransform.h"

std::vector<std::complex<double>> DIFFastFourierTransform::transform(std::vector<std::complex<double>> x) const {
    int N = x.size();
    int log2n = log2(N);

    for (int s = log2n; s >= 1; s--) {
        int m = 1 << s;
        std::complex<double> wm = std::polar(1.0, -2 * M_PI / m);

        for (int k = 0; k < N; k += m) {
            std::complex<double> w = 1.0;
            for (int j = 0; j < m / 2; j++) {
                std::complex<double> t = x[k + j + m / 2];
                std::complex<double> u = x[k + j];
                x[k + j] = u + t;
                x[k + j + m / 2] = (u - t) * w;
                w *= wm;
            }
        }
    }
    for (int i = 0; i < N; i++) {
        int newBit = reverseBits(i, log2n);
        if (i < newBit) {
            std::swap(x[newBit], x[i]);
        }
    }
    return x;
}

