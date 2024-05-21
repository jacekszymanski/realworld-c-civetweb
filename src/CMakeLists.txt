cmake_minimum_required(VERSION 3.5.1)
project(realworld-c-civetweb)

set(TARGET_NAME ${PROJECT_NAME})
set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(civetweb REQUIRED)

include_directories(${civetweb_INCLUDE_DIR})

FILE(GLOB ModelFiles "openapi/model/*.c")
FILE(GLOB HandlerFiles "openapi/handlers/*.c")
add_executable(${TARGET_NAME}
   main.c
   stubs.c
   db.c
   util.c

   openapi/api/UserAndAuthenticationAPI.c
   openapi/api/ProfileAPI.c
   ${ModelFiles}
   ${HandlerFiles}
   openapi/util/list.c
)

install(TARGETS ${TARGET_NAME} DESTINATION bin)
