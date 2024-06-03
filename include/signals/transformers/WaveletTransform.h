
#pragma once

#include "RealTransform.h"

enum TransformOrder {
    DB4,
    DB6,
    DB8
};

class WaveletTransform : public RealTransform {
public:

    explicit WaveletTransform(TransformOrder order);

    std::vector<double> transform(std::vector<double> x) const override;

private:
    std::vector<double> waveletTransform(std::vector<double> x, std::vector<double> h) const;
    const std::vector<double> DB4;
    const std::vector<double> DB6;
    const std::vector<double> DB8;
    const TransformOrder order;
};
