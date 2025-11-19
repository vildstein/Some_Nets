cmake_minimum_required(VERSION 2.8.11...3.22)
set(PROJECT_NAME "StevensDateTime")

project(${PROJECT_NAME} C)
message(STATUS "PROJECT_NAME =  ${PROJECT_NAME}")
message(STATUS "CMAKE_SYSTEM_NAME = ${CMAKE_SYSTEM_NAME}")

set(CMAKE_C_STANDARD 11)
add_executable("${PROJECT_NAME}Client"
        client.c
        include.h)

add_executable("${PROJECT_NAME}Server"
        server.c
        include.h)

#if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
#    target_compile_definitions(${PROJECT_NAME} PRIVATE OS_DEFINED_CMAKE_LIN)
#    message(STATUS "LINUX DEFINED")
#else ()
#    target_compile_definitions(${PROJECT_NAME} PRIVATE OS_DEFINED_CMAKE_WIN)
#    target_link_libraries(${PROJECT_NAME} PRIVATE ws2_32)
#    message(STATUS "DEFINED NOT LINUX")
#endif()
