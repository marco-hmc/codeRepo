# 向std::map实例中高效并有条件的插入元素

我们需要用键值对填充一个`map`实例时，会碰到两种不同的情况：

1. 键不存在。创建一个全新的键值对。
2. 键已存在。修改键所对应的值。

我通常会使用`insert`或`emplace`函数对`map`插入新元素，如果插入不成功，那么就是第二种情况，就需要去修改现有的元素。`insert`和`emplace`都会创建一个新元素尝试插入到`map`实例中，不过在第二种情况下，这个新生成的元素会被扔掉。两种情况下，我们都会多余调用一次构造函数。

C++17中，添加了`try_emplace`函数，其只有在满足条件的情况下，才能插入新元素。让我们实现一个程序，建立一张表，列出各国亿万富翁的数量。我们例子中不会使用很大开销进行元素创建，不过我们的例子来源于生活，其能让你明白如何使用`try_emplace`。

## How to do it...

本节中，我们将实现一个应用，其能创建一张百万富翁的列表。这个列表中按国家区分，里面记录了各国富人的数量。

1. 包含头文件和声明命名空间。

   ```c++
   #include <iostream>
   #include <functional>
   #include <list>
   #include <map>

   using namespace std;

   struct billionaire {
       string name;
       double dollars;
       string country;
   };

   int main()
   {
       list<billionaire> billionaires {
           {"Bill Gates", 86.0, "USA"},
           {"Warren Buffet", 75.6, "USA"},
           {"Jeff Bezos", 72.8, "USA"},
           {"Amancio Ortega", 71.3, "Spain"},
           {"Mark Zuckerberg", 56.0, "USA"},
           {"Carlos Slim", 54.5, "Mexico"},
           // ...
           {"Bernard Arnault", 41.5, "France"},
           // ...
           {"Liliane Bettencourt", 39.5, "France"},
           // ...
           {"Wang Jianlin", 31.3, "China"},
           {"Li Ka-shing", 31.2, "Hong Kong"}
           // ...
       };
   	map<string, pair<const billionaire, size_t>> m;	
   	for (const auto &b : billionaires) {
   		auto [iterator, success] = m.try_emplace(b.country, b, 1);
       if (!success) {
           iterator->second.second += 1;
           }
       }
       for (const auto & [key, value] : m) {
           const auto &[b, count] = value;
           cout << b.country << " : " << count
          	     << " billionaires. Richest is "
                << b.name << " with " << b.dollars
                << " B$\n";
       }
   }
   ```

8. 编译并运行程序，就会得到下面的输出(这里的输出是不完整的，因为列表比较长)。

   ```
   $ ./efficient_insert_or_modify
   China : 1 billionaires. Richest is Wang Jianlin with 31.3 B$
   France : 2 billionaires. Richest is Bernard Arnault with 41.5 B$
   Hong Kong : 1 billionaires. Richest is Li Ka-shing with 31.2 B$
   Mexico : 1 billionaires. Richest is Carlos Slim with 54.5 B$
   Spain : 1 billionaires. Richest is Amancio Ortega with 71.3 B$
   USA : 4 billionaires. Richest is Bill Gates with 86 B$
   ```

## How it works...

本节围绕着`std::map`中的`try_emplace`函数展开，这个函数是C++17添加的。下面是其函数声明之一：

```c++
std::pair<iterator, bool> try_emplace(const key_type& k, Args&&... args);
```

其函数第一个参数`k`是插入的键，`args`表示这个键对应的值。如果我们成功的插入了元素，那么函数就会返回一个迭代器，其指向新节点在表中的位置，组对中布尔变量的值被置为true。当插入不成功，组对中的布尔变量值会置为false，并且迭代器指向与新元素冲突的位置。

这个特性在我们的例子中非常有用——可以完美处理第一次访问到，和之后访问到的情况。

> Note：
>
> `std::map`中`insert`和`emplace`方法完全相同。`try_emplace`与它们不同的地方在于，在遇到已经存在的键时，不会去构造组对。当相应对象的类型需要很大开销进行构造时，这对于程序性能是帮助的。

## There's more...

如果我们将表的类型从`std::map`换成`std::unordered_map`，程序照样能工作。这样的话，当不同类型的表具有较好的性能特性时，我们就可以快速的进行切换。例子中，唯一可观察到的区别是，亿万富翁表不再按字母顺序打印，因为哈希表和搜索树不同，其不会对对象进行排序。