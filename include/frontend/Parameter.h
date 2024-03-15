#include <string>

class Parameter {
public:
    std::string name;
    double value;
    double isVisible;

    Parameter(const std::string &name);
    double val();
};
