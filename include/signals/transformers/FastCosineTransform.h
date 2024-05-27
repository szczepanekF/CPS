
#pragma once

#include "DiscreteCosineTransform.h"
#include "DITFastFourierTransform.h"
#include "DiscreteFourierTransform.h"

class FastCosineTransform : public DiscreteCosineTransform {

public:
    FastCosineTransform();

    std::vector<double> transform(std::vector<double> x) const override;

private:
    DITFastFourierTransform ditFft;
};
