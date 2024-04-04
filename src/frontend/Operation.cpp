#include "frontend/Operation.h"





bool Operation::getIsActive() const {
    return isActive;
}

void Operation::setIsActive(bool isActive) {
    Operation::isActive = isActive;
}

const char *Operation::getName() const {
    return name;
}

void Operation::setName(const char *name) {
    Operation::name = name;
}

Operation::Operation(OPERATION_TYPE type, const char *name) : name(name), isActive(false), type(type) {}




