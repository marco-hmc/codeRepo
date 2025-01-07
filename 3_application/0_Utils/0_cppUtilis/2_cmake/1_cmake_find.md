## CMake 外部库管理和使用

### 1. find_package

```cmake
find_package(<PackageName> [version] [REQUIRED] [COMPONENTS components...])
```
- `<PackageName>`：要查找的包的名称。
- `[version]`：可选，指定所需的包版本。
- `[REQUIRED]`：可选，如果指定，找不到包时会导致配置失败。
- `[COMPONENTS components...]`：可选，指定要查找的包组件。

`find_package` 命令用于查找和加载外部库或包。它的本质是在模块路径下查找名为 `Find<PackageName>.cmake` 的脚本文件，并执行该脚本文件。

* **变量设置**
这个脚本文件通常会设置一些变量，以便在后续的构建过程中使用。
- `<PackageName>_FOUND`：指示是否找到指定的包。
- `<PackageName>_LIBRARIES`：指定包的库文件路径。
- `<PackageName>_INCLUDE_DIRS`：指定包的头文件路径。
基于这些变量去设置库文件路径和头文件即可。

    ```cmake
    target_include_directories(my_executable PRIVATE ${MyCustomLib_INCLUDE_DIRS})
    target_link_libraries(my_executable PRIVATE ${MyCustomLib_LIBRARIES})
    ```

* **别名和导入机制**
新的 `Find<PackageName>.cmake` 脚本文件通常会提供别名和导入机制：

- **别名（Alias）**：可以重命名生成对象目标的名字，使引用目标更加直观和一致。
- **导入机制（Imported Targets）**：将指定库的 `include_directories` 和 `link_directories` 结合起来，具体表现为库的生成对象添加一个 `IMPORTED` 关键词，并设置导入属性（如 `INTERFACE_INCLUDE_DIRECTORIES` 和 `IMPORTED_LOCATION`）。

* **查找.cmake文件路径**
`find_package` 命令会在以下位置查找包：
   1. **CMake 模块路径**：CMake 自带的模块路径，通常位于 CMake 安装目录下的 `Modules` 目录。
   2. **用户定义的模块路径**：可以通过设置 `CMAKE_MODULE_PATH` 变量来指定额外的模块路径。

### 2. 例子
自己的CMakeLists.txt需要声明使用boost库
    ```cmake
    # CMakeLists.txt
    cmake_minimum_required(VERSION 3.10)
    project(MyProject)

    find_package(Boost 1.70 REQUIRED COMPONENTS filesystem system) # 查找 Boost 库
    add_executable(my_executable main.cpp) # 添加可执行文件
    target_link_libraries(my_executable PRIVATE Boost::filesystem Boost::system) # 链接 Boost 库到可执行文件
    ```

那么在cmake安装目录的modules目录下，一般会有一个FindBoost.cmake脚本文件。这个脚本文件会有这些
    ```cmake
    # FindBoost.cmake

    # 查找 Boost 库文件
    find_library(Boost_FILESYSTEM_LIBRARY NAMES boost_filesystem)

    # 查找 Boost 头文件路径
    find_path(Boost_INCLUDE_DIR boost/filesystem.hpp)

    # 定义导入目标
    add_library(Boost::filesystem SHARED IMPORTED)
    set_target_properties(Boost::filesystem PROPERTIES
        IMPORTED_LOCATION ${Boost_FILESYSTEM_LIBRARY}
        INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
    )
    ```

CMakeLists.txt.in有什么用