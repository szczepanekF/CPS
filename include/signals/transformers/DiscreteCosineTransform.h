
#pragma once

#include "RealTransform.h"

class DiscreteCosineTransform : public RealTransform {
public:
    std::vector<double> transform(std::vector<double> x) const  override;

protected:
    static double c(int m, int N) ;
};
