#ifndef OOP_INVALIDCONFIGFILE_H
#define OOP_INVALIDCONFIGFILE_H

#include <exception>
#include <string>

class InvalidConfigFile : public std::exception {
private:
    std::string file;

public:
    explicit InvalidConfigFile(const std::string &file);
    const char *what() const noexcept override;
};

#endif
