# FILEPATH: /C:/Users/46599/Documents/1_codeRepo/0_codigRepo/qtRepo/CMakeLists.txt
cmake_minimum_required(VERSION 3.5)

project(hello_headers)

# Find the required Qt packages
find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(SOURCES
    src/Hello.cpp
    src/main.cpp
)

add_executable(hello_headers ${SOURCES})

target_include_directories(hello_headers
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
)

# Link the Qt libraries to the executable
target_link_libraries(hello_headers PRIVATE Qt5::Widgets)
