cmake_minimum_required(VERSION 3.5.1)
project(realworld-c-civetweb)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(TARGET_NAME ${PROJECT_NAME})
set(LIBRARY_NAME lib_${TARGET_NAME})

# __VA_OPT__ detection
include(CheckSourceRuns)
check_source_runs(C "
#define PP_THIRD_ARG(a,b,c,...) c
#define VA_OPT_SUPPORTED_I(...) PP_THIRD_ARG(__VA_OPT__(,),0,1,)
#define VA_OPT_SUPPORTED VA_OPT_SUPPORTED_I(?)

void main() {
  exit(VA_OPT_SUPPORTED);
}

" HAVE_VA_OPT)

find_package(civetweb REQUIRED)
find_package(cmocka REQUIRED) # TODO fix use only for test builds
find_library(SQLITE3_LIB sqlite3 REQUIRED)
find_library(CJSON_LIB cjson REQUIRED)
find_library(L8W8JWT_LIB l8w8jwt REQUIRED)
find_library(M_LIB m REQUIRED)

list(APPEND PROD_LIBS civetweb::civetweb ${SQLITE3_LIB} ${CJSON_LIB} ${L8W8JWT_LIB} ${M_LIB})

#For now
set(CMAKE_BUILD_TYPE Debug)

string(APPEND CMAKE_C_FLAGS " -DHAVE_VA_OPT=${HAVE_VA_OPT} ")
string(APPEND CMAKE_C_FLAGS_DEBUG " -DLOGLEVEL=5 ")

string(APPEND CMAKE_C_FLAGS " -ffile-prefix-map=${CMAKE_SOURCE_DIR}/=  ")
string(APPEND CMAKE_C_FLAGS " -g -Wall -Wextra -Werror ")
string(APPEND CMAKE_C_FLAGS " -Wno-unused-parameter -Wno-unused-variable ")

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
target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(${TARGET_NAME}
   main.c
)

target_link_libraries(${TARGET_NAME} ${LIBRARY_NAME} ${PROD_LIBS})

install(TARGETS ${TARGET_NAME} DESTINATION bin)
