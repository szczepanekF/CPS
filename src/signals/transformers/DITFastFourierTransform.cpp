
#include <iostream>
#include <cmath>
#include <complex>
#include "signals/transformers/DITFastFourierTransform.h"

std::vector<std::complex<double>> DITFastFourierTransform::transform(std::vector<std::complex<double>> x) const {
    int N = x.size();
    int log2n = std::log2(N);
    for (int i = 0; i < N; i++) {
        int newBit = reverseBits(i, log2n);
        if (i < newBit) {
            std::swap(x[newBit], x[i]);
        }
    }

    for (int s = 1; s <= log2n; s++) {
        int m = 1 << s;
        std::complex<double> wm = std::polar(1.0, -2 * M_PI / m);

        for (int k = 0; k < N; k += m) {
            std::complex<double> w = 1.0;
            for (int j = 0; j < m / 2; j++) {
                std::complex<double> t = w * x[k + j + m / 2];
                std::complex<double> u = x[k + j];
                x[k + j] = u + t;
                x[k + j + m / 2] = u - t;
                w *= wm;
            }
        }
    }

    return x;
}

int DITFastFourierTransform::reverseBits(int x, int log2n) const {
    int n = 0;
    for (int i = 0; i < log2n; i++) {
        n <<= 1;
        n |= (x & 1);
        x >>= 1;
    }

    return n;
}
