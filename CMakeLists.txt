cmake_minimum_required(VERSION 3.10)

project(mc)

include(CTest)
enable_testing()

add_compile_options(-std=c++17)

add_subdirectory(src)