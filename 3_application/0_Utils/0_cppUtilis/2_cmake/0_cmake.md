## cmake

### 0. 基本概念

- **什么是构建工具？**
  根据构建文件，调用编译器，连接器完成生成目标对象`target`，生成目标对象`target`可以是静态库、动态库和可执行文件（甚至进一步的，生成对象可以为空，用于表示执行脚本。比如比如 make 工具中的 make clean，资源化，代码检查等等）。

- **构建工具和文件的生态位置**
  - **Make**：Make 是一个构建工具，它根据 Makefile 调用编译器和链接器来构建项目。
  - **Makefile**：Makefile 是 Make 使用的构建文件，用于描述如何构建项目。Make 读取 Makefile，并根据其中定义的规则调用编译器和链接器。

  - **MSBuild**：MSBuild 是 Microsoft 的构建工具，它根据 .vcxproj 文件（Visual C++ 项目文件）和 .csproj 文件（C# 项目文件）调用编译器和链接器来构建项目。
  - **.vcxproj**：.vcxproj 文件是 Visual C++ 项目的项目文件，用于描述如何构建 Visual C++ 项目。MSBuild 读取 .vcxproj 文件，并根据其中定义的规则调用编译器和链接器。

  - **Ninja**：Ninja 是一个高效的构建工具，它根据 build.ninja 文件调用编译器和链接器来构建项目。
  - **build.ninja**：build.ninja 文件是 Ninja 使用的构建文件，用于描述如何构建项目。Ninja 读取 build.ninja 文件，并根据其中定义的规则调用编译器和链接器。

- **生成工具**
  用于生成构建文件的。

  - **CMakeLists.txt**：CMakeLists.txt 是 CMake 使用的配置文件，用于描述项目的构建过程。CMake 读取 CMakeLists.txt 文件，并生成适用于不同构建工具的构建文件，如 Makefile、build.ninja、.vcxproj 等。

- **发展演化的描述**
  我未经考察地做一些发展演化的描述，以便串起这些工具和文件的关系。一开始，构建工具主要是 Make，它使用 Makefile 来描述构建过程。然而，Makefile 的语法和功能有限，针对大型工程非常吃力。于是出现了 CMake，它通过 CMakeLists.txt 文件生成 Makefile。

  与此同时，微软通过 Visual Studio IDE 提供了项目管理功能，允许用户通过 GUI 操作指定哪些文件属于同一个模块，并生成静态库、动态库或可执行文件。相应的数据存储在 `.vcxproj` 文件中。

  CMake 的设计目标是生成构建文件描述，因此它不仅可以生成 Makefile，还可以生成 .vcxproj 文件。CMake 支持.vcxproj 也只是顺手之举。

  后来，Google 推出了 Ninja 构建工具，旨在提高构建效率。其实就是改进 make 的。但是 make 的所有权又不是 Goole 的。便直接另起炉灶了。

- **总结**

  构建文件描述的生成有三种方式：手工写、gui 操作、脚本生成。三种方式都可以，但是脚本生成更灵活，更适合大型工程。CMake 是一个跨平台的构建系统生成工具，可以生成适用于不同构建工具的构建文件。通过理解这些工具和文件在构建生态系统中的位置和作用，可以更好地管理和构建项目。
  因此 cmake 已经成为了 C++构建工具的标准。但是与此同时，cmake 的学习曲线也是很陡的。特别是兼容了很多历史写法，一个功能可以有很多种写法，灵活性很高，但是也容易让人迷失。学习成本也高。


### 1. cmake 脚本语法

* **条件操作**
  - **IF**
    ```cmake
    IF(CONDITION)
      # 条件为真时执行的操作
    ELSE()
      # 条件为假时执行的操作
    ENDIF()
    ```

* **循环操作**
  - **while**
    ```cmake
    WHILE(CONDITION)
      # 循环体，条件为真时执行的操作
    ENDWHILE()
    ```

  - **foreach**
    ```cmake
    FOREACH(item IN LISTS list)
      # 循环体，遍历列表中的每个元素
    ENDFOREACH()
    ```

* **设置变量**
  - **SET**
    ```cmake
    SET(ZS_NAME "${AB}") # 第一种写法
    SET(ZS_NAME ${CD}) # 第二种写法
    set(ENV{MY_ENV_VARIABLE} "Hello!")
    ```

    第一种写法和第二种写法是等价的，都是用来设置变量的值。区别在于第一种写法使用了双引号将变量的值括起来，而第二种写法没有使用双引号。使用双引号可以确保变量的值被视为一个整体，而不会被解释为多个独立的字符串。在这个例子中，由于 `${AB}` 和 `${CD}` 是变量，它们的值将被替换为实际的值，然后赋给 `ZS_NAME` 变量。所以在这种情况下，这两种写法是等效的。

* **宏**
    ```cmake
    macro(MacroName arg1 arg2 ...)
      # 宏的操作和命令
    endmacro()
    ```

    - `macro` 关键字用于定义一个宏。
    - `MacroName` 是宏的名称，可以根据需要自定义。
    - `arg1, arg2, ...` 是宏的参数列表，可以根据需要定义和使用参数。

* **函数**
    ```cmake
    function(FunctionName arg1 arg2 ...)
      # 函数的操作和命令
      # return() 可选，用于返回结果
    endfunction()
    ```

    - `function` 关键字用于定义一个函数。
    - `FunctionName` 是函数的名称，可以根据需要自定义。
    - `arg1, arg2, ...` 是函数的参数列表，可以根据需要定义和使用参数。
    - `return()` 是可选的命令，用于在函数中返回结果。

* **文件操作**
  - **file**
    ```cmake
    file(GLOB SOURCES "src/*.cpp")
    ```

    `file(GLOB ...)` 命令用于查找符合指定模式的文件，并将它们的路径存储在变量中。在这个例子中，`SOURCES` 变量将包含 `src` 目录下所有 `.cpp` 文件的路径。

### 2. 生成

- **如何生目标?**

  ```cmake
  add_library(my_static_lib STATIC source1.cpp) # 定义静态库
  add_library(my_shared_lib SHARED source1.cpp) # 定义动态库
  add_executable(${PROJECT_NAME} main.cpp)
  add_custom_target()
  ```

- **cmake 中的目标是什么意思？**
  目标（Target）是构建系统中的一个基本概念，表示一个可以构建的实体，如可执行文件、库文件。也可以特殊地表示一个自定义命令。

- 如何理解 CMakePredefinedTargets?

  - **`all_build`**
    - **描述**：`all_build` 目标用于构建项目中的所有目标。
    - **用途**：这是默认的构建目标，通常在执行 `make` 或 `cmake --build .` 时被调用。
  - **`install`**
    - **描述**：`install` 目标用于将构建生成的文件安装到指定的安装目录。
    - **用途**：执行安装步骤，将可执行文件、库文件、头文件等复制到预定义的安装路径。
  - **`package`**
    - **描述**：`package` 目标用于创建项目的分发包（如 `.tar.gz`、`.zip`、`.deb`、`.rpm` 等）。
    - **用途**：生成可分发的安装包，便于发布和分发项目。
  - **`zero_check`**
    - **描述**：`zero_check` 目标用于确保生成的构建系统是最新的。
    - **用途**：在每次构建之前检查 CMakeLists.txt 文件和其他配置文件是否有变化，如果有变化，则重新运行 CMake 以更新构建


### 3. 路径指定

- **如何指定路径**

  ```cmake
  # 指定头文件路径
  target_include_directories(TARGET [PRIVATE|PUBLIC|INTERFACE] INCLUDE_DIRECTORY ...)

  # 指令库文件
  target_link_libraries(TARGET [PRIVATE|PUBLIC|INTERFACE] LIBRARY_NAME ...)

  # 指定找库路径
  find_package(LIBRARY_NAME)
  find_library(MYLIBRARY_LIB NAMES mylibrary PATHS /path/to/mylibrary)
  link_directories(/path/to/libDir)
  CMAKE_PREFIX_PATH 变量用于设置库和头文件的搜索路径。通常用于设置多个库和头文件的搜索路径。

  ```

### 4. 安装
CMake 提供了一系列的 `install` 指令，用于将构建生成的目标文件、库文件、目录和配置文件安装到指定的目标位置。以下是对常用 `install` 指令的总结：

* **1. 安装目标文件**
    ```cmake
    install(TARGETS cmake_examples_inst_bin
        DESTINATION bin)
    ```

    - **作用**：将目标文件 `cmake_examples_inst_bin` 安装到 `bin` 目录。

* **2. 安装库文件**
    ```cmake
    install(TARGETS cmake_examples_inst
        LIBRARY DESTINATION lib)
    ```

    - **作用**：将库文件 `cmake_examples_inst` 安装到 `lib` 目录。

* **3. 安装库文件和运行时文件**
    ```cmake
    install(TARGETS cmake_examples_inst
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)
    ```

    - **作用**：将库文件 `cmake_examples_inst` 安装到 `lib` 目录，将运行时文件安装到 `bin` 目录。

* **4. 安装目录**
    ```cmake
    install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/
        DESTINATION include)
    ```

    - **作用**：将目录 `${PROJECT_SOURCE_DIR}/include/` 安装到 `include` 目录。

* **5. 安装文件**
    ```cmake
    install(FILES cmake-examples.conf
        DESTINATION etc)
    ```

    - **作用**：将文件 `cmake-examples.conf` 安装到 `etc` 目录。

* **默认安装位置**

- **默认安装位置**：默认安装位置由 `CMAKE_INSTALL_PREFIX` 设置，默认值为 `/usr/local/`。
- **更改默认安装位置**：如果要为所有用户更改默认安装位置，可以在顶层 `CMakeLists.txt` 文件中添加以下代码：

```cmake
set(CMAKE_INSTALL_PREFIX "/desired/install/path" CACHE PATH "Installation Directory" FORCE)
```

### 5. 第三方库
第三方库的介绍说明都比较长，因此都单独展开细说。

#### 5.1 系统自带方式
- find_package
- find_library

#### 5.2 vendoring方式
- git sub-module
- git sub-tree

#### 5.3 url下载方式
- ExternalProject_Add
- fetchContent

#### 5.4 conan方式
- conan

### 6. 杂项

#### 6.1 编译器设置

  ```cmake
  add_definitions(-DDEBUG) # 添加全局宏定义
  target_compile_definitions(TARGET_OBJECT PRIVATE DEBUG) # 为特定目标添加宏定义
  ```

- **什么是编译器的编译选项?**
  `g++ -o2`其中`-o2`就是一个编译器选项,一般还包括优化级别/警告选项/目标平台选项/调试选项等.

- **为什么有时候看见的`ADD_DEFINITIONS`添加的不太像是一个编译器选项?**
  那说明编译器本身并不直接识别或处理这个命令，而是将其作为预定义的宏定义传递给代码的预处理阶段。

  ```c++
  #ifdef IAMHUNGRYNOW
      ...
  #else
      ...
  #endif
  ```

#### 6.2 什么是可见性？
这个`[PUBLIC|PRIVATE|INTERFACE]`是可见性属性
1. `PRIVATE`
    include 目录仅应用于目标自身.
2. `PUBLIC`
    include 目录将应用于目标自身，以及使用目标自己的其他目标
3. `INTERFACE`
    include 目录仅应用于使用目标的其他目标，不应用于目标自身.

```cmake
  add_library(my_lib src.cpp)
  target_include_directories(my_lib XXX_ATTR
      ${PROJECT_SOURCE_DIR}/include
  )

  target_link_libraries(my_executable private my_lib)
  ```

* 如果`XXX_ATTR`为private，`my_executable`不可以使用这个头文件路径
* 如果`XXX_ATTR`为public，`my_executable`也可以使用这个头文件路径
* 如果`XXX_ATTR`为interface，`my_executable`可以使用这个头文件路径，但是自己不使用。
  * header-only文件库，实现和定义都在头文件。
  * 接口库，我给了头文件，我不负责实现。
  * 传递编译选项。

#### 6.3 什么是`add_subdirectory()`？

它的作用是将名为`subdir`的子目录添加到当前项目的构建过程中.
- **`add_subdirectory()`的使用场景是什么?**
  当你的项目由多个模块或子项目组成时,每个模块有自己的源文件/依赖关系和构建配置,你可以使用`add_subdirectory()`来将每个模块作为子目录添加到主项目中.这样可以将项目的构建过程分解为更小的部分,每个部分有自己的`CMakeLists.txt`文件来管理.例如以下场景

  - 多模块项目:
  - 第三方库或模块:共享功能库:如果你有一些通用的功能或工具代码,你可以将其封装为一个独立的库,并将其作为子目录添加到不同的项目中.
  - 构建和测试工具:

#### 6.4 cmake的build文件说明
- **CMake 中的 cache 有什么用?**
  首先 cache 中存储的变量是全局的，父目录子目录都可以查看。

- **.cmake 是什么文件?**
  `.cmake`文件是一种常见的文件扩展名,用于存储 CMake 相关的配置/宏定义/函数或其他辅助功能.

### 99. quiz

#### 1. CMakeLists 是大小写敏感的吗?

不完全是,CMake 的语法和关键词是大小写不敏感的.但是变量和函数名是大小写敏感的

- `find_package`

- **`set`变量的作用域有多大?**

  - 在 CMakeLists.txt 文件中使用`set`命令设置的变量默认情况下是全局变量,对整个项目都是可见的.
  - 在子目录的 CMakeLists.txt 文件中设置的变量将在该子目录及其子目录中生效,但不会影响父目录或其他兄弟目录中的变量.
  - 在函数或宏中使用`set`命令设置的变量的作用域仅限于该函数或宏内部,不会影响调用它们的上下文.这意味着这些变量在函数或宏之外是不可见的.

- **`IF(A)`和`IF(${A})`的区别是什么?**

- **`SET(A ${A})`和`SET(A "${A}")`的区别是什么?**

- **`SET(A "${A}" CACHE PATH "xxx")`的意义是什么?**

#### 3. cmake 的顺序问题

一般是先生成 target，再设置 target 的条件，例如 include 目录，属性等等。

#### 1.宏和函数在 CMake 的区别是什么？
  1. 参数传递方式:宏和函数在参数传递方式上有所不同.在 CMake 中,宏的参数是通过简单的文本替换来传递的,而函数的参数则是通过变量的赋值和引用传递的.
  2. 变量作用域:宏和函数在变量作用域上有所不同.宏的定义和调用是在同一个变量作用域内进行的,宏内部的变量对于调用宏的上下文没有影响.而函数具有独立的变量作用域,函数内部的变量只在函数内部有效,不会影响调用函数的上下文.
  3. 返回值:宏没有返回值的概念,而函数可以使用`return()`命令来显式返回一个结果.

### 100. 未整理

我设置了 set(CMAKE_CXX_FLAGS "-std=c++17") 但是没有效果（谁让你这样设置版本的？我课上说了多少遍要用 set(CMAKE_CXX_STANDARD 17) 知道吗？你那个东西有概率会被覆盖而且不跨平台！CMAKE_CXX_STANDARD 才是标准做法）

我设置了 set(CMAKE_CXX_FLAGS "-O3") 但是没有效果（谁让你这样设置开关优化的？我课上说了多少遍要用 set(CMAKE_BUILD_TYPE Release) 知道吗？你那个东西有概率会被覆盖根本不跨平台！CMAKE_BUILD_TYPE 才是标准做法，Release 开优化，Debug 关优化，RelWithDebInfo 会开优化但保留调试信息，如果要让 Release 从默认的 -O3 变成 -O2 应该用 set(CMAKE_CXX_FLAGS_RELEASE "-O2") 同理还有 CMAKE_CXX_FLAGS_DEBUG 可以设）

我想要链接某某库，能不能把他做成 subdir 方便我链接？（只有官方支持 CMake subdir 邪教的那些库，如 fmt, spdlog 等可以，否则必须先 make install 那个库到系统中去，然后 find_package 他，subdir 是邪教，不是官方推荐的方法，小彭老师能在 Zeno 里大量用是因为他是 CMake 专家，他有那个本事，如果希望实现完美的“自包含”也可以尝试一下 CMake 自带的 FetchContent 功能，指定一个 URL，他会自动帮你从网上下载依赖项的源码并构建，并使你的主项目能够找到他

target_link_libraries(imported_targets PRIVATE Boost::filesystem)

### 100. 常用变量

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

