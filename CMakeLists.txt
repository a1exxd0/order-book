# CMakeLists.txt

# Specify project make details
cmake_minimum_required(VERSION 3.22)
project(order-book)

# Set minimum C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -fopenmp -std=c++23")

# Add more optimization flags for an actual build
# Good idea for debugging steps to use this though!
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -O0 -g")

# Add main directory
add_subdirectory(src)

# Add testing directory
enable_testing()
add_subdirectory(test)