cmake_minimum_required(VERSION 3.10)

project(tmpProject VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include directories
include_directories(include)

# Find all source files
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.cxx" "src/*.cc" "src/*.c")

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES})
