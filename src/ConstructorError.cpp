#include "../headers/ConstructorError.h"

ConstructorError::ConstructorError(const std::string &objectName)
    : objectName("Constructor error: " + objectName) {}

const char *ConstructorError::what() const noexcept {
    return objectName.c_str();
}
