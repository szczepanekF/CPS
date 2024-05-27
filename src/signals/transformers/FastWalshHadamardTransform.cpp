
#include "signals/transformers/FastWalshHadamardTransform.h"

std::vector<double> FastWalshHadamardTransform::transform(std::vector<double> x) const {
    int N = x.size();
    for (int step = 1; step < N; step *= 2) {
        for (int i = 0; i < N; i += 2 * step) {
            for (int j = 0; j < step; ++j) {
                double u = x[i + j];
                double v = x[i + j + step];
                x[i + j] = u + v;
                x[i + j + step] = u - v;
            }
        }
    }
    return x;
}
