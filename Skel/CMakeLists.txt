cmake_minimum_required(VERSION 2.8.11...3.20)
set(PROJECT_NAME "Skeletons")

project(${PROJECT_NAME} C)

message(STATUS "PROJECT_NAME =  ${PROJECT_NAME}")
message(STATUS "CMAKE_SYSTEM_NAME = ${CMAKE_SYSTEM_NAME}")

set(CMAKE_C_STANDARD 11)

set(TCP_CLIENT_APP_NAME "${PROJECT_NAME}_TCP_client_skel.exe")
set(TCP_SERVER_APP_NAME "${PROJECT_NAME}_TCP_server_skel.exe")

set(UDP_CLIENT_APP_NAME "${PROJECT_NAME}_UDP_client_skel.exe")
set(UDP_SERVER_APP_NAME "${PROJECT_NAME}_UDP_server_skel.exe")

#message(STATUS "TCP_CLIENT_APP_NAME =  ${CLIENT_APP_NAME}")
#set(exList "${TCP_CLIENT_APP_NAME};${TCP_SERVER_APP_NAME};${UDP_CLIENT_APP_NAME};${UDP_SERVER_APP_NAME}")

set(exList "${TCP_CLIENT_APP_NAME};${TCP_SERVER_APP_NAME}")

foreach (VAR IN LISTS exList ITEMS)
    message(STATUS "VAR_IN_FOREACH =  ${VAR}")
endforeach()

add_executable(${TCP_CLIENT_APP_NAME}
        TCP_client_skel.c
        error_func.c
        set_address_func.c
        skel_defines.h)

add_executable(${TCP_SERVER_APP_NAME}
        TCP_serv_skel.c
        set_address_func.c
        skel_defines.h)

foreach (APP_NAME IN LISTS exList)
    message(STATUS "APP_NAME =  ${APP_NAME}")
    if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
        target_compile_definitions(${APP_NAME} PRIVATE OS_DEFINED_CMAKE_LIN)
        message(STATUS "LINUX DEFINED")
    else ()
        target_compile_definitions(${APP_NAME} PRIVATE OS_DEFINED_CMAKE_WIN)
        target_link_libraries(${PROJECT_NAME} PRIVATE ws2_32)
        message(STATUS "DEFINED NOT LINUX")
    endif()
endforeach()




#if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
#    target_compile_definitions(${CLIENT_APP_NAME} PRIVATE OS_DEFINED_CMAKE_LIN)
#    message(STATUS "LINUX DEFINED")
#else ()
#    target_compile_definitions(${CLIENT_APP_NAME} PRIVATE OS_DEFINED_CMAKE_WIN)
#    target_link_libraries(${PROJECT_NAME} PRIVATE ws2_32)
#    message(STATUS "DEFINED NOT LINUX")
#endif()