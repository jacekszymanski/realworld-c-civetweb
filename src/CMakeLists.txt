cmake_minimum_required(VERSION 3.5.1)
project(realworld-c-civetweb)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(TARGET_NAME ${PROJECT_NAME})
set(LIBRARY_NAME lib_${TARGET_NAME})

find_package(civetweb REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${civetweb_INCLUDE_DIR})

FILE(GLOB AppFiles "app/*.c")
FILE(GLOB DbFiles "db/*.c")
FILE(GLOB ModelFiles "openapi/model/*.c")
FILE(GLOB HandlerFiles "handlers/*.c")

add_library(${LIBRARY_NAME} STATIC
   ${AppFiles}
   ${DbFiles}
   ${ModelFiles}
   ${HandlerFiles}

   # FIXME cannot now add /api/ with GLOB as most have compile errors
   openapi/api/UserAndAuthenticationAPI.c
   openapi/api/ProfileAPI.c

   openapi/util/list.c
)

set_target_properties(${LIBRARY_NAME} PROPERTIES OUTPUT_NAME ${TARGET_NAME})

add_executable(${TARGET_NAME}
   main.c
)

target_link_libraries(${TARGET_NAME} ${LIBRARY_NAME})

install(TARGETS ${TARGET_NAME} DESTINATION bin)
