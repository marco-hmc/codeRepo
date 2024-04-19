# 使用同一输入调用多个函数

## How to do it...

另一个使用一个函数调用，引发后续多个函数调用。我们的例子中，我们将使用不同的打印函数打印一些信息出来。

2. 这个函数可以接受任意数量的参数，并且返回一个Lambda表达式，这个Lambda表达式只接受一个参数。
3. 
4. 表达式可以通过这个参数调用所有已提供的函数。这样，我们可以定义`auto call_all (multicall(f, g, h))`函数对象，然后调用`call_all(123)`，从而达到同时调用`f(123); g(123); h(123); `的效果。这个函数看起来比较复杂，是因为我们需要一个语法技巧来展开参数包functions，并在`std::initializer_list`实例中包含一系列可调用的函数对象。

   ```c++
   template <typename ... Ts>
   static auto multicall (Ts ...functions)
   {
       return [=](auto x) {
           (void)std::initializer_list<int>{
           	((void)functions(x), 0)...
           };
       };
   }
   template <typename F, typename ... Ts>
   static auto for_each (F f, Ts ...xs) {
       (void)std::initializer_list<int>{
      		((void)f(xs), 0)...
       };
   }

   static auto brace_print (char a, char b) {
       return [=] (auto x) {
       	std::cout << a << x << b << ", ";
       };
   }

   int main()
   {
       auto f (brace_print('(', ')'));
       auto g (brace_print('[', ']'));
       auto h (brace_print('{', '}'));
       auto nl ([](auto) { std::cout << '\n'; });		

   	auto call_fgh (multicall(f, g, h, nl)); 
   	for_each(call_fgh, 1, 2, 3, 4, 5);
   }
   ```

10. 编译运行，我们应该能得到期望的结果：

   ```c++
   $ ./multicaller
   (1), [1], {1},
   (2), [2], {2},
   (3), [3], {3},
   (4), [4], {4},
   (5), [5], {5},
   ```

## How it works...

我们刚刚实现的辅助函数还是挺复杂的。我们使用了`std::initializer_list`来帮助我们展开参数包。为什么这里不用特殊的数据结构呢？再来看一下`for_each`的实现：

```c++
auto for_each ([](auto f, auto ...xs) {
    (void)std::initializer_list<int>{
    	((void)f(xs), 0)...
    };
});
```

这段代码的核心在于`f(xs)`表达式。`xs`是一个参数包，我们需要将其进行解包，才能获取出独立的参数，以便调用函数f。不幸的是，我们知道这里不能简单的使用`...`标记，写成`f(xs)...`。

所以，我能做的只能是构造出一个`std::initializer_list`列表，其具有一个可变的构造函数。表达式可以直接通过` return std::initializer_list<int>{f(xs)...};`方式构建，不过其也有缺点。在让我们看一下`for_each`的实现，看起来要比之前简单许多：

```c++
auto for_each ([](auto f, auto ...xs) {
	return std::initializer_list<int>{f(xs)...};
});
```

这看起来非常简单易懂，但是我们要了解其缺点所在：

1. 其使用f函数的所有调用返回值，构造了一个初始化列表。但我们并不关心返回值。
2. 虽然其返回的初始化列表，但是我们想要一个“即发即弃”的函数，这些函数不用返回任何东西。
3. f在这里可能是一个函数，因为其不会返回任何东西，可能在编译时就会被优化掉。

要想`for_each`修复上面所有的问题，会让其变的更加复杂。例子中做到了一下几点：

1. 不返回初始化列表，但会将所有表达式使用` (void)std::initializer_list<int>{...} `转换为`void`类型。
2. 初始化表达式中，其将`f(xs)...`包装进`(f(xs),0)...`表达式中。这会让程序将返回值完全抛弃，不过0将会放置在初始化列表中。
3. `f(xs)`在`(f(xs), 0)...`表达式中，将会再次转换成`void`，所以这里就和没有返回值一样。

这些不幸的事导致例程如此复杂丑陋，不过其能为所有可变的函数对象工作，并且不管这些函数对象是否返回值，或返回什么样的值。

这种技术可以很好控制函数调用的顺序，严格保证多个函数/函数对象以某种顺序进行调用。

> Note:
>
> 不推荐使用C风格的类型转换，因为C++有自己的转换操作。我们可以使用`reinterpret_cast<void>(expression) `代替例程中的代码行，不过这样会降低代码的可读性，会给后面的阅读者带来一些困扰。

