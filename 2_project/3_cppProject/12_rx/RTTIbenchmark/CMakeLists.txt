file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*_test.cpp)

add_executable(rtti_benchmark_tests ${SOURCES} benchmark.cpp)

target_include_directories(rtti_benchmark_tests PRIVATE ${CMAKE_SOURCE_DIR})