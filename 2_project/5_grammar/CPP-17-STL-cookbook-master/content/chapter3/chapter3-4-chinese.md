# 使用迭代器实现算法

本节中，我们将用迭代器来实现斐波那契函数。斐波那契函数会有类似如下的迭代：`F(n) = F(n - 1) + F(n - 2)`。数列的初始值`F(0) = 0 `和 `F(1) = 1`。这样下列序列就可以进行计算：

- F(0) = 0
- F(1) = 1
- F(2) = F(1) + F(0) = 1
- F(3) = F(2) + F(1) = 2
- F(4) = F(3) + F(2) = 3
- F(5) = F(4) + F(3) = 5
- F(6) = F(5) + F(4) = 8
- ...

这里我们有两个选择——递归调用斐波那契函数计算整个数列，这样很浪费计算时间，或者将最后两个斐波那契数作为临时变量，并用它们来计算下一个数。
第二种方法我们需要重新实现斐波那契算法循环。这样我们就可以将斐波那契数列计算的代码和我们实际的代码放在一起：

```c++
size_ta{0};
size_tb{1};
for(size_ti{0};i< N;++i){
    constsize_told_b{b};
    b+=a;
    a=old_b;
    // do something with b, which is the current fibonacci number
}
```

## How to do it...

1. 为了打印斐波那契数列在终端，我们需要包含标准输入输出流头文件。

   ```c++
   #include <iostream>

   class fibit
   {
       size_t i {0};
       size_t a {0};
       size_t b {1};

   public:
       fibit() = default;
       explicit fibit(size_t i_)           : i{i_}
       {}

   	size_t operator*() const { return b; }
       fibit& operator++() {
           const size_t old_b {b};
           b += a;
           a = old_b;
           ++i;
           return *this;
       } 
   	bool operator!=(const fibit &o) const { return i != o.i; }
    }
   class fib_range
   {
   	size_t end_n;
   public:
       fib_range(size_t end_n_)
       	: end_n{end_n_}
       {}
       fibit begin() const { return fibit{}; }
       fibit end() const { return fibit{end_n}; }
   };

   int main()
   {
       for (size_t i : fib_range(10)) {
      		std::cout << i << ", ";
       }
       std::cout << '\n';
   }
   ```

10. 编译运行后，我们会在终端上看到如下的打印：

    ```c++
    1, 1, 2, 3, 5, 8, 13, 21, 34, 55,
    ```

## There's more...

为了兼容STL中的迭代器，这里实现的迭代器必须支持`std::iterator_traits`类。想要知道怎么做，要参考一下3.2节(让自己的迭代器与STL的迭代器兼容)，其对如何兼容进行了明确地说明。

> Note：
> 试着从迭代器的角度思考，这样的代码在很多情况下就显得十分优雅。不用担心性能，编译器会根据模板对迭代器相关的代码进行优化。

为了保证例子的简洁性，我们并没有对其做任何事情，不过要是作为斐波那契迭代器的发布库的话，其可用性还是比较差的——`fibit`传入一个参数的构造函数，可以直接使用`end`迭代器替换，因为`fibit`并没有包含任何一个合法的斐波那契值，这里的库并不强制使用这种方式。

还有些方面需要进行修复：

- 将`fibit(size_t i_)`声明为私有构造函数，并在`fibit`类中将`fib_range`类声明为一个友元类。这样用户就只能使用正确的方式进行迭代了。

- 可以使用迭代器哨兵，避免用户引用`end`迭代器。可以参考一下3.6节(使用哨兵终止迭代)中内容，以获得更多信息。
