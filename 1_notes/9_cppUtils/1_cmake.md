## Q&A of CMake

> marco

[toc]

### 1. Easy

* **CMakeLists是大小写敏感的吗?**

  不完全是,CMake的语法和关键词是大小写不敏感的.但是变量和函数名是大小写敏感的



* **下面两则代码有区别吗?**

  ```cmake
  ## code1
  set(SOURCES
      src/Hello.cpp
      src/main.cpp
  )
  ## code2
  set(SOURCES
      src/Hello.cpp; src/main.cpp
  )
  ```



* **如何指定头文件路径**

  ```cmake
  target_include_directories(hello_headers
      PRIVATE 
          ${PROJECT_SOURCE_DIR}/include
  )
  ```

  等价于 `g++` 里面的`-I`指定include路径



* **如何指令库路径**

  ```cmake
  target_link_libraries(target_name [PRIVATE|PUBLIC|INTERFACE] library_name1 library_name2 ...)
  
  ```

  

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



* `find_package`

  

### 2. Advanced

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

    

* **`set`变量的作用域有多大?**

  - 在CMakeLists.txt文件中使用`set`命令设置的变量默认情况下是全局变量,对整个项目都是可见的.
  - 在子目录的CMakeLists.txt文件中设置的变量将在该子目录及其子目录中生效,但不会影响父目录或其他兄弟目录中的变量.
  - 在函数或宏中使用`set`命令设置的变量的作用域仅限于该函数或宏内部,不会影响调用它们的上下文.这意味着这些变量在函数或宏之外是不可见的.

  

* **.cmake是什么文件?**

  `.cmake`文件是一种常见的文件扩展名,用于存储CMake相关的配置/宏定义/函数或其他辅助功能.

  

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

    

* **CMake中的cache有什么用?**

  首先cache中存储的变量是全局的,父目录子目录都可以查看.



### 3. Q&A

* **`IF(A)`和`IF(${A})`的区别是什么?**

* **`SET(A ${A})`和`SET(A "${A}")`的区别是什么?**

* **`SET(A "${A}" CACHE PATH "xxx")`的意义是什么?**

  
