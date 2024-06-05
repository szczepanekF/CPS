#include <string>
#include "signals/signalConversion/OperationTypes.h"

class Operation {

public:
    explicit Operation(OPERATION_TYPE type, const char *name);

    const char *getName() const;


    bool isOperationActive() const;

    void setIsActive(bool isActive);

    OPERATION_TYPE getType() const;

private:
    const char* name;
    bool isActive;
    OPERATION_TYPE type;

};


