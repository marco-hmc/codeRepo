cmake_minimum_required(VERSION 3.5)
project(helloWorld VERSION 0.1.0 LANGUAGES C CXX)

include_directories(
    include
)

# project(your_project_name)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find the QtWidgets library
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

add_executable(helloWorld main.cpp)

# Link the Qt libraries to the target
target_link_libraries(helloWorld Qt5::Core Qt5::Gui Qt5::Widgets)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)