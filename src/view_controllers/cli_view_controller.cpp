#include <iostream>
#include <cstdio>
#include "view_controllers/cli_view_controller.hpp"
#include "std/string.hpp"
#include "std/unique_array.hpp"

void CliViewController::writeOutput(String s) const {
    std::cout << s << std::endl;
}

String CliViewController::getInput() const {
    unique_array<char> buffer { new char[1000] };
    std::cin.getline(buffer.get(), 1000);
    String input { String(buffer.get()) };
    return input;
}