cmake_minimum_required(VERSION 3.16)
project(OSManager)

set(CMAKE_CXX_STANDARD 14)

set(OS_MANAGER_SRC_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src/include)

include_directories(${OS_MANAGER_SRC_INCLUDE_DIR})

add_executable(OSManager main.cpp src/kernel/disk/DiskManager.cpp src/kernel/disk/DiskManager.h src/kernel/catalog/CatalogManager.cpp src/kernel/catalog/CatalogManager.h src/kernel/memory/MemoryManager.cpp src/kernel/memory/MemoryManager.h src/kernel/thread/ThreadManager.cpp src/kernel/thread/ThreadManager.h src/include/define.h src/user/UserManager.cpp src/user/UserManager.h src/include/utils.h)
add_subdirectory(src)
