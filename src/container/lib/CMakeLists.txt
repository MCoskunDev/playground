cmake_minimum_required(VERSION 3.10)

set(lib_name "mc_container")

add_library(
    ${lib_name}
    disjoint_set.cpp
)

target_link_libraries(
    ${lib_name}
)

target_include_directories(${lib_name} PUBLIC ../inc)
