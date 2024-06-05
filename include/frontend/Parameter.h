#pragma once
#include <string>

class Parameter {
public:
    std::string name;
    double value;
    bool isVisible;

    explicit Parameter(const std::string &name);

};
