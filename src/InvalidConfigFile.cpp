#include "../headers/InvalidConfigFile.h"

InvalidConfigFile::InvalidConfigFile(const std::string &file)
    : file("Invalid configuration file: " + file) {}

const char *InvalidConfigFile::what() const noexcept {
    return file.c_str();
}
