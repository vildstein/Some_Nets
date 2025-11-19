cmake_minimum_required(VERSION 3.31)
project(start_up C)

set(CMAKE_C_STANDARD 11)

add_executable(start_up main.c)
target_link_libraries(start_up PRIVATE ws2_32)
