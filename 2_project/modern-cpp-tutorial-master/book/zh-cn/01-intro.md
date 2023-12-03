---
title: 第 1 章 迈向现代 C++
type: book-zh-cn
order: 1
---

## 1.2 与 C 的兼容性

如果你是首次接触现代 C++，那么你很可能还看不懂上面的那一小段代码，即：

```cpp
[out = std::ref(std::cout << "Result from C code: " << add(1, 2))](){
    out.get() << ".\n";
}();
```

不必担心，本书的后续章节将为你介绍这一切。

[返回目录](./toc.md) | [上一章](./00-preface.md) | [下一章 语言可用性强化](./02-usability.md)

## 进一步阅读的参考文献

- [C++ 语言导学. Bjarne Stroustrup](https://www.amazon.cn/dp/B00WUBYBYS/ref=sr_1_1?ie=UTF8&qid=1522400738&sr=8-1&keywords=C%2B%2B+%E8%AF%AD%E8%A8%80%E5%AF%BC%E5%AD%A6)
- [C++ 历史](https://en.cppreference.com/w/cpp/language/history)
- [C++ 特性在 GCC/Clang 等编译器中的支持情况](https://en.cppreference.com/w/cpp/compiler_support)
- [C++98 与 C99 之间的区别](http://david.tribble.com/text/cdiffs.htm#C99-vs-CPP98)
