# 使用元组快速构成数据结构

```c++
struct Foo {
  int a;
  string b;
  float c;
};
```

之前的章节中，为了替代定义结构体，我们可以定义一个元组：

```c++
using Foo = tuple<int, string, float>;
```

如要访问元组他的第一个类型变量，可以使用`std::get<0>(t)`，第二个类型变量为`std::get<1>(t)`，以此类推。

如果索引值过大，编译器会在编译时进行报错。

之前的章节中已经展示了C++17对元组的分解能力，允许我们使用如下的方式快速分解元素，并能对单独元素进行访问：

```c++
auto [a, b, c] = some_tuple
```

绑定和分解单个数据结构，只是元组能力之一。我们也可以想尽办法对元组进行连接和分割。本节中，我们将学习如何完成这样的任务。

## How to do it...

本节，我们将完成对任意元组进行打印的任务。另外，我们将完成一个函数，可以对元组进行zip操作：

1. 包含必要的头文件，并声明所使用的命名空间：

   ```c++
   #include <iostream>
   #include <tuple>
   #include <list>
   #include <utility>
   #include <string>
   #include <iterator>
   #include <numeric>
   #include <algorithm>
   
   using namespace std;

   template <typename T, typename ... Ts>
   void print_args(ostream &os, const T &v, const Ts &...vs)
   {
   	os << v;

   	(void)initializer_list<int>{((os << ", " << vs), 0)...};
   }

   template <typename ... Ts>
   ostream& operator<<(ostream &os, const tuple<Ts...> &t)
   {

   	auto print_to_os ([&os](const auto &...xs) {
   		print_args(os, xs...);
   	});
       os << "(";
       apply(print_to_os, t);
       return os << ")";
   }

   template <typename T>
   tuple<double, double, double, double>
   sum_min_max_avg(const T &range)
   {

       auto min_max (minmax_element(begin(range), end(range)));
       auto sum (accumulate(begin(range), end(range), 0.0));
       return {sum, *min_max.first, *min_max.second,
       		sum / range.size()};
   }
   
   template <typename T1, typename T2>
   static auto zip(const T1 &a, const T2 &b)
   {
   
       auto z ([](auto ...xs) {
           return [xs...](auto ...ys) {
           	return tuple_cat(make_tuple(xs, ys) ...);
           };
       });
   
    	return apply(apply(z, a), b);
    } 
   
    int main()
    {
        auto student_desc (make_tuple("ID", "Name", "GPA"));
        auto student (make_tuple(123456, "John Doe", 3.7)); 
   
    	cout << student_desc << '\n'
    		<< student << '\n';
   
    	cout << tuple_cat(student_desc, student) << '\n';
   
    	auto zipped (zip(student_desc, student));
    	cout << zipped << '\n';
   
        auto numbers = {0.0, 1.0, 2.0, 3.0, 4.0};
        cout << zip(
                make_tuple("Sum", "Minimum", "Maximum", "Average"),
                sum_min_max_avg(numbers))
            << '\n';
    }
    ```

17. 编译并运行程序，我们就会得到如下输出。前两行是`student`和`student_desc`元组的打印结果。第3行是使用`tuple_cat`组合后的输出结果。第4行是将学生元组进行`zip`后的结果。最后一行我们将会看到对应数字列表的和值、最小值、最大值和均值。因为有`zip`操作，我们可以清楚地了解这些数字的意义：

    ```c++
    $ ./tuple
    (ID, Name, GPA)
    (123456, John Doe, 3.7)
    (ID, Name, GPA, 123456, John Doe, 3.7)
    (ID, 123456, Name, John Doe, GPA, 3.7)
    (Sum, 10, Minimum, 0, Maximum, 4, Average, 2)
    ```

## How it works...

本节的有些代码的确比较复杂。我们对元组的`operator<<`操作符进行了重载实现，这样看起来比较复杂，但是这样就能对元组中的成员进行打印。然后我们实现`sum_min_max_avg`函数，其会返回一个元组。另外，`zip`应该是个比较复杂的函数。

这里最简单的函数是`sum_min_max_avg`。当我们定义一个函数`tuple<Foo, Bar, Baz> f()`时，我们可以将返回语句写成`return {foo_instance, bar_instance, baz_instance};`，这样函数将会自动的构建一个元组进行返回。如果你对`sum_min_max_avg`中所使用的STL函数有疑问，那可以回看一下第5章，其中有一些STL的基本函数操作。

其他较为复杂的部分，就是一些辅助函数：

**operator<< for tuples**

使用`operator<<`对输出流进行输出时，我们实现了`print_args`函数。其可以接受任意个参数，不过第一个参数必须是一个`ostream`实例：

```c++
template <typename T, typename ... Ts>
void print_args(ostream &os, const T &v, const Ts &...vs)
{
	os << v;
    
	(void)initializer_list<int>{((os << ", " << vs), 0)...};
}
```

这个函数打印的第一个元素是`v`，然后会将参数包`vs`中的元素进行打印。我们将第一个元素单独拎出来的原因是要使用逗号将所有元素进行分隔，但是我们不确定哪个参数是头或是尾(也就是要打印成“1, 2, 3”或是“,1, 2, 3”)。我们在第4章了解到使用Lambda表达式对`initializer_list`进行扩展，也就是[使用同一输入调用多个函数](content/chapter4/chapter4-5-chinese.md)这一节。这个函数，就能帮我们对元组进行打印。`operator<<`实现如下所示：

```c++
template <typename ... Ts>
ostream& operator<<(ostream &os, const tuple<Ts...> &t)
{
    auto capt_tup ([&os](const auto &...xs) {
    	print_args(os, xs...);
    });
    
    os << "(";
    apply(capt_tup, t);
    return os << ")";
}
```

首先我们定义了一个函数对象`capt_tup`。当我们调用`capt_tup(foo, ar, whatever)`时，其实际调用的是print_args(**os**, foo, bar, whatever)。这个函数只会做一件事，就是将可变列表中的参数输出到输出流对象`os`中。

之后，我们使用`std::apply`对元组`t`进行解包。如果这步看起来很复杂，那么可以看一下前一节，以了解`std::apply`的工作原理。

**元素的zip函数**

zip函数能够接收两个元组，虽然其实现很清晰，但是看起来还是异常复杂：

```c++
template <typename T1, typename T2>
auto zip(const T1 &a, const T2 &b)
{
    auto z ([](auto ...xs) {
        return [xs...](auto ...ys) {
        	return tuple_cat(make_tuple(xs, ys) ...);
        };
    });
    return apply(apply(z, a), b);
}
```

为了能更好的了解这段代码，我们可以假设有两个元组，一个元组a为(1, 2, 3)，另一个元组b为('a', 'b', 'c')。

例程中，我们调用了`apply(z, a)`，也就相当于调用函数`z(1, 2, 3)`，其会构造一个哈数对象将这些参数捕获后进行返回，这样1，2，3就被放入参数包`xs`中了。这里会再次调用，`apply(z(1, 2, 3), b)`，会将'a', 'b', 'c'放入参数包`ys`中。

Okay，现在`xs = (1, 2, 3)`，`ys = ('a', 'b', 'c')`，然后会发生什么呢？`tuple_cat(make_tuple(xs, ys) ...)`就会完成下图所描述的过程：

![](../../images/chapter8/8-5-1.png)

首先，`xs`和`ys`中的成员将会被zip到一起，也就是交叉配对在一起。这个交叉配对发生在`  make_tuple(xs, ys)... `部分，这会将两个元组组成一个元组。为了获得一个大元组，我们使用了`tuple_cat`，通过对元组的级联获取一个大的元组，其包含了所有元组中的成员，并进行了交叉配对。