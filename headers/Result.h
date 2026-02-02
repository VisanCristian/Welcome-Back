#ifndef OOP_RESULT_H
#define OOP_RESULT_H

template<typename S, typename E>
class Result {
private:
    S ok;
    E err;
    bool success;

    Result(const S &ok, const E &err, bool success);

public:
    static Result<S, E> OkResult(const S &value);
    static Result<S, E> ErrResult(const E &value);

    [[nodiscard]] bool isOk() const;
    const S &getOk() const;
    const E &getErr() const;
};

template<typename S, typename E>
Result<S, E>::Result(const S &ok, const E &err, bool success) : ok(ok), err(err), success(success) {}

template<typename S, typename E>
Result<S, E> Result<S, E>::OkResult(const S &value) {
    return Result<S, E>(value, E{}, true);
}

template<typename S, typename E>
Result<S, E> Result<S, E>::ErrResult(const E &value) {
    return Result<S, E>(S{}, value, false);
}

template<typename S, typename E>
const S &Result<S, E>::getOk() const {
    return ok;
}

template<typename S, typename E>
const E &Result<S, E>::getErr() const {
    return err;
}

template<typename S, typename E>
bool Result<S, E>::isOk() const {
    return success;
}

#endif
