file(GLOB_RECURSE files RELATIVE ${CMAKE_CURRENT_LIST_DIR} *.c[p]*)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

## Compiler options
# Make the compiler complain, a lot
# Force colors when using ninja
add_compile_options(-fcolor-diagnostics)
# Turn on the address sanitizer for safety checks
option(SANITIZER "Turn on the address sanitizer" OFF)
if(SANITIZER)
    add_compile_options(-fsanitize=address -fno-omit-frame-pointer -O1)
    add_link_options(-fsanitize=address)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_executable(SegfaultsOfTheCaribbean
    ${files}
)
target_include_directories(SegfaultsOfTheCaribbean PUBLIC ../include)
target_compile_features(SegfaultsOfTheCaribbean PUBLIC cxx_std_17)