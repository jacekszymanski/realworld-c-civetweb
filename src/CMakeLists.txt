cmake_minimum_required(VERSION 3.5.1)
project(realworld-c-civetweb)

set(TARGET_NAME ${PROJECT_NAME})
set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(civetweb REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${civetweb_INCLUDE_DIR})

FILE(GLOB AppFiles "app/*.c")
FILE(GLOB DbFiles "db/*.c")
FILE(GLOB ModelFiles "openapi/model/*.c")
FILE(GLOB HandlerFiles "handlers/*.c")

add_executable(${TARGET_NAME}
   ${AppFiles}
   ${DbFiles}
   ${ModelFiles}
   ${HandlerFiles}

   # FIXME cannot now add /api/ with GLOB as most have compile errors
   openapi/api/UserAndAuthenticationAPI.c
   openapi/api/ProfileAPI.c

   openapi/util/list.c
)

install(TARGETS ${TARGET_NAME} DESTINATION bin)
