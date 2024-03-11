# 使用Lambda为std::function添加多态性

我们现在想编写一些观察函数，用来观察一些变量的变化，当相应变量的数值发生改变时会进行提示，比如气压仪或是股票软件这类的东西。当有些值发生变化时，对应的观察对象就会被调用，之后以对应的方式进行反应。

为了实现这个观察器，我们存储了一些相关的函数对象在一个`vector`中，这些函数都接受以`int`变量作为参数，这个参数就是观察到的值。 我们不清楚这些函数对于传入值会做什么特殊的处理，不过我们也没有必要知道。

那么`vector`中的函数对象类型是什么呢？`std::vector<void (*)(int)>`，只要函数声明成`void f(int)`就符合这个这个函数指针类型的定义。这对于Lambda表达式同样有效，不过Lambda表达就是不能捕获任何值了——` [](int x) {...} `。对于捕获列表来说，Lambda表达式确实和普通的函数指针不同，因为其就不是一个函数指针，是一个函数对象，也就是将很多数据耦合到一个函数当中！想想在C++11时代之前，C++中没有Lambda表达式，类和结构体通常会将数据和函数耦合在一起，并且当你修改一个类中的数据成员时，你得到的是一个完全不同类型的数据。

这样`vector`中就无法将使用同样类型名字的不同类别的对象存储在一起。不能捕获已存在的变量，这个限制对于用户来说非常的不友好，也限制了代码的使用范围。用户该如何保存不同类型的函数对象呢？对接口进行约束，采用特定的传参方式传入已经观察到的值？

本节中，我们将展示使用`std::function`来解决这个问题，其将扮演一个“Lambda表达式多态包装器”的角色，捕获列表是不是空的都没有关系。

## How to do it...

本节我们将创建很多Lambda表达式，其捕获类型是完全不同的，但是其函数签名的类型是相同的。然后，使用`std::function`将这些函数对象存入一个`vector`：

1. 包含必要的头文件：

    ```c++
    #include <iostream>
    #include <deque>
    #include <list>
    #include <vector>
    #include <functional>

   template <typename C>
   static auto consumer (C &container){
       return [&] (auto value) {
       	container.push_back(value);
       };
   }
   
   template <typename C>
   static void print (const C &c)
   {
       for (auto i : c) {
       	std::cout << i << ", ";
       }
       std::cout << '\n';
   }

   int main()
   {
       std::deque<int> d;
       std::list<int> l;
       std::vector<int> v;

       const std::vector<std::function<void(int)>> consumers
       	{consumer(d), consumer(l), consumer(v)};
       for (size_t i {0}; i < 10; ++i) {
           for (auto &&consume : consumers) {
           	consume(i);
           }
       }
       print(d);
       print(l);
       print(v);
   }
   ```

8. 编译运行程序，就会看到如下输出，和我们的期望是一样的。

   ```c++
   $ ./std_function
   0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
   0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
   0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
   ```

## How it works...

本节中比较复杂的地方就是这一行：

```c++
const std::vector<std::function<void(int)>> consumers
	{consumer(d), consumer(l), consumer(v)};
```

d，l和v对象都包装进一个`consumer(...)`调用中。这个调用会返回多个函数对象，这样每个函数对象都能捕获这三个容器实例。虽然函数对象只能接受`int`型变量为参数，但是其捕获到的是完全不同的类型。这就将不同类型的A、B和C变量存入到一个`vector`中一样。

为了这个功能，需要找到一个共同的类型，也就是能保存不同类型的函数对象，这个类型就是`std::function`。一个`std::function<void(int)>`对象可以存储我们的函数对象或传统函数，其接受只有一个整型参数和返回为空的函数类型。这里使用了多态性，为函数类型进行解耦。思考如下的写法：

```c++
std::function<void(int)> f (
	[&vector](int x) { vector.push_back(x); });
```

这里有个函数对象，将Lambda表达式包装入`std::function`对象当中，当我们调用`f(123)`时，会产生一个虚函数调用，其会重定向到对象内部的实际执行函数。

当存储函数对象时，`std::function`就显得非常智能。当我们使用Lambda表达式捕获越来越多的变量时，`std::function`实例的体积也会越来越大。如果对象体积特别特别巨大，那么其将会在堆上分配出对应内存空间来存放这个函数对象。这些对于我们代码的功能性并没有什么影响，这里需要让你了解一下是因为这样的存储方式会对性能有一定的影响。

> Note:
>
> 很多初学者都认为或希望`std::function<...>`的实际表达类型是一个Lambda表达式。不过这是错误的理解！因为有多态库的帮助，其才能将Lambda表达式进行包装，从而抹去类型的差异。
