#ifndef FILE_CLI_VIEW_CONTROLLER_HPP
#define FILE_CLI_VIEW_CONTROLLER_HPP
#include "std/string.hpp"

class CliViewController {
public:
    CliViewController() = default;
    ~CliViewController() = default;
    void writeOutput(String s) const;
    String getInput() const;
};

#endif
