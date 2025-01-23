cmake_minimum_required(version 3.20)

project(project)

## compile options
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

## flags
set(_Flag_Test ON)
set(_Flag_Memory_Leak ON)

## link-stage
file(GLOB SOURCES "src/*.cpp")

## generate-stage
add_executable(${PROJECT_NAME} ${SOURCES})

## 
if(_Flag_Memory_Leak)
    add_compile_options(-fsanitize=address -fno-omit-frame-pointer)
    add_link_options(-fsanitize=address)
endif()

if(_Flag_Test)
    include(ctest)
    enable_testing()
    add_subdirectory(test)
endif()