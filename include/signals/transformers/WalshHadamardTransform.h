
#pragma once

#include "RealTransform.h"

class WalshHadamardTransform : public RealTransform {
public:
    std::vector<double> transform(std::vector<double> x) const override;

private:
    void fillWalshHadamardMatrix(std::vector<std::vector<double>> &H, int m) const;
};
