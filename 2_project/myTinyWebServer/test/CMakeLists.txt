enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(runTests test_server.cpp)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)
target_link_libraries(runTests gtest gtest_main)

add_test(NAME ServerHttpTest COMMAND runTests)