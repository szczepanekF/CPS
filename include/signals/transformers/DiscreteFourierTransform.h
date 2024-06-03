
#pragma once

#include "ComplexTransform.h"

class DiscreteFourierTransform : public ComplexTransform {
public:
    std::vector<std::complex<double>> transform(std::vector<std::complex<double>> x) const  override;

};
