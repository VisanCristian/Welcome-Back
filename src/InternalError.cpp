#include "../headers/InternalError.h"

InternalError::InternalError(const std::string &functionCall)
    : functionCall("Internal error: " + functionCall) {}

const char *InternalError::what() const noexcept {
    return functionCall.c_str();
}
