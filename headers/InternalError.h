#ifndef OOP_INTERNALERROR_H
#define OOP_INTERNALERROR_H

#include <exception>
#include <string>

class InternalError : public std::exception {
private:
    std::string functionCall;

public:
    explicit InternalError(const std::string &functionCall);
    const char *what() const noexcept override;
};

#endif
