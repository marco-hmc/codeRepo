cmake_minimum_required(VERSION 3.10)

# 设置项目名称
project(myThreadPool)

# 指定 C++ 标准
set(CMAKE_CXX_STANDARD 17)

# 查找 src 目录中的所有源文件
file(GLOB_RECURSE SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

# 添加可执行文件
add_executable(myThreadPool main.cpp ${SOURCES})

# 指定头文件目录
target_include_directories(myThreadPool PRIVATE ${PROJECT_SOURCE_DIR}/include)