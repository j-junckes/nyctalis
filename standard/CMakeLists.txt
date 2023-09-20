cmake_minimum_required(VERSION 3.27.4)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
project(standard)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -g -ffreestanding -Wall -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -g -ffreestanding -Wall -Wextra")
add_definitions(-D__is_std)

file(GLOB_RECURSE LIB_SOURCES "src/*.cpp")
file(GLOB_RECURSE LIBK_SOURCES ${LIB_SOURCES})

add_library(std STATIC ${LIB_SOURCES})
set_target_properties(std PROPERTIES COMPILE_FLAGS "-D__is_std")

add_library(stdk STATIC ${LIBK_SOURCES})
set_target_properties(stdk PROPERTIES COMPILE_FLAGS "-D__is_stdk")

target_include_directories(std PUBLIC "include")
target_include_directories(stdk PUBLIC "include" "../veil/include")

