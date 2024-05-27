
#include "signals/transformers/ComplexTransform.h"
#include <complex>

std::vector<std::complex<double>> ComplexTransform::transformFromReal(std::vector<double> x) const {
    std::vector<std::complex<double>> values(x.size());
    for (int i = 0; i < (int) x.size(); i++) {
        values[i] = {x[i], 0};
    }
    return transform(values);
}
