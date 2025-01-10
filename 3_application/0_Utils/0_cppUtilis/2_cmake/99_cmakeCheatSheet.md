
- **CMAKE_SOURCE_DIR**
  顶级`CMakeLists.txt`所在目录。
- **CMAKE_CURRENT_SOURCE_DIR**
  当前`CMakeLists.txt`所在目录。多用于子目录的情况
- **PROJECT_SOURCE_DIR**
  最近的定义`project()`的那个`CMakeLists.txt`所在的目录。
- **CMAKE_BINARY_DIR**
  根的二进制/构建目录，即运行 cmake 命令的目录
- **CMAKE_CURRENT_BINARY_DIR**
  在根目录下的当前构建目录。
- **PROJECT_BINARY_DIR**
  当前项目的构建目录。
- `cmake_prefix_path`
  用于告诉 CMake 去哪里查找一些外部的项目、库或者工具链等相关文件。
- `cmake_library_path`



### 3. 常用的变量

#### 3.1 与源文件和目录相关的变量

- **${CMAKE_CURRENT_SOURCE_DIR}**：
  表示当前处理的 CMakeLists.txt 文件所在的源文件目录。比如在项目的某个子目录下的 CMakeLists.txt 中使用它，就指向该子目录的路径，方便用来指定源文件、头文件等相对于这个目录的位置，像 `add_executable(myapp ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)` 这样去组织构建可执行文件相关的源文件。
- **${CMAKE_CURRENT_BINARY_DIR}**：
  对应于当前 CMakeLists.txt 文件对应的构建目录，也就是编译生成目标文件、中间文件等所在的目录。例如在生成自定义的构建脚本等场景下，可以用它来指定输出路径，像 `configure_file(config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)` ，会根据配置模板文件生成对应的配置头文件到构建目录下。
- **${CMAKE_SOURCE_DIR}**：
  整个项目最顶层的源文件目录，是所有源文件目录的根目录，对于定位项目中全局的一些公共源文件、资源文件等非常有用，例如在多子目录项目中，顶层 CMakeLists.txt 可以用它来指定一些共享的头文件查找路径，通过 `include_directories(${CMAKE_SOURCE_DIR}/include)` 让各个子目录的编译单元都能找到公共头文件。
- **${CMAKE_BINARY_DIR}**：
  整个项目的构建根目录，所有的构建产物最终都会放置在这个目录或者其下的子目录中，类似构建过程中生成的库文件、可执行文件等都会在这个目录结构下，并且可以利用它来设置一些全局的输出布局，比如 `set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)` 把最终生成的可执行文件统一放到 `bin` 子目录中。

#### 3.2 与编译选项相关的变量

- **${CMAKE_C_FLAGS}**：
  用于设置 C 语言编译器的编译选项，比如可以添加优化级别选项 `-O2` ，调试相关选项 `-g` 等，像 `set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -g")` ，这样在编译 C 语言源文件时就会应用这些指定的编译参数。
- **${CMAKE_CXX_FLAGS}**：
  和上面类似，不过是针对 C++ 语言编译器的编译选项，同样可以添加诸如优化、调试、警告处理等相关的参数，例如 `set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")` 让编译器在编译 C++ 源文件时显示更多的警告信息。

#### 3.3 与目标属性相关的变量

- **${PROJECT_NAME}**：
  代表当前项目的名称，这个名称通常是通过 `project()` 命令在 CMakeLists.txt 中定义的，在后续指定生成的目标文件（如库文件、可执行文件）的名称、安装目录等场景中会经常用到，比如 `add_library(${PROJECT_NAME}_lib mylib.cpp)` ，就会以项目名称结合后缀的形式来命名生成的库文件。
- **${CMAKE_INSTALL_PREFIX}**：
  用于指定项目安装的根目录，当执行 `make install` 命令时，生成的可执行文件、库文件、头文件等会按照设定的安装规则安装到这个指定的目录及其子目录下，例如 `set(CMAKE_INSTALL_PREFIX /usr/local)` ，那么最终的安装产物就会放置到 `/usr/local` 对应的合适位置（可执行文件到 `bin` 目录、库文件到 `lib` 目录等）。

#### 3.4 与查找库相关的变量

- **${CMAKE_FIND_ROOT_PATH}**：
  在跨平台交叉编译或者查找特定路径下的依赖库时很有用，它定义了一个搜索路径的根路径，CMake 会基于这个根路径去查找库文件、头文件等，比如在嵌入式开发中，指定交叉编译工具链对应的系统根目录路径，通过 `set(CMAKE_FIND_ROOT_PATH /path/to/embedded/root)` 来辅助查找相关的库和头文件。

#### 3.5 与构建类型相关的变量

- **${CMAKE_BUILD_TYPE}**：
  表示当前的构建类型，常见的值有 `Debug`、`Release`、`RelWithDebInfo`（发布版本带调试信息）、`MinSizeRel`（最小化大小发布版）等，不同的构建类型会应用不同的编译选项，例如在 `Debug` 类型下会默认开启更多的调试相关的编译参数，方便调试程序，而 `Release` 类型则侧重于优化生成的二进制文件性能和减小文件大小等，可以通过 `set(CMAKE_BUILD_TYPE Release)` 来显式指定构建类型。


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