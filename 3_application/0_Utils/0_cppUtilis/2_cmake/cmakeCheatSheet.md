以下是一份 CMake 常用的速查表（cheat sheet）内容，涵盖了一些基本且常用的指令和概念：

### 1. 基本项目结构创建
- **创建最小可构建项目**：
```cmake
cmake_minimum_required(VERSION 3.10)  # 指定最低 CMake 版本要求

project(MyProject)  # 定义项目名称

add_executable(MyExecutable main.cpp)  # 添加可执行文件，关联源文件（这里假设主源文件是 main.cpp）
```

### 2. 变量相关
- **定义变量**：
```cmake
set(MY_VARIABLE "value")  # 定义普通变量，这里定义了名为 MY_VARIABLE 的变量，值为 "value"
```
- **使用变量**：
```cmake
add_executable(${MY_VARIABLE}_executable main.cpp)  # 在指令中使用变量，这里会生成名为 value_executable 的可执行文件（假设 MY_VARIABLE 如上述定义）
```

### 3. 源文件添加
- **单个源文件添加（可执行目标）**：
```cmake
add_executable(MyApp main.cpp)  # 为名为 MyApp 的可执行文件添加单个源文件 main.cpp
```
- **多个源文件添加（可执行目标）**：
```cmake
add_executable(MyApp main.cpp util.cpp another.cpp)  # 添加多个源文件到可执行文件 MyApp
```
- **添加源文件到库（静态库示例）**：
```cmake
add_library(MyLib STATIC mylib.cpp helper.cpp)  # 创建名为 MyLib 的静态库，并添加相关源文件
```

### 4. 库的链接
- **链接静态库到可执行文件**：
```cmake
add_executable(MyApp main.cpp)
target_link_libraries(MyApp MyLib)  # 将之前定义的静态库 MyLib 链接到可执行文件 MyApp
```
- **链接动态库到可执行文件（类似方式，只是库类型不同）**：
```cmake
add_library(MySharedLib SHARED sharedlib.cpp)  # 先创建动态库
add_executable(MyApp main.cpp)
target_link_libraries(MyApp MySharedLib)  # 把动态库链接到可执行文件
```

### 5. 头文件路径设置
- **指定单个头文件路径**：
```cmake
include_directories(include)  # 假设头文件在项目的 include 目录下，让编译器能找到头文件
```
- **指定多个头文件路径**：
```cmake
include_directories(include1 include2)  # 为编译器添加多个头文件查找路径
```

### 6. 编译选项设置
- **添加编译定义（类似预处理器定义）**：
```cmake
add_definitions(-DDEBUG)  # 定义 DEBUG 宏，在代码中可通过条件编译使用，例如 #ifdef DEBUG
```
- **设置 C++ 标准**：
```cmake
set(CMAKE_CXX_STANDARD 17)  # 设置 C++ 标准为 C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # 要求必须支持该标准，否则报错
```

### 7. 构建类型选择
- **指定构建类型（Debug、Release 等）**：
```cmake
set(CMAKE_BUILD_TYPE Debug)  # 设置构建类型为 Debug，也可以是 Release、RelWithDebInfo 等
```

### 8. 子目录构建
- **添加子目录构建（假设有子目录 src 包含源文件等）**：
```cmake
add_subdirectory(src)  # 进入 src 子目录执行其中的 CMakeLists.txt 文件来构建该部分内容
```

### 9. 查找外部库
- **查找并使用 Boost 库（示例）**：
```cmake
find_package(Boost REQUIRED COMPONENTS filesystem)  # 查找 Boost 库，要求包含 filesystem 组件
if(Boost_FOUND)
    target_link_libraries(MyApp Boost::filesystem)  # 如果找到，链接到可执行文件 MyApp
endif()
```

### 10. 安装相关
- **安装可执行文件**：
```cmake
install(TARGETS MyApp DESTINATION bin)  # 将可执行文件 MyApp 安装到 bin 目录（安装后的目标目录，实际安装路径依系统等情况而定）
```
- **安装库文件**：
```cmake
install(TARGETS MyLib DESTINATION lib)  # 把库文件安装到 lib 目录
```
- **安装头文件**：
```cmake
install(DIRECTORY include/ DESTINATION include)  # 将项目的 include 目录下的头文件安装到目标系统的 include 目录
```

### 11. 条件判断
- **基于操作系统判断**：
```cmake
if(WIN32)
    # Windows 相关配置，比如添加特定的源文件等
    add_executable(MyApp winmain.cpp main.cpp)
elseif(UNIX)
    # Linux 等 UNIX 系统相关配置
    add_executable(MyApp main.cpp)
endif()
```

这只是 CMake 常用功能的一个简要速查表，CMake 功能强大且灵活，实际项目中还会涉及更多高级用法和配置场景。 