cmake_minimum_required(VERSION 3.12)
project(SegfaultsOfTheCaribbean)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(include)
add_subdirectory(src)
