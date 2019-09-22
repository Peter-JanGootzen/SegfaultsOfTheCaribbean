file(GLOB_RECURSE files RELATIVE ${CMAKE_CURRENT_LIST_DIR} *.c[p]*)

add_executable(SegfaultsOfTheCaribbean
    ${files}
)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
target_include_directories(SegfaultsOfTheCaribbean PUBLIC ../include)

target_compile_features(SegfaultsOfTheCaribbean PUBLIC cxx_std_17)
