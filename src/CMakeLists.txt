cmake_minimum_required(VERSION 3.5.1)
project(realworld-c-civetweb)

set(TARGET_NAME ${PROJECT_NAME})

find_package(civetweb REQUIRED)

include_directories(${civetweb_INCLUDE_DIR})

add_executable(${TARGET_NAME} main.c)
target_link_libraries(${TARGET_NAME} ${civetweb_LIBRARY})

install(TARGETS ${TARGET_NAME} DESTINATION bin)
