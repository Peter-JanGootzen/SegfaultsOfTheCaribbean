#include "view_controllers/cli_view_controller.hpp"
#include <iostream>

void CliViewController::WriteOutput(String s) const {
    std::cout << s << std::endl;
}