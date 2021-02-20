cmake_minimum_required(VERSION 3.18)

if(${HAPPY_BUILD_PICO})
    include(pico_sdk_import.cmake)
endif()

project(happy C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(HAPPY_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
option(HAPPY_BUILD_TESTS "build unit tests"                ON)
option(HAPPY_RUN_TESTS   "run unit tests as part of build" ON)

if(${HAPPY_BUILD_PICO})
    pico_sdk_init()
    add_subdirectory(pico)
else()
    if(${HAPPY_BUILD_TESTS})
        add_subdirectory(extern/spdlog)
        add_subdirectory(extern/googletest)
        add_subdirectory(test)
    endif()
endif()

add_subdirectory(lib)

