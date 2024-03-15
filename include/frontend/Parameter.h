#pragma once
#include <string>

class Parameter {
public:
    std::string name;
    double value;
    bool isVisible;

    Parameter(const std::string &name);

};
