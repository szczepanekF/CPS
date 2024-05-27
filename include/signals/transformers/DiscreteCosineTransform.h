
#pragma once

#include "RealTransform.h"

class DiscreteCosineTransform : public RealTransform {
public:
    std::vector<double> transform(std::vector<double> x) const  override;

protected:
    double c(int m, int N) const ;
};
