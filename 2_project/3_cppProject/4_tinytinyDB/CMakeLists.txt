cmake_minimum_required(VERSION 3.12)

project(myTinyWebServer)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(Boost 1.74.0 REQUIRED COMPONENTS system)
find_package(spdlog REQUIRED)

# 添加可执行文件
add_executable(${PROJECT_NAME}
    src/main_http.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE Boost::system)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIRS})

# 添加测试目录
add_subdirectory(test)
