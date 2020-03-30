cmake_minimum_required(VERSION 3.10)

set(exe_test "container.test")

add_executable(${exe_test} 
    disjoint_sets.test.cpp
)

target_link_libraries(
    ${exe_test}
    mc_container
)

add_test(NAME ${exe_test} COMMAND ${exe_test})
