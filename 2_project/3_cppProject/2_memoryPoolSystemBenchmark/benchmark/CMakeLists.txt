file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*_test.cpp)

add_executable(bc_test ${SOURCES} benchmark.cpp)

target_include_directories(bc_test PRIVATE ${CMAKE_SOURCE_DIR})