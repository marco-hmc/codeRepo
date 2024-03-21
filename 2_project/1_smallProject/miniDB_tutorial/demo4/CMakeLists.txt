# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.5)

# Set the project name
project (demo4)

set(SOURCES
    src/common.c
    src/complier.c
    src/vm.c
    src/data.c
    src/main.c
)

set(TESTSOURCES
    test/common.c
    test/complier.c
    test/vm.c
    test/data.c
    test/function_test.c
)
# Add an executable
add_executable(${PROJECT_NAME} ${SOURCES})

add_executable(TEST ${TESTSOURCES})

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

target_include_directories(TEST
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)