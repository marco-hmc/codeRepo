cmake_minimum_required(VERSION 3.10)
project(RTTIComparison)

set(CMAKE_CXX_STANDARD 11)

add_executable(RTTIComparison main.cpp rtti.cpp dynamicCast.cpp)
