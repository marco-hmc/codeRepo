# 建立可迭代区域

我们已经认识了STL中提供的各种迭代器。我们只需实现一个迭代器，支持前缀加法`++`，解引用`*`和比较操作`==`，这样我们就能使用C++11基于范围的for循环对该迭代器进行遍历。

为了更好的了解迭代器，本节中将展示如何实现一个迭代器。迭代该迭代器时，只输出一组数字。实现的迭代器并不支持任何容器，以及类似的结构。这些数字是在迭代过程中临时生成的。

## How to do it...

本节中，我们将实现一个迭代器类，并且对该迭代器进行迭代：

1. 包含必要的头文件。

   ```c++
   #include <iostream> 
   class num_iterator { 

   	int i;
   public:
   	explicit num_iterator(int position = 0) : i{position} {}
   	int operator*() const { return i; }
       num_iterator& operator++() {
           ++i;
           return *this;
       }
       bool operator!=(const num_iterator &other) const {
       	return i != other.i;
       }
   };
   
   class num_range {
       int a;
       int b;
   public:
       num_range(int from, int to)
       	: a{from}, b{to}{}
       num_iterator begin() const { return num_iterator{a}; }
       num_iterator end() const { return num_iterator{b}; }
   };

   int main()
   {
       for (int i : num_range{100, 110}) {
       	std::cout << i << ", ";
       }
       std::cout << '\n';
   }
   ```

11. 编译运行后，得到如下输出：

    ```c++
    100, 101, 102, 103, 104, 105, 106, 107, 108, 109,
    ```

## How it works...

考虑一下如下的代码段：

```c++
for (auto x : range) { code_block; }
```

这段代码将被编译器翻译为类似如下的代码：

```c++
{
    auto __begin = std::begin(range);
    auto __end = std::end(range);
    for ( ; __begin != __end; ++__begin) {
        auto x = *__begin;
        code_block
    }
}
```

这样看起来就直观许多，也能清楚的了解我们的迭代器需要实现如下操作：

- operator!=
- operatpr++
- operator*

也需要`begin`和`end`方法返回相应的迭代器，用来确定开始和结束的范围。

> Note:
>
> 本书中，我们使用`std::begin(x)`替代`x.begin()`。如果有`begin`成员函数，那么`std::begin(x)`会自动调用`x.begin()`。当`x`是一个数组，没有`begin()`方法是，`std::begin(x)`会找到其他方式来处理。同样的方式也适用于`std::end(x)`。当用户自定义的类型不提供`begin/end`成员函数时，`std::begin/std::end`就无法工作了。

本例中的迭代器是一个前向迭代器。再来看一下使用`num_range`的循环，从另一个角度看是非常的简单。

> Note:
>
> 回头看下构造出迭代器的方法在`range`类中为`const`。这里不需要关注编译器是否会因为修饰符`const`而报错，因为迭代`const`的对象是很常见的事。

