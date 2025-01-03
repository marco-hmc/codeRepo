## cmake

### 1. 常用基本语法

#### 1.1 路径指定

* **如何指定头文件路径**

  ```cmake
  target_include_directories(hello_headers
      PRIVATE 
          ${PROJECT_SOURCE_DIR}/include
  )
  ```

* **如何指令库路径**

  ```cmake
  target_link_libraries(target_name [PRIVATE|PUBLIC|INTERFACE] library_name1 library_name2 ...)
  
  ```

  等价于 `g++` 里面的`-I`指定include路径

#### 1.2 编译器设置
* **`ADD_DEFINITIONS`有什么用?**

  它用于将预定义的宏定义添加到编译器的编译选项中.

* **什么是编译器的编译选项?**

  `g++ -o2`其中`-o2`就是一个编译器选项,一般还包括优化级别/警告选项/目标平台选项/调试选项等.

* **为什么有时候看见的`ADD_DEFINITIONS`添加的不太像是一个编译器选项?**

  那说明编译器本身并不直接识别或处理这个命令,而是将其作为预定义的宏定义传递给代码的预处理阶段.

  例如,以下代码

  ```c++
  // ADD_DEFINITIONS(IAMHUNGRYNOW)
  #ifdef IAMHUNGRYNOW
      // 一些特定于 IAMHUNGRYNOW 的代码
  #else
      // 另一些代码
  #endif
  ```

#### 1.3 cmake脚本语法

* **SET**
  ```cmake
  SET(ZS_NAME "${AB}")
  SET(ZS_NAME ${CD})
  ```
  这两种写法是等价的,都是用来设置变量的值.区别在于第一种写法使用了双引号将变量的值括起来,而第二种写法没有使用双引号.使用双引号可以确保变量的值被视为一个整体,而不会被解释为多个独立的字符串.在这个例子中,由于${AB}和${CD}是变量,它们的值将被替换为实际的值,然后赋给ZS_NAME变量.所以在这种情况下,这两种写法是等效的.

* **Cmake的宏和函数是什么东西,语法是怎么样的?**

  ```cmake
  macro(MacroName arg1 arg2 ...)
    # 宏的操作和命令
  endmacro()
  ## macro:关键字用于定义一个宏.
  ## MacroName:宏的名称,你可以根据需要自定义.
  ## arg1, arg2, ...:宏的参数列表,你可以根据需要定义和使用参数.
  
  function(FunctionName arg1 arg2 ...)
    # 函数的操作和命令
    # return() 可选,用于返回结果
  endfunction()
  
  ## function:关键字用于定义一个函数.
  ## FunctionName:函数的名称,你可以根据需要自定义.
  ## arg1, arg2, ...:函数的参数列表,你可以根据需要定义和使用参数.
  ## return():可选的命令,用于在函数中返回结果.
  ```

  * **宏和函数在CMake的区别是什么?**
    1. 参数传递方式:宏和函数在参数传递方式上有所不同.在CMake中,宏的参数是通过简单的文本替换来传递的,而函数的参数则是通过变量的赋值和引用传递的.
    2. 变量作用域:宏和函数在变量作用域上有所不同.宏的定义和调用是在同一个变量作用域内进行的,宏内部的变量对于调用宏的上下文没有影响.而函数具有独立的变量作用域,函数内部的变量只在函数内部有效,不会影响调用函数的上下文.
    3. 返回值:宏没有返回值的概念,而函数可以使用`return()`命令来显式返回一个结果.


#### 1.4 生成

cmake中的目标是什么意思？
  目标（Target）是构建系统中的一个基本概念，表示一个可以构建的实体，如可执行文件、库文件。也可以特殊地表示一个自定义命令。

如何理解CMakePredefinedTargets?
* **`all_build`**
  - **描述**：`all_build` 目标用于构建项目中的所有目标。
  - **用途**：这是默认的构建目标，通常在执行 `make` 或 `cmake --build .` 时被调用。
* **`install`**
  - **描述**：`install` 目标用于将构建生成的文件安装到指定的安装目录。
  - **用途**：执行安装步骤，将可执行文件、库文件、头文件等复制到预定义的安装路径。
  ```
* **`package`**
  - **描述**：`package` 目标用于创建项目的分发包（如 `.tar.gz`、`.zip`、`.deb`、`.rpm` 等）。
  - **用途**：生成可分发的安装包，便于发布和分发项目。
* **`zero_check`**
  - **描述**：`zero_check` 目标用于确保生成的构建系统是最新的。
  - **用途**：在每次构建之前检查 CMakeLists.txt 文件和其他配置文件是否有变化，如果有变化，则重新运行 CMake 以更新构建



* **如何生成静态库和动态库?**

  ```cmake
  # 定义静态库
  add_library(my_static_lib STATIC
    source1.cpp
    source2.cpp
  )
  
  # 定义动态库
  add_library(my_shared_lib SHARED
    source1.cpp
    source2.cpp
  )
  
  ```


#### 1.5 杂项

* **什么是可见性?**

  ```cmake
  target_include_directories(hello_headers
      PRIVATE 
          ${PROJECT_SOURCE_DIR}/include
  )
  ```

  这个`PRIVATE`是可见性属性,可见性属性总共有3个.

  1. `PRIVATE`
     include目录仅应用于目标自身.

  2. `PUBLIC`
     include目录将应用于目标自身,以及使用目标自己的其他目标

  3. `INTERFACE`
     include目录仅应用于使用目标的其他目标,不应用于目标自身.

  * **`PUBLIC`的使用场景是什么?**
    * ```cmake
      add_library(my_library)
      target_include_directories(my_library PUBLIC include)
      ```

      在上述示例中,将`include`目录添加到`my_library`库的公共接口中.这意味着任何使用`my_library`的目标都可以访问`include`目录中的头文件,而无需显式设置包含目录.
    

* **什么是`add_subdirectory()`?**

  它的作用是将名为`subdir`的子目录添加到当前项目的构建过程中.

  * **`add_subdirectory()`的使用场景是什么?**

    当你的项目由多个模块或子项目组成时,每个模块有自己的源文件/依赖关系和构建配置,你可以使用`add_subdirectory()`来将每个模块作为子目录添加到主项目中.这样可以将项目的构建过程分解为更小的部分,每个部分有自己的`CMakeLists.txt`文件来管理.例如以下场景

    * 多模块项目:
    * 第三方库或模块:共享功能库:如果你有一些通用的功能或工具代码,你可以将其封装为一个独立的库,并将其作为子目录添加到不同的项目中.
    * 构建和测试工具:



### 2. 文件结构说明

* **CMake中的cache有什么用?**
  首先cache中存储的变量是全局的,父目录子目录都可以查看.

* **.cmake是什么文件?**

  `.cmake`文件是一种常见的文件扩展名,用于存储CMake相关的配置/宏定义/函数或其他辅助功能.

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


### 96. 

### 97. cmake提速方式
#### 1. 并行
#### 2. pimpl
#### 2. pch
#### 3. ccache
#### 4. unity build
* unity build - supported by cmake
  * 为什么会变快？因为编译单元少了，减少了编译的初始化开销。
  * 减少了头文件的重复解析
  * 更大的编译单元，利于内联函数，常量传播等编译器优化方式。
  * 缺点：
    * 调试：
    * 命名空间

* include what you used
* clang build analyzer
* module c++ 20

1、Windows 平台，使用increase build ，缺点是无法产生pdb 符号文件。速度有保障
2、Linux平台，最近发现一个很有趣的现象，我们写了一个脚本把所有的cpp 文件写到了一个CPP 文件中,可以大幅度提高编译速度，缺点是gdb 调试的时候不方便。
使用distcc 和ccache 并不能显著提高速度，除非机器数量特别庞大，而且要保证机器环境一致，相比之下更推荐写脚本把CPP 文件数量减少。


### 99. quiz 

#### 1. CMakeLists是大小写敏感的吗?

  不完全是,CMake的语法和关键词是大小写不敏感的.但是变量和函数名是大小写敏感的

* `find_package`

* **`set`变量的作用域有多大?**

  - 在CMakeLists.txt文件中使用`set`命令设置的变量默认情况下是全局变量,对整个项目都是可见的.
  - 在子目录的CMakeLists.txt文件中设置的变量将在该子目录及其子目录中生效,但不会影响父目录或其他兄弟目录中的变量.
  - 在函数或宏中使用`set`命令设置的变量的作用域仅限于该函数或宏内部,不会影响调用它们的上下文.这意味着这些变量在函数或宏之外是不可见的.

* **`IF(A)`和`IF(${A})`的区别是什么?**

* **`SET(A ${A})`和`SET(A "${A}")`的区别是什么?**

* **`SET(A "${A}" CACHE PATH "xxx")`的意义是什么?**

### 100. 未整理
 
我设置了 set(CMAKE_CXX_FLAGS "-std=c++17") 但是没有效果（谁让你这样设置版本的？我课上说了多少遍要用 set(CMAKE_CXX_STANDARD 17) 知道吗？你那个东西有概率会被覆盖而且不跨平台！CMAKE_CXX_STANDARD 才是标准做法）

我设置了 set(CMAKE_CXX_FLAGS "-O3") 但是没有效果（谁让你这样设置开关优化的？我课上说了多少遍要用 set(CMAKE_BUILD_TYPE Release) 知道吗？你那个东西有概率会被覆盖根本不跨平台！CMAKE_BUILD_TYPE 才是标准做法，Release 开优化，Debug 关优化，RelWithDebInfo 会开优化但保留调试信息，如果要让 Release 从默认的 -O3 变成 -O2 应该用 set(CMAKE_CXX_FLAGS_RELEASE "-O2") 同理还有 CMAKE_CXX_FLAGS_DEBUG 可以设）

我想要链接某某库，能不能把他做成 subdir 方便我链接？（只有官方支持 CMake subdir 邪教的那些库，如 fmt, spdlog 等可以，否则必须先 make install 那个库到系统中去，然后 find_package 他，subdir 是邪教，不是官方推荐的方法，小彭老师能在 Zeno 里大量用是因为他是 CMake 专家，他有那个本事，如果希望实现完美的“自包含”也可以尝试一下 CMake 自带的 FetchContent 功能，指定一个 URL，他会自动帮你从网上下载依赖项的源码并构建，并使你的主项目能够找到他
