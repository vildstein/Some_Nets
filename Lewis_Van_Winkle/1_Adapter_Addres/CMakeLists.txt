cmake_minimum_required(VERSION 3.31)
project(adapters C)

set(CMAKE_C_STANDARD 11)

add_executable(adapters main.c)
target_link_libraries(adapters PRIVATE ws2_32 iphlpapi)
