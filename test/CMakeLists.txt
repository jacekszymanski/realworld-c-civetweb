cmake_minimum_required(VERSION 3.5.1)
project(realworld-c-civetweb-test)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_BUILD_TYPE Debug)

set(TARGET_NAME ${PROJECT_NAME})

add_subdirectory(../src lib EXCLUDE_FROM_ALL)

add_executable(${TARGET_NAME} test_util.c)
target_link_libraries(${TARGET_NAME} lib_realworld-c-civetweb)
