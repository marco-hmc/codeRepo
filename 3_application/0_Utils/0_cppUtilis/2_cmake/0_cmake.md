## cmake

### cheat-sheet

* **与源文件和目录相关的变量**
  - **${CMAKE_CURRENT_SOURCE_DIR}**：
    表示当前处理的 CMakeLists.txt 文件所在的源文件目录。
  - **${CMAKE_CURRENT_BINARY_DIR}**：
    对应于当前 CMakeLists.txt 文件对应的构建目录，也就是编译生成目标文件、中间文件等所在的目录。
  - **${CMAKE_SOURCE_DIR}**：
    整个项目最顶层的源文件目录，是所有源文件目录的根目录，对于定位项目中全局的一些公共源文件、资源文件等非常有用。
  - **${CMAKE_BINARY_DIR}**：
    整个项目的构建根目录，所有的构建产物最终都会放置在这个目录或者其下的子目录中，类似构建过程中生成的库文件、可执行文件等都会在这个目录结构下，并且可以利用它来设置一些全局的输出布局。
  - **${PROJECT_SOURCE_DIR}**
    最近的定义`project()`的那个`CMakeLists.txt`所在的目录。
  - **${PROJECT_BINARY_DIR}**
    当前项目的构建目录。
  - **${CMAKE_PREFIX_PATH}**
    用于告诉 CMake 去哪里查找一些外部的项目、库或者工具链等相关文件。
  - **${CMAKE_LIBRARY_PATH}**
    指定 CMake 查找库文件的路径。
  - **${CMAKE_FIND_ROOT_PATH}**：
    在跨平台交叉编译或者查找特定路径下的依赖库时很有用，它定义了一个搜索路径的根路径，CMake 会基于这个根路径去查找库文件、头文件等，比如在嵌入式开发中，指定交叉编译工具链对应的系统根目录路径，通过 `set(CMAKE_FIND_ROOT_PATH /path/to/embedded/root)` 来辅助查找相关的库和头文件。
  
* **与编译选项相关的变量**
  - **${CMAKE_C_FLAGS}**：
    用于设置 C 语言编译器的编译选项，比如可以添加优化级别选项 `-O2` ，调试相关选项 `-g` 等，像 `set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -g")`。
  - **${CMAKE_CXX_FLAGS}**：
    和上面类似，不过是针对 C++ 语言编译器的编译选项，同样可以添加诸如优化、调试、警告处理等相关的参数。  
  - **${CMAKE_BUILD_TYPE}**：
    表示当前的构建类型，常见的值有 `Debug`、`Release`、`RelWithDebInfo`（发布版本带调试信息）、`MinSizeRel`（最小化大小发布版）等，不同的构建类型会应用不同的编译选项，例如在 `Debug` 类型下会默认开启更多的调试相关的编译参数，方便调试程序，而 `Release` 类型则侧重于优化生成的二进制文件性能和减小文件大小等，可以通过 `set(CMAKE_BUILD_TYPE Release)` 来显式指定构建类型。    
    
* **与目标属性相关的变量**
  - **${PROJECT_NAME}**：
    代表当前项目的名称，这个名称通常是通过 `project()` 命令在 CMakeLists.txt 中定义的，在后续指定生成的目标文件（如库文件、可执行文件）的名称、安装目录等场景中会经常用到，比如 `add_library(${PROJECT_NAME}_lib mylib.cpp)` ，就会以项目名称结合后缀的形式来命名生成的库文件。
  - **${CMAKE_INSTALL_PREFIX}**：
    用于指定项目安装的根目录，当执行 `make install` 命令时，生成的可执行文件、库文件、头文件等会按照设定的安装规则安装到这个指定的目录及其子目录下，例如 `set(CMAKE_INSTALL_PREFIX /usr/local)` ，那么最终的安装产物就会放置到 `/usr/local` 对应的合适位置（可执行文件到 `bin` 目录、库文件到 `lib` 目录等）。


### 0. 基本概念

- **什么是构建工具？**
  根据构建文件，调用编译器，连接器完成生成目标对象`target`就是构建工具，cmake就是构建工具。
  而生成目标对象`target`可以是静态库、动态库和可执行文件（甚至进一步的，生成对象可以为空，用于表示执行脚本。比如比如 make 工具中的 make clean，资源化，代码检查等等）。

- **构建工具和文件的生态位置**
  - **Make**：Make 是一个构建工具，它根据 Makefile 调用编译器和链接器来构建项目。
  - **Makefile**：Makefile 是 Make 使用的构建文件，用于描述如何构建项目。Make 读取 Makefile，并根据其中定义的规则调用编译器和链接器。

  - **MSBuild**：MSBuild 是 Microsoft 的构建工具，它根据 .vcxproj 文件（Visual C++ 项目文件）和 .csproj 文件（C# 项目文件）调用编译器和链接器来构建项目。
  - **.vcxproj**：.vcxproj 文件是 Visual C++ 项目的项目文件，用于描述如何构建 Visual C++ 项目。MSBuild 读取 .vcxproj 文件，并根据其中定义的规则调用编译器和链接器。

  - **Ninja**：Ninja 是一个高效的构建工具，它根据 build.ninja 文件调用编译器和链接器来构建项目。
  - **build.ninja**：build.ninja 文件是 Ninja 使用的构建文件，用于描述如何构建项目。Ninja 读取 build.ninja 文件，并根据其中定义的规则调用编译器和链接器。

- **发展演化的描述**
  我未经考察地做一些发展演化的描述，以便串起这些工具和文件的关系。一开始，构建工具主要是 Make，它使用 Makefile 来描述构建过程。然而，Makefile 的语法和功能有限，针对大型工程非常吃力。于是出现了 CMake，它通过 CMakeLists.txt 文件生成 Makefile。
  与此同时，微软通过 Visual Studio IDE 提供了项目管理功能，允许用户通过 GUI 操作指定哪些文件属于同一个模块，并生成静态库、动态库或可执行文件。相应的数据存储在 `.vcxproj` 文件中。
  CMake 的设计目标是生成构建文件描述，因此它不仅可以生成 Makefile，还可以生成 .vcxproj 文件。CMake 支持.vcxproj 也只是顺手之举。
  后来，Google 推出了 Ninja 构建工具，旨在提高构建效率。其实就是改进 make 的。但是 make 的所有权又不是 Goole 的。便直接另起炉灶了。

- **总结**
  需要有一个文件指定编译路径，怎么调用编译器，生成什么对象（库还是可执行文件）等等，这个文件叫构建文件。解析这个构建文件实际调用编译器、链接器的就是构建工具了。
  > 构建工具： make-makefile, MSBuild-.vcxproj, Ninja-build.ninja，就是c++下常见构建工具和构建文件。
  构建文件描述的生成有三种方式：手工写、gui 操作、脚本生成。在早期没有ninja，对于makefile都是手写；而.vcxproj则是gui点击操作。
  后来出现了cmake，cmake可以理解为一种专门用于生成构建文件的脚本语言吧。因此可以生成makefile文件，从而避免手写；同时也方便了跨平台，一个vs工程如果支持cmake，迁移到linux也方便了。
  至于ninja可以理解为是make的补丁版本，解决make编译速度太慢的问题。为什么不直接在make上改呢？那是因为make的背后是unix团队，MSBuild的背后是google团队。而ninja是google推出来的。是社会工程学的问题。而make也在迭代，新版本有没有解决编译速度慢的问题则不好说了。


### 1. cmake 脚本语法

#### 1.1 设置变量-set
  - **SET**
    ```cmake
    SET(ZS_NAME "${AB}") # 第一种写法
    SET(ZS_NAME ${CD}) # 第二种写法
    set(ENV{MY_ENV_VARIABLE} "Hello!")
    set(ENV{MY_ENV_VARIABLE}_xxx "Hello!") # 可拼接
    # 使用的时候，要使用${VAR_NAME}
    ```

    第一种写法和第二种写法是等价的，都是用来设置变量的值。区别在于第一种写法使用了双引号将变量的值括起来，而第二种写法没有使用双引号。使用双引号可以确保变量的值被视为一个整体，而不会被解释为多个独立的字符串。在这个例子中，由于 `${AB}` 和 `${CD}` 是变量，它们的值将被替换为实际的值，然后赋给 `ZS_NAME` 变量。所以在这种情况下，这两种写法是等效的。

#### 1.2 条件操作-if
  - **IF**
    ```cmake
    IF(CONDITION)
      # ...
    ELSE()
      # ...
    ENDIF()
    ```

#### 1.3 循环操作-while-foreach
  - **while**
    ```cmake
    WHILE(CONDITION)
      # ...
    ENDWHILE()
    ```

  - **foreach**
    ```cmake
    FOREACH(item IN LISTS list)
      # ...
    ENDFOREACH()
    ```

#### 1.4 宏和函数-macro-func
    ```cmake
    macro(MacroName arg1 arg2 ...)
      # 宏的操作和命令
    endmacro()

    function(FunctionName arg1 arg2 ...)
      # ...
      # return() 可选，用于返回结果
    endfunction()
    ```

#### 1.5 其他-file
  - **file**
    ```cmake
    file(GLOB SOURCES "src/*.cpp")
    ```

    `file(GLOB ...)` 命令用于查找符合指定模式的文件，并将它们的路径存储在变量中。在这个例子中，`SOURCES` 变量将包含 `src` 目录下所有 `.cpp` 文件的路径。

### 2. 生成

#### 2.1 如何生目标？

  ```cmake
  add_library(my_static_lib STATIC source1.cpp) # 定义静态库
  add_library(my_shared_lib SHARED source1.cpp) # 定义动态库
  add_executable(EXECUTABLE_NAME main.cpp)
  add_custom_target()
  add_dependencies(<target> <dependency> [<dependency>...])
  add_test()
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
  # CMAKE_PREFIX_PATH 变量用于设置库和头文件的搜索路径。通常用于设置多个库和头文件的搜索路径。
  ```

### 4. 脚本引用
#### 4.1 ctest.cmake
搭配add_executable(), add_test()和include(ctest)使用。

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

### 6. 打包

#### 6.1 cpack

### 7. 安装
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


### 8. 杂项

#### 8.1 编译器设置

  ```cmake
  add_definitions(-DDEBUG) # 添加全局宏定义
  target_compile_definitions(TARGET_OBJECT PRIVATE DEBUG) # 为特定目标添加宏定义
  ```

  ```cmake
  set(CMAKE_CXX_STANDARD 17)  # 设置 C++ 标准为 C++17
  set(CMAKE_CXX_STANDARD_REQUIRED ON)  # 要求必须支持该标准，否则报错
  set(CMAKE_BUILD_TYPE Debug)  # 设置构建类型为 Debug，也可以是 Release、RelWithDebInfo 等
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

#### 8.2 什么是可见性？
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

#### 8.3 什么是`add_subdirectory()`？

它的作用是将名为`subdir`的子目录添加到当前项目的构建过程中.
- **`add_subdirectory()`的使用场景是什么?**
  当你的项目由多个模块或子项目组成时,每个模块有自己的源文件/依赖关系和构建配置,你可以使用`add_subdirectory()`来将每个模块作为子目录添加到主项目中.这样可以将项目的构建过程分解为更小的部分,每个部分有自己的`CMakeLists.txt`文件来管理.例如以下场景

  - 多模块项目:
  - 第三方库或模块:共享功能库:如果你有一些通用的功能或工具代码,你可以将其封装为一个独立的库,并将其作为子目录添加到不同的项目中.
  - 构建和测试工具:

#### 8.4 cmake的build文件说明
- **CMake 中的 cache 有什么用?**
  首先 cache 中存储的变量是全局的，父目录子目录都可以查看。

- **.cmake 是什么文件?**
  `.cmake`文件是一种常见的文件扩展名,用于存储 CMake 相关的配置/宏定义/函数或其他辅助功能.

#### 8.5 .cmake文件的使用

#### 8.6 cmakePresets.json使用


### 99. quiz

#### 1. CMakeLists 是大小写敏感的吗?

不完全是,CMake 的语法和关键词是大小写不敏感的.但是变量和函数名是大小写敏感的

- **`set`变量的作用域有多大?**

  - 在根目录的CMakeLists.txt 文件中使用`set`命令设置的变量默认情况下是全局变量,对整个项目都是可见的.
  - 在子目录的 CMakeLists.txt 文件中设置的变量将在该子目录及其子目录中生效,但不会影响父目录或其他兄弟目录中的变量.
  - 在函数或宏中使用`set`命令设置的变量的作用域仅限于该函数或宏内部,不会影响调用它们的上下文.这意味着这些变量在函数或宏之外是不可见的.

- **`IF(A)`和`IF(${A})`的区别是什么?**

- **`SET(A ${A})`和`SET(A "${A}")`的区别是什么?**

#### 2. cmake 的顺序问题和依赖问题

* cmake顺序
  一般是先生成 target，再设置 target 的条件，例如 include 目录，属性等等。
* cmake依赖
  * add_dependencies() 显式指定
  * target_link_libraries() 隐式指定
  * find_package() 隐式指定

#### 3.宏和函数在 CMake 的区别是什么？
  1. 参数传递方式:宏和函数在参数传递方式上有所不同.在 CMake 中,宏的参数是通过简单的文本替换来传递的,而函数的参数则是通过变量的赋值和引用传递的.
  2. 变量作用域:宏和函数在变量作用域上有所不同.宏的定义和调用是在同一个变量作用域内进行的,宏内部的变量对于调用宏的上下文没有影响.而函数具有独立的变量作用域,函数内部的变量只在函数内部有效,不会影响调用函数的上下文.
  3. 返回值:宏没有返回值的概念,而函数可以使用`return()`命令来显式返回一个结果.

#### 4. 注意事项
* 不要设置`CMAKE_CXX_FLAGS`，会被覆盖
  * `set(CMAKE_CXX_FLAGS "-std=c++17") ` -> `set(CMAKE_CXX_STANDARD 17)`
  * `set(CMAKE_CXX_FLAGS "-O3") ` -> `set(CMAKE_BUILD_TYPE Release)`

#### 5. ccache
ccache是一个用来加速build阶段的工具。但用处不大。cache是作为build过程的前处理阶段，判断是否有无cache，有就用上的。那这个阶段为什么不是内置到make里面，而是单独作为一个工具呢？如果有用，make打个补丁加上去不就好了吗。



cmake/gmake and ccache are not exclusive to each other. They are typically used together.

ccache comes into play when the entire source tree needs to be rebuilt for some reason. cmake/gmake rebuilds only changed files, but there are situations where the entire source tree needs to be recompiled. And if this happens repeatedly, ccache will wake up and short-circuit the compiler. C++ compilers are notorious for being slow, and this often helps quite a bit.

Just a couple of examples: when you need to repeatedly switch between building with and without optimizations, repeatedly. cmake/gmake won't help you when you edit the makefile and adjust the compilation flags. None of the source files actually changed, so cmake/gmake doesn't think there's anything to do, so you must explicitly make clean and recompile from scratch.

If you are doing it repeatedly, ccache will avoid having to run the compiler on the entire source code, and will simply fetch out the appropriate object module instead of compiling the source from scratch.

Another common situation is when you're running a script to prepare an installable package for your code. This typically involves using an implementation-specific tool to rebuild the source code, from scratch, into an installable package.



Consider the case where you switch to some older branch of your project - that you did compile in the past and that ccache has cached, but CMake sees as "almost all files have changed and must be recompiled" - that's where you see a massive gain.

Another situation is where you have deleted your build directory (for some good reason) and now have to rebuild everything. ccache is also a huge help there.

Also; ccache is trivial to set up and is thenceforth completely invisible / transparent, so there really is no reason to not use it. When it helps it usually helps a lot, when it does not help it doesn't hurt.



#### 6. cmake生成的build目录说明
