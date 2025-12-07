#ifndef OOP_GAMEERRORS_H
#define OOP_GAMEERRORS_H

#include <exception>
#include <string>

template<typename S, typename E>
class Result {
private:
    S Ok;
    E Err;
    bool success;

    Result(const S &ok, const E &err, bool success);

public:
    static Result<S, E> OkResult(const S &value);
    static Result<S, E> ErrResult(const E &value);

    [[nodiscard]] bool isOk() const;
    const S &getOk() const;
    const E &getErr() const;

};


class GameError : public std::exception {
private:
    std::string message;

public:
    GameError() = default;
    explicit GameError(const std::string &msg);
    const char *what() const noexcept override;
};


class InvalidConfigFile : public std::exception {
private:
    std::string file;
public:
    explicit InvalidConfigFile(const std::string &file);
    const char *what() const noexcept override;
};

class ConstructorError : public std::exception {
private:
    std::string ObjectName;
public:
    ConstructorError() = default;
    explicit ConstructorError(const std::string &ObjectName);
    const char *what() const noexcept override;
};

class InternalError : public std::exception {
private:
    std::string functionCall;
public:
    explicit InternalError(const std::string &functionCall);
    const char *what() const noexcept override;
};

template<typename type>
class Ok {
private:
    type value;
public:
    explicit Ok(const type &value);
    const type& getValue() const;

};





#endif // OOP_GAMEERRORS_H
