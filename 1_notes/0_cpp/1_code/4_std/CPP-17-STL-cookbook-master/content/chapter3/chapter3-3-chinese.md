# 使用迭代适配器填充通用数据结构

大多数情况下，我们想要用数据来填充任何容器，不过数据源和容器却没有通用的接口。这种情况下，我们就需要人工的去编写算法，将相应的数据推入容器中。不过，这会分散我们解决问题的注意力。

不同数据结构间的数据传递现在可以只通过一行代码就完成，这要感谢STL中的**迭代适配器**。本节会展示如何使用迭代适配器。

## How to do it...

本节中，我们使用一些迭代器包装器，展示如何使用包装器，并了解其如何在编程任务中给予我们帮助。

   ```c++
   #include <iostream>
   #include <string>
   #include <iterator>
   #include <sstream>
   #include <deque>
   using namespace std;

   int main()
   {
       istream_iterator<int> it_cin {cin};
       istream_iterator<int> end_cin;

       deque<int> v;
       copy(it_cin, end_cin, back_inserter(v));	
   
   	istringstream sstr {"123 456 789"};

       auto deque_middle (next(begin(v),
       	 static_cast<int>(v.size()) / 2));

   	copy(istream_iterator<int>{sstr}, {}, inserter(v, deque_middle));

       initializer_list<int> il2 {-1, -2, -3};
       copy(begin(il2), end(il2), front_inserter(v));

       copy(begin(v), end(v), ostream_iterator<int>{cout, ", "});
       cout << '\n';
   }
   ```

10. 编译并运行，即有如下的输出。你能找到那些数字是由哪行的代码插入的吗？

    ```c++
    $ echo "1 2 3 4 5" | ./main
    -3, -2, -1, 1, 2, 123, 456, 789, 3, 4, 5,
    ```

## How it works...

本节我们使用了很多不同类型的迭代适配器。他们有一点是共同的，会将一个对象包装成迭代器。

**std::back_insert_iterator**

`back_insert_iterator`可以包装`std::vector`、`std::deque`、`std::list`等容器。其会调用容器的`push_back`方法在容器最后插入相应的元素。如果容器实例不够长，那么容器的容量会自动增长。

**std::front_insert_iterator**

`front_insert_iterator`和`back_insert_iterator`一样，不过`front_insert_iterator`调用的是容器的`push_front`函数，也就是在所有元素前插入元素。这里需要注意的是，当对类似于`std::vector`的容器进行插入时，其已经存在的所有元素都要后移，从而空出位置来放插入元素，这会对性能造成一定程度的影响。

**std::insert_iterator**

这个适配器与其他插入适配器类似，不过能在容器的中间位置插入新元素。使用`std::inserter`包装辅助函数需要两个参数。第一个参数是容器的实例，第二个参数是迭代器指向的位置，就是新元素插入的位置。

**std::istream_iterator**

`istream_iterator`是另一种十分方便的适配器。其能对任何`std::istream`使用(文件流或标准输入流)，并且可以根据实例的具体特化类型，对流进行分析。本节中，我们使用了`std::istram_iterator<int>(std::cin)`，其会将整数从标准输入中拉出来。

通常，对于流来说，其长度我们是不知道的。这就存在一个问题，也就是`end`迭代器指向的位置在哪里？对于流迭代器来说，它就知道相应的`end`迭代器的位置。这样就使得迭代器的比较更加高效，不需要通过遍历来完成。这样就是为什么`end`流迭代器不需要传入任何参数的原因。

**std::ostream_iterator**

`ostream_iterator`和`istream_iterator`类似，不过是用来进行输出的流迭代器。与`istream_iterator`不同在于，构造时需要传入两个参数，且第二个参数必须要是一个字符串，这个字符串将会在各个元素之后，推入输出流中。这样我们就能很容易的在元素中间插入逗号或者换行的符号，以便用户进行观察。