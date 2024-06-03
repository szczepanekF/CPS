
#pragma once
#include <complex>
#include <vector>

class ComplexTransform {

public:
    virtual ~ComplexTransform() = default;
    virtual std::vector<std::complex<double>> transform(std::vector<std::complex<double>> x)  const = 0;
    virtual std::vector<std::complex<double>> transformFromReal(std::vector<double> x) const;
};
