file(GLOB_RECURSE files RELATIVE ${CMAKE_CURRENT_LIST_DIR} *.c[p]*)

add_executable(SegfaultsOfTheCaribbean
    ${files}
)
target_include_directories(SegfaultsOfTheCaribbean PUBLIC ../include)

target_compile_features(SegfaultsOfTheCaribbean PUBLIC cxx_std_17)
