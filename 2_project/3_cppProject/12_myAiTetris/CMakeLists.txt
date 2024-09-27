cmake_minimum_required(VERSION 3.12)
project(MyAiTetris)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
# 查找Qt库
set(CMAKE_PREFIX_PATH "D:/1_software/Qt/5.14.2/msvc2017_64/lib/cmake/Qt5")
find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

# 添加项目源文件
set(SOURCES
    src/main.cpp
    src/ui/widget.cpp
)

# 添加项目头文件
set(HEADERS
    include/ui/widget.h
)

# 添加测试源文件
set(TEST_SOURCES
    test/test_myTetris.cpp
)

# 处理 .ui 文件
qt5_wrap_ui(UI_HEADERS resources/widget.ui)

# 添加头文件库路径
include_directories(include)

# 添加可执行文件
add_executable(MyAiTetris ${SOURCES} ${HEADERS} ${UI_HEADERS})

# 链接Qt库
target_link_libraries(MyAiTetris Qt5::Core)
target_link_libraries(MyAiTetris Qt5::Widgets)

# 添加测试可执行文件
add_executable(TestMyClass ${TEST_SOURCES} ${SOURCES} ${HEADERS})

# 链接Google Test库
target_link_libraries(TestMyClass gtest gtest_main)

# 添加测试
add_test(NAME MyTestClass COMMAND TestMyClass)