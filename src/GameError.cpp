#include "headers/GameError.h"

GameError::GameError(const std::string &msg) : message(msg) {}

const char *GameError::what() const noexcept {
    return message.c_str();
}
