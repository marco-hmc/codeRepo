cmake_minimum_required(VERSION 3.10)

# set the project name
project(myThreadPool)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)

# add the executable
add_executable(myThreadPool main.cpp)

# specify include directories
target_include_directories(myThreadPool PRIVATE ${PROJECT_SOURCE_DIR}/include)