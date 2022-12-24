cmake_minimum_required(VERSION 3.16)
project(OSManager)

set(CMAKE_CXX_STANDARD 14)

set(OS_MANAGER_SRC_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src/include)

include_directories(${OS_MANAGER_SRC_INCLUDE_DIR})

add_executable(OSManager main.cpp src/disk/DiskManager.cpp src/include/DiskManager.h src/catalog/CatalogManager.cpp src/include/CatalogManager.h src/memory/MemoryManager.cpp src/include/MemoryManager.h src/thread/ThreadManager.cpp src/include/ThreadManager.h src/include/define.h src/memory/LRUReplacer.cpp src/include/LRUReplacer.h)
add_subdirectory(src)
