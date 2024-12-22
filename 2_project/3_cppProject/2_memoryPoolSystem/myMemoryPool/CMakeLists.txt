cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME "myNewProject")

project(${PROJECT_NAME})

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)

# add the executable
add_executable(${PROJECT_NAME} main.cpp)

# specify include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)