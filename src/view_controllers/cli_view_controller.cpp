#include <iostream>
#include <cstdio>
#include "view_controllers/cli_view_controller.hpp"
#include "std/string.hpp"

void CliViewController::writeOutput(String s) const {
    std::cout << s << std::endl;
}

String CliViewController::getInput() const {
    char buffer[1000];
    std::cin.getline(buffer, 1000);
    return String(buffer);
}