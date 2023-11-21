---
title: 第 9 章 其他杂项
type: book-zh-cn
order: 9
---

# 第 9 章 其他杂项

[TOC]

## 9.1 新类型

## 9.2 noexcept 的修饰和操作


## 9.3 字面量

### 自定义字面量

C++11 引进了自定义字面量的能力，通过重载双引号后缀运算符实现：

```cpp
// 字符串字面量自定义必须设置如下的参数列表
std::string operator"" _wow1(const char *wow1, size_t len) {
    return std::string(wow1)+"woooooooooow, amazing";
}

std::string operator"" _wow2 (unsigned long long i) {
    return std::to_string(i)+"woooooooooow, amazing";
}

int main() {
    auto str = "abc"_wow1;
    auto num = 1_wow2;
    std::cout << str << std::endl;
    std::cout << num << std::endl;
    return 0;
}
```

自定义字面量支持四种字面量：

1. 整型字面量：重载时必须使用 `unsigned long long`、`const char *`、模板字面量算符参数，在上面的代码中使用的是前者；
2. 浮点型字面量：重载时必须使用 `long double`、`const char *`、模板字面量算符；
3. 字符串字面量：必须使用 `(const char *, size_t)` 形式的参数表；
4. 字符字面量：参数只能是 `char`, `wchar_t`, `char16_t`, `char32_t` 这几种类型。

## 9.4 内存对齐

C++ 11 引入了两个新的关键字 `alignof` 和 `alignas` 来支持对内存对齐进行控制。
`alignof` 关键字能够获得一个与平台相关的 `std::size_t` 类型的值，用于查询该平台的对齐方式。
当然我们有时候并不满足于此，甚至希望自定定义结构的对齐方式，同样，C++ 11 还引入了 `alignas`
来重新修饰某个结构的对齐方式。我们来看两个例子：

```cpp
#include <iostream>

struct Storage {
    char      a;
    int       b;
    double    c;
    long long d;
};

struct alignas(std::max_align_t) AlignasStorage {
    char      a;
    int       b;
    double    c;
    long long d;
};

int main() {
    std::cout << alignof(Storage) << std::endl;
    std::cout << alignof(AlignasStorage) << std::endl;
    return 0;
}
```

其中 `std::max_align_t` 要求每个标量类型的对齐方式严格一样，因此它几乎是最大标量没有差异，
进而大部分平台上得到的结果为 `long double`，因此我们这里得到的 `AlignasStorage` 的对齐要求是 8 或 16。

## 总结

本节介绍的几个特性是从仍未介绍的现代 C++ 新特性里使用频次较靠前的特性了，`noexcept` 是最为重要的特性，它的一个功能在于能够阻止异常的扩散传播，有效的让编译器最大限度的优化我们的代码。

[返回目录](./toc.md) | [上一章](./08-filesystem.md) | [下一章 展望：C++20 简介](./10-cpp20.md)
