
#include "signals/transformers/DiscreteCosineTransform.h"
#include <cmath>
std::vector<double> DiscreteCosineTransform::transform(std::vector<double> x) const {
    int N = x.size();
    std::vector<double> vals(N);
    for (int m = 0; m < N; m++) {
        double sum = 0.0;
        for (int n = 0; n < N; n++) {
            sum += x[n] * cos(M_PI * (2.0 * n + 1) * m / (2.0 * N));
        }
        vals[m] = c(m, N) * sum;
    }
    return vals;
}

double DiscreteCosineTransform::c(int m, int N) const {
    if (m == 0) {
        return std::sqrt(1.0 / N);
    }
    return std::sqrt(2.0 / N);
}
