#include "GameErrors.h"
#include <vector>
#include <memory>
#include "Puzzle.h"

GameError::GameError(const std::string &msg) : message(msg) {}
const char *GameError::what() const noexcept {
    return message.c_str();
}

InvalidConfigFile::InvalidConfigFile(const std::string &file)
    : file("Invalid configuration file: " + file) {}
const char *InvalidConfigFile::what() const noexcept {
    return file.c_str();
}

ConstructorError::ConstructorError(const std::string &ObjectName)
    : ObjectName("Constructor error: " + ObjectName) {}
const char *ConstructorError::what() const noexcept {
    return ObjectName.c_str();
}

InternalError::InternalError(const std::string &functionCall)
    : functionCall("Internal error: " + functionCall) {}
const char *InternalError::what() const noexcept {
    return functionCall.c_str();
}

template<typename S, typename E>
Result<S, E>::Result(const S &ok, const E &err, bool success) : Ok(ok), Err(err), success(success) {}

template<typename S, typename E>
Result<S, E> Result<S, E>::OkResult (const S &value) {
    return Result<S, E>(value, E{}, true);
}

template<typename S, typename E>
Result<S, E> Result<S, E>::ErrResult (const E &value) {
    return Result<S, E>(S{}, value, false);
}

template<typename S, typename E>
const S &Result<S, E>::getOk() const {
    return Ok;
}

template<typename S, typename E>
const E &Result<S, E>::getErr() const {
    return Err;
}

template<typename S, typename E>
bool Result<S, E>::isOk() const {
    return success;
}

template class Result<std::string, GameError>;
template class Result<bool, GameError>;
template class Result<bool, ConstructorError>;
template class Result<std::vector<std::shared_ptr<Puzzle>>, ConstructorError>;
