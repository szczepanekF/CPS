
#pragma once

#include "RealTransform.h"

class FastWalshHadamardTransform : public RealTransform {
public:
    std::vector<double> transform(std::vector<double> x) const override;
};
