#ifndef OOP_GAMEERROR_H
#define OOP_GAMEERROR_H

#include <exception>
#include <string>

class GameError : public std::exception {
private:
    std::string message;

public:
    GameError() = default;
    explicit GameError(const std::string &msg);
    const char *what() const noexcept override;
};

#endif
