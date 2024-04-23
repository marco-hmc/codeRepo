# 标准算法的自动并行

## How to do it...

本节，将使用标准算法来完成一个程序。这个程序本身就是在模拟我们实际工作中的场景。当使用这些标准算法时，我们为了得到更快的性能，将执行策略嵌入其中：

1. 包含必要的头文件，并声明所使用的命名空间。其中`execution`头文件是C++17之后加入的：

   ```c++
   #include <iostream>
   #include <vector>
   #include <random>
   #include <algorithm>
   #include <execution>
   
   using namespace std;

   static bool odd(int n) { return n % 2; }

   int main()
   {
   	vector<int> d (50000000);

   	mt19937 gen;
   
   	uniform_int_distribution<int> dis(0, 100000);
   	auto rand_num ([=] () mutable { return dis(gen); }); 

   	generate(execution::par, begin(d), end(d), rand_num);

   	sort(execution::par, begin(d), end(d));

   	reverse(execution::par, begin(d), end(d));

   	auto odds (count_if(execution::par, begin(d), end(d), odd));

   	cout << (100.0 * odds / d.size())
   		<< "% of the numbers are odd.\n";
   }
   ```

10. 编译并运行程序，就能得到下面的输出。整个程序中我们就使用了一种执行策略，我们对不同执行策略之间的差异也是非常感兴趣。这个就留给读者当做作业。去了解一下不同的执行策略，比如`seq`，`par`和`par_vec`。 不过，对于不同的执行策略，我们肯定会得到不同的执行时间：

    ```c++
    $ ./auto_parallel
    50.4% of the numbers are odd.
    ```

## How it works...

本节并没有设计特别复杂的使用场景，这样就能让我们集中精力与标准库函数的调用上。并行版本的算法和标准串行的算法并没有什么区别。其差别就是多了一个参数，也就是执行策略。

让我们结合以下代码，来看三个核心问题：

```c++
generate(execution::par, begin(d), end(d), rand_num);
sort( execution::par, begin(d), end(d));
reverse( execution::par, begin(d), end(d));

auto odds (count_if(execution::par, begin(d), end(d), odd));
```

**哪些STL可以使用这种方式进行并行？**

69种存在的STL算法在C++17标准中，都可以使用这种方式进行并行，还有7种新算法也支持并行。虽然这种升级对于很多实现来说很伤，但是也只是在接口上增加了一个参数——执行策略参数。这也不是意味着我们总要提供一个执行策略参数。并且执行策略参数放在了第一个参数的位置上。

这里有69个升级了的算法。并且有7个新算法在一开始就支持了并发：

```c++
adjacent difference, adjacent find.
all_of, any_of, none_of
copy
count
equal
fill
find
generate
includes
inner product
in place merge, merge
is heap, is partitioned, is sorted
lexicographical_compare
min element, minmax element
mismatch
move
n-th element
partial sort, sort copy
partition
remove + variations
replace + variations
reverse / rotate
search
set difference / intersection / union /symmetric difference
sort
stable partition
swap ranges
transform
unique
```

详细的内容可以查看[C++ Reference](http://en.cppreference.com/w/cpp/experimental/parallelism/existing)。([参考页面](https://www.bfilipek.com/2017/08/cpp17-details-parallel.html))

这些算法的升级是一件令人振奋的事！如果我们之前的程序使用了很多的STL算法，那么就很容易的将这些算法进行并行。这里需要注意的是，这样的的改变并不意味着每个程序自动化运行N次都会很快，因为多核编程更为复杂，所要注意的事情更多。

不过，在这之前我们现在都会用`std::thread`，`std::async`或是第三方库进行复杂的并行算法设计，而现在我们可以以更加优雅、与操作系统不相关的方式进行算法的并行化。

**执行策略是如何工作的？**

执行策略会告诉我们的标准函数，以何种方式进行自动化并行。

`std::execution`命名空间下面，有三种策略类型：

| 策略                                                         | 含义                                                         |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| [sequenced_policy](https://zh.cppreference.com/w/cpp/algorithm/execution_policy_tag_t) | 算法使用串行的方式执行，这与原始执行方式没有什么区别。全局可用的实例命名为`std::execution::seq`。 |
| [parallel_policy](https://zh.cppreference.com/w/cpp/algorithm/execution_policy_tag_t) | 算法使用多线程的方式进行执行。全局可用的实例命名为`std::execution::par`。 |
| [parallel_unsequenced_policy](https://zh.cppreference.com/w/cpp/algorithm/execution_policy_tag_t) | 算法使用多线程的方式进行执行。并允许对代码进行向量化。在这个例子中，线程间可以对内存进行交叉访问，向量化的内容可以在同一个线程中执行。全局可用的实例命名为`std::execution::par_unseq`。 |

执行策略意味着我们需要进行严格限制。严格的约定，让我们有更多并行策略可以使用：

- 并行算法对所有元素的访问，必须不能导致死锁或数据竞争。
- 向量化和并行化中，所有可访问的函数不能使用任何一种阻塞式同步。

我们需要遵守这些规则，这样才不会将错误引入到程序中。

