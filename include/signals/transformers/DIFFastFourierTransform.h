
#pragma once

#include "DITFastFourierTransform.h"
class DIFFastFourierTransform : public DITFastFourierTransform{
public:
    std::vector<std::complex<double>> transform(std::vector<std::complex<double>> x) const override;

};
