## conan 

### 1. 什么是conan？应用场景是什么？
Conan 是一个开源的 C/C++ 包管理器，旨在帮助开发者管理和分发库。它可以用于解决依赖关系、版本控制和跨平台构建等问题。应用场景包括但不限于：
- 管理项目的第三方库依赖
- 构建和发布内部库
- 支持跨平台开发

### 2. conan怎么用？

#### 2.1 基本使用步骤

1. `创建conanfile.txt`

```ini
# `conanfile.txt`
[requires]
fmt/5.3.0@bincrafters/stable

[generators]
cmake
```

2. `安装依赖项`
```shell
    conan install .
```
这将下载并安装 fmt 库及其依赖项，并生成一个 `conanbuildinfo.cmake` 文件，用于集成到 CMake 构建系统中。

3. `集成到cmake构建系统`
```cmake
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
```

#### 2.2 相关文件有哪些？
- `conanfile.txt`：简化的包定义文件，主要用于列出依赖。
- `conanfile.py`：定义包的配方，包括依赖、构建选项、源代码等。
- `conan.lock`：锁定依赖版本，确保构建的一致性。
- `conan-profile`：Conan 的 profile 是用于定义包构建和运行时的配置参数的文件。它包含了编译器设置、编译选项、环境变量等信息。使用 profile 可以确保在不同的环境中构建和运行包时的一致性和可重复性。

#### 常用命令有哪些？
- `conan install`：安装依赖包。
- `conan create`：创建并打包库。
- `conan upload`：上传包到远程仓库。
- `conan search`：搜索包。
- `conan remove`：删除本地或远程包。

#### conan-profile 怎么用？
- **一致性**：确保在不同的机器和环境中构建包时使用相同的配置。
- **可重复性**：可以轻松地重现构建环境，方便调试和测试。
- **简化配置**：通过 profile 文件，可以避免在命令行中重复输入配置参数。

你可以通过 `conan profile` 命令来管理 profile，例如创建、编辑和列出 profile。

Conan 的 profile 是全局的，默认情况下存储在用户主目录下的 `.conan2/profiles` 目录中。因此，所有工作空间都可以访问和使用这些 profile。

不过，你也可以在项目级别创建和使用自定义的 profile。只需在项目目录中创建一个 profile 文件，然后在运行 Conan 命令时指定该 profile。例如：


### 98. attach files
```ini
    ## conanfile.txt
    [requires]
    # 列出项目所需的依赖包
    boost/1.75.0
    poco/1.10.1

    [generators]
    # 指定生成的构建文件类型
    cmake

    [options]
    # 定义包的可选配置
    boost:shared=True
    poco:shared=True

    [imports]
    # 指定要导入的文件
    bin, *.dll -> ./bin
    lib, *.dylib* -> ./lib
```

```ini
    ## conanfile-profile
    [settings]
    # 指定编译器、操作系统、架构等信息
    os=Linux
    arch=x86_64
    compiler=gcc
    compiler.version=10
    compiler.libcxx=libstdc++11
    build_type=Release

    [options]
    # 定义包的可选配置
    boost:shared=True
    poco:shared=True

    [build_requires]
    # 列出构建所需的工具包
    cmake/3.19.2

    [env]
    # 设置环境变量
    CC=/usr/bin/gcc
    CXX=/usr/bin/g++
```

### 99. quiz

#### 1. 为什么 Conan 推广不开，或者说 C++ 的包管理工具统一起来这么难？

C++ 的包管理工具推广困难，主要原因在于以下几个方面：

1. **平台差异**：
   - C++ 的包不像 Java 是平台无关的。每个平台（如 Windows、Linux、macOS）都有其特定的库和依赖，这导致需要为每个平台提供不同的包版本。
   - 操作系统层面的平台差异是情有可原的，但这只是问题的一部分。
2. **编译器差异**：
   - 不同的 C++ 编译器（如 GCC、Clang、MSVC）之间互不兼容。不同编译器的 ABI（应用二进制接口）不一样，库内部使用的编译器指令不同，内部调用的库指令也不同。
   - 这意味着一个包需要提供平台数与编译器数的乘积那么多个版本，才能覆盖所有可能的组合。
3. **依赖管理复杂**：
   - 由于平台和编译器的多样性，一个包的依赖管理变得非常复杂。每个依赖项也需要考虑平台和编译器的兼容性，这进一步增加了管理的难度。
4. **现有工具的局限性**：
   - Windows 平台一般使用 vcpkg，它主要支持 Windows 平台和 MSVC 编译器。
   - 如果是自己发布和管理包，通常使用 Conan，可以自己配置源服务器和包管理策略。

