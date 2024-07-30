cmake_minimum_required(VERSION 3.12)
project(demo_0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

# 指定源文件
file(GLOB SOURCES "src/*.cpp")

# 添加可执行文件
add_executable(${PROJECT_NAME} main.cpp ${SOURCES})

# 添加测试目录
add_subdirectory(test)
