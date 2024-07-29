## clang-format

clang-format是一个非常强大的工具，用于自动格式化C、C++、Objective-C、Java、JavaScript、TypeScript等语言的代码。它是Clang项目的一部分，旨在自动化和统一代码的格式化风格，以提高代码的可读性和维护性。

相对于其他格式化工具来说，clang的优势如下：
配置灵活：通过.clang-format配置文件，用户可以详细定义代码格式化的规则，如缩进宽度、大括号风格等。
集成支持：clang-format可以集成到多种IDE和编辑器中，如Visual Studio、Eclipse、Vim等，也可以作为Git的钩子使用，实现提交前自动格式化。

大部分开源项目，都会通过clang-format的方式保证风格的一致性。如LLVM项目，Chromium项目等等。在商业项目，如QT库本身中也能看到很多clang-format的身影。

### 1. 使用方式

visual studio2017是原生支持clang-format了。

一般将`.clang-format`放在和BIM同级目录下，在vs选中代码，执行格式化命令（快捷键为`ctrl k ctrl f`）就能完成选中代码的格式化。

而`.clang-format`已经被放在BIM同级目录下，一般开发只需要知道现在可以通过`ctrl k ctrl f`去完成代码格式化就好，而格式化的配置项是在`.clang-format`提供的。

**clang-format是非强制使用，因此如果格式化达不到标准，不要进行格式化操作即可。**

### 2. 配置项

```yml
---
Language:           Cpp
BasedOnStyle:       Google                  # 基于Google风格
IndentWidth:        4                       # 缩进宽度
TabWidth:           4                       # Tab的空格大小为4
UseTab:             Never                   # 不使用Tab，tab为空格
SortIncludes:       true                    # 头文件排序，不会改行（删除用于区分模块的行，不会被删除），可以删除重复头文件，不会删除未使用的头文件
AccessModifierOffset: -4                    # 访问权限符(public, private, protected)的缩进向左缩进四格
AlignEscapedNewlines: Left                  # 换行符左对齐
AlwaysBreakTemplateDeclarations: true       # 模板参数总是换行

NamespaceIndentation: All                   # 命名空间缩进
BreakBeforeBraces: Allman                   # 函数后面的开括号，新起一行
AlignAfterOpenBracket: DontAlign            # 不特意对齐函数调用或声明中的参数   
BinPackArguments: true                      # 函数参数换行
BinPackParameters: true                     # 函数参数换行
ColumnLimit: 130                            # 列的最大宽度
AllowShortFunctionsOnASingleLine: None      # 允许短函数不是单独
...
```


### 3. 注意事项

* 宏的格式化
vs2017自带的clang-format不支持宏对齐功能，需要新版本的clang-format使用`AlignConsecutiveMacros: true`才可以开启宏声明的对齐功能。
所以对于下面这种情况，需要手动对齐
```c++
#define BIM_XXX_YYY             A
#define BIM_XXX_YYY_ZZZ         B
```