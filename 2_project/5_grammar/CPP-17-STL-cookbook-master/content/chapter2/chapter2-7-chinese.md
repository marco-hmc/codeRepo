# 高效的修改std::map元素的键值

在`std::map`数据结构中，键-值通常都对应存在，而且键通常是唯一并排序过的，而且键值一旦设定那么就不允许用户再进行修改。为了阻止用户修改键，键的类型声明使用了`const`。

这种限制是非常明智的，其可以保证用户很难在使用`std::map`的时候出错。不过，如果我们真的需要修改`map`的键值该怎么办呢？

C++17之前，因为对应的键已经存在，我们不得不将整个键-值对从树中移除，然后再插入。这种方法的确定很明显，其需要分配出一些不必要的内存，感觉上也会对性能有一定的影响。

从C++17起，我们无需重新分配内存，就可以删除和重新插入map键值对。下面的内容中将会展示如何操作。

## How to do it...

我们使用`std::map`类型一个实现应用，用于确定车手在虚拟比赛中的排位。当车手在比赛中完成超越，那么我们将使用C++17的新方法改变其键值。

1. 包含必要的头文件和声明使用的命名空间。

   ```c++
   #include <iostream>
   #include <map>
   
   using namespace std;
   template <typename M>
   void print(const M &m)
   {
       cout << "Race placement:\n";
       for (const auto &[placement, driver] : m) {
      		cout << placement << ": " << driver << '\n';
       }
   }
   int main()
   {
       map<int, string> race_placement {
           {1, "Mario"}, {2, "Luigi"}, {3, "Bowser"},
           {4, "Peach"}, {5, "Yoshi"}, {6, "Koopa"},
           {7, "Toad"}, {8, "Donkey Kong Jr."}
       };
       print(race_placement);
   {
       auto a(race_placement.extract(3));
       auto b(race_placement.extract(8)); 
   	swap(a.key(), b.key());
       race_placement.insert(move(a));
       race_placement.insert(move(b));
   }
   ```

7. 最后，我们打印一下目前的排位。

   ```c++
   	print(race_placement);
   }
   ```

8. 编译并运行可以得到如下输出。我们可以看到初始的排位和最后的排位。

   ```c++
   $ ./mapnode_key_modification
   Race placement:
   1: Mario
   2: Luigi
   3: Bowser
   4: Peach
   5: Yoshi
   6: Koopa
   7: Toad
   8: Donkey Kong Jr.
   Race placement:
   1: Mario
   2: Luigi
   3: Donkey Kong Jr.
   4: Peach
   5: Yoshi
   6: Koopa
   7: Toad
   8: Bowser
   ```

## How it works...

在C++17中，`std::map`有一个新成员函数`extract`。其有两种形式：

```c++
node_type extract(const_iterator position);
node_type extract(const key_type& x)
```

在例子中，我们使用了第二个，能接受一个键值，然后找到这个键值，并提取对应的`map`节点。第一个函数接受一个迭代器，提取的速度会更快，应为给定了迭代器就不需要在查找。

当使用第二种方式去提取一个不存在的节点时，会返回一个空`node_type`实例。`empty()`成员函数会返回一个布尔值，用来表明`node_type`实例是否为空。以任何方式访问一个空的实例都会产生未定义行为。

提取节点之后，我们要使用`key()`函数获取要修改的键，这个函数会返回一个非常量的键。

需要注意的是，要将节点重新插会到`map`时，我们需要在`insert`中移动他们。因为`extract`可避免不必要的拷贝和内存分配。还有一点就是，移动一个`node_type`时，其不会让容器的任何值发生移动。

## There's more...

使用`extract`方法提取的`map`节点实际上非常通用。我们可以从一个`map`实例中提取出来节点，然后插入到另一个`map`中，甚至可以插入到`multimap`实例中。这种方式在`unordered_map`和`unordered_multimap`实例中也适用。同样在`set/multiset`和`unordered_set/unordered_multiset`也适用。

为了在不同`map`或`set`结构中移动元素，键、值和分配器的类型都必须相同。需要注意的是，不能将`map`中的节点移动到`unordered_map`中，或是将`set`中的元素移动到`unordered_set`中。

