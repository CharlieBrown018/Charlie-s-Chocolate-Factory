cmake_minimum_required(VERSION 3.10)

project(ChocolateShopPOS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(src)

# Add all source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Create executable
add_executable(ChocolateShopPOS ${SOURCES})

# Copy inventory.txt to build directory
configure_file(${CMAKE_SOURCE_DIR}/data/inventory.txt ${CMAKE_BINARY_DIR}/data/inventory.txt COPYONLY)