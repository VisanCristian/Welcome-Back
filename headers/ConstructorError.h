#ifndef OOP_CONSTRUCTORERROR_H
#define OOP_CONSTRUCTORERROR_H

#include <exception>
#include <string>

class ConstructorError : public std::exception {
private:
    std::string objectName;

public:
    ConstructorError() = default;
    explicit ConstructorError(const std::string &objectName);
    const char *what() const noexcept override;
};

#endif
