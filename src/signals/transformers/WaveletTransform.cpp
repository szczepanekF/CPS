
#include "signals/transformers/WaveletTransform.h"
#include <cmath>
#include <iostream>

std::vector<double> WaveletTransform::transform(std::vector<double> x) const {
    switch (order) {
        case TransformOrder::DB4:
            return waveletTransform(x, DB4);
        case TransformOrder::DB6:
            return waveletTransform(x, DB6);
        case TransformOrder::DB8:
            return waveletTransform(x, DB8);
    }
    return {};
}

std::vector<double> WaveletTransform::waveletTransform(std::vector<double> x, std::vector<double> h) const {
    int N = x.size();
    std::vector<double> X(N);

    for (int i = 0; i < N; i++) {
        double sum = 0.0;
        int begin = (i / 2) * 2;

        for (int j = begin; j < begin + static_cast<int>(h.size()); j++) {
            double factor;
            if (i % 2 == 0) {
                factor = h[j - begin];
            } else {
                factor = h[h.size() - (j - begin) - 1];
                if ((j - begin) % 2 == 1) {
                    factor *= -1;
                }
            }
            sum += (factor * x[j % N]);
        }
        X[i] = sum;
    }

    std::vector<double> mixedX(N);
    int iterator = 0;
    for (int i = 0; i < N; i += 2) {
        mixedX[iterator++] = X[i];
    }
    for (int i = 1; i < N; i += 2) {
        mixedX[iterator++] = X[i];
    }

    return mixedX;
}


WaveletTransform::WaveletTransform(const TransformOrder order)
        : DB4({(1.0 + std::sqrt(3.0)) / (4.0 * std::sqrt(2)),
               (3.0 + std::sqrt(3.0)) / (4.0 * std::sqrt(2)),
               (3.0 - std::sqrt(3.0)) / (4.0 * std::sqrt(2)),
               (1.0 - std::sqrt(3.0)) / (4.0 * std::sqrt(2))}),
          DB6({0.47046721, 1.14111692, 0.650365, -0.19093442, -0.12083221, 0.0498175}),
          DB8({0.32580343, 1.01094572, 0.8922014, -0.03957503, -0.26450717, 0.0436163, 0.0465036, -0.01498699}),
          order(order) {

}


