cmake_minimum_required(VERSION 3.5.1)
project(realworld-c-civetweb-test)

set(TARGET_NAME ${PROJECT_NAME})

add_subdirectory(../src realworld-c-civetweb)

add_executable(${TARGET_NAME} test_util.c)
target_include_directories(${TARGET_NAME} PUBLIC ../src)
target_link_libraries(${TARGET_NAME} lib_realworld-c-civetweb)
