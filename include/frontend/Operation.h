#include <string>
#include "OperationTypes.h"

class Operation {

public:
    explicit Operation(OPERATION_TYPE type, const char *name, std::string mode);

    const char *getName() const;

    void setName(const char *name);

    bool getIsActive() const;

    void setIsActive(bool isActive);

    const std::string &getMode() const;

private:
    const char* name;
    bool isActive;
    OPERATION_TYPE type;
    std::string mode;
};


