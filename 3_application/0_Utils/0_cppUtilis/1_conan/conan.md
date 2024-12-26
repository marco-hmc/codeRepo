## conan 

### 1. 什么是conan？应用场景是什么？
Conan 是一个开源的 C/C++ 包管理器，旨在帮助开发者管理和分发库。它可以用于解决依赖关系、版本控制和跨平台构建等问题。应用场景包括但不限于：
- 管理项目的第三方库依赖
- 构建和发布内部库
- 支持跨平台开发

### 2. conan怎么用？

#### 关键文件有哪些？
- `conanfile.py`：定义包的配方，包括依赖、构建选项、源代码等。
- `conanfile.txt`：简化的包定义文件，主要用于列出依赖。
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