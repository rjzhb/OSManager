cmake_minimum_required(VERSION 3.16)
project(OSManager)

set(CMAKE_CXX_STANDARD 14)

set(OS_MANAGER_SRC_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src/include)

include_directories(${OS_MANAGER_SRC_INCLUDE_DIR})

add_executable(OSManager main.cpp)
add_subdirectory(src)
