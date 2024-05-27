
#pragma once

#include "ComplexTransform.h"

#include <vector>

class DITFastFourierTransform :public ComplexTransform {
public:
    std::vector<std::complex<double>> transform(std::vector<std::complex<double>> x) const  override;

protected:
    int reverseBits(int x, int log2n) const ;
};
