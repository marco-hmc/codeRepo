# 设置CMake的最小版本要求
cmake_minimum_required(VERSION 3.10)

# 设置项目名称
project(SingleFileProject)

# 设置C标准
set(CMAKE_C_STANDARD 11)

# 指定编译器
set(CMAKE_C_COMPILER gcc)

# 添加可执行文件
add_executable(SingleFileProject src/part1.c)