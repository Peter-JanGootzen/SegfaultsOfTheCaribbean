#ifndef FILE_CLI_VIEW_CONTROLLER_HPP
#define FILE_CLI_VIEW_CONTROLLER_HPP
#include "std/string.hpp"

class CliViewController {
public:
    CliViewController() = default;
    ~CliViewController() = default;
    void WriteOutput(String s) const;
};

#endif
