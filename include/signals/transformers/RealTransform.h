
#pragma once

#include <vector>

class RealTransform {
public:
    virtual ~RealTransform() = default;

    virtual std::vector<double> transform(std::vector<double> x) const = 0;
};
