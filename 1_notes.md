



# 下一步

现在你已经了解了系统设计的基础知识，以下是一些额外的资源：

- [分布式系统](https://www.youtube.com/watch?v=UEAMfLPZZhE&list=PLeKd45zvjcDFUEv_ohr_HdUFe97RItdiB)（由 Dr. Martin Kleppmann 主讲）
- [系统设计面试：内部指南](https://www.amazon.in/System-Design-Interview-insiders-Second/dp/B08CMF2CQF)
- [微服务](https://microservices.io)（由 Chris Richardson 主讲）
- [无服务器计算](https://en.wikipedia.org/wiki/Serverless_computing)
- [Kubernetes](https://kubernetes.io)

还建议积极关注那些在大规模实践中应用我们在课程中学到的知识的公司的工程博客：

- [Microsoft Engineering](https://engineering.microsoft.com)
- [Google Research Blog](http://googleresearch.blogspot.com)
- [Netflix Tech Blog](http://techblog.netflix.com)
- [AWS Blog](https://aws.amazon.com/blogs/aws)
- [Facebook Engineering](https://www.facebook.com/Engineering)
- [Uber Engineering Blog](http://eng.uber.com)
- [Airbnb Engineering](http://nerds.airbnb.com)
- [GitHub Engineering Blog](https://github.blog/category/engineering)
- [Intel Software Blog](https://software.intel.com/en-us/blogs)
- [LinkedIn Engineering](http://engineering.linkedin.com/blog)
- [Paypal Developer Blog](https://medium.com/paypal-engineering)
- [Twitter Engineering](https://blog.twitter.com/engineering)


# References

- [IBM Blogs](https://www.ibm.com/blogs)
- [Fastly Blogs](https://www.fastly.com/blog)
- [NS1 Blogs](https://ns1.com/blog)
- [Grokking the System Design Interview](https://www.designgurus.io/course/grokking-the-system-design-interview)
- [Grokking Microservices Design Patterns](https://www.designgurus.io/course/grokking-microservices-design-patterns)
- [System Design Primer](https://github.com/donnemartin/system-design-primer)
- [AWS Blogs](https://aws.amazon.com/blogs)
- [Architecture Patterns by Microsoft](https://learn.microsoft.com/en-us/azure/architecture/patterns)
- [Martin Fowler](https://martinfowler.com)
- [PagerDuty resources](https://www.pagerduty.com/resources)
- [VMWare Blogs](https://blogs.vmware.com/learning)



dom 解析和流式解析两种

- cygwin 是是什么？
- gflw 是什么？
- downDemo github

- 继承的析构函数一般要怎么处理？继承的特殊成员函数怎么处理？

有两个同名函数 func()，形参分别是 Foo 类型指针和 Bar 类型指针，Bar 类型是 Foo 类型的派生类。
如果有一个 Foo \*bar = new Bar(); 调用 func(bar)，调用的是那一个方法？

- 如何避免代码膨胀？
- 交互
  - 操作系统到 qt 到 bim
- bim 的架构
- bim 的命令调度
- bim 的显示
  - bim 的不同视图下的 ctp 数据差异体现在哪里
- bim 的构件类型
- 多线程开发指南
- 重生成
- 模型数据
  - viewItem
  - docItem
  - ctp
    https://confluence.zwcad.com/pages/viewpage.action?pageId=60720467

* 模型编辑
  - 自己
    - 预览模式
  - 重生成
* 模型显示
  - graphics
* undo 实现
* 离线配置
* 特征/ 永久命名概念
*

* 如果有一个全局变量存在，最后是提供统一的操作函数接口。哪怕是一个 int 的++操作也通过函数封装起来，这样可以方便调试。
* 知道哪些地方修改过。不然这个状态无法追踪在哪里被修改了。

#### 8. 设计 class 犹如设计 type

- 新的 class 对象应该被如何创建和构造
- 对象的初始化和赋值应该有什么样的差别(不同的函数调用,构造函数和赋值操作符)
- 新的 class 如果被 pass by value(以值传递),意味着什么(copy 构造函数)
- 什么是新 type 的"合法值"(成员变量通常只有某些数值是有效的,这些值决定了 class 必须维护的约束条件)
- 新的 class 需要配合某个继承图系么(会受到继承类的约束)
- 新的 class 需要什么样的转换(和其他类型的类型变换)
- 什么样的操作符和函数对于此 type 而言是合理的(决定声明哪些函数,哪些是成员函数)
- 什么样的函数必须为 private 的
- 新的 class 是否还有相似的其他 class,如果是的话就应该定义一个 class template
- 你真的需要一个新 type 么?如果只是定义新的 derived class 或者为原来的 class 添加功能,说不定定义 non-member 函数或者 templates 更好

比如内存映射，调用栈，同步对象等，连同公司本身的业务都需要有一定的了解。

### not re-organized

7、实现一个建议内存池
如何实现 cpp 的新 feature 比如协程?
如何用 c 实现 template?

---

模板，模板特化，SFINAE，type_traits，形参包，
结构化绑定及其手搓，具名要求，迭代器 trait，值类别，左右值、泛左值(glvalue)、

纯右值(prvalue)，移动语义，转发引用(俗称万能引用)，std::forward<T>()完美转发，RAII，表达式求值，弃值表达式，不求值表达式，潜在求值表达式，常量表达式，临时量实质化(C++17)，标准布局类，用元编程实现 constexpr 编译期算法(如编译期汉诺塔，编译期递归，拼接字符数组，打函数表)，用户定义字面量，构造函数异常处理，函数 try 块，模块，全局模块片段及其存在的意义，模块分区，在 CMake 工程中声明模块范围库(范围适配器，定制点对象(CPO)，niebloid，ADL 实参依赖查找，常见的范围工厂，视图，老式迭代器对和新式迭代器+哨位概念的对比)，可变仿引用对象的 operator= 成员必须带 const 限定的依据，奇特重现模板模式(CRTP)以及其在 C++20 范围适配器中的应用概念库，requires 子句，约束的归入(subsume)，约束的偏序，concept，原子约束，约束规范化过程，范围库中常用的 concept(可间接写入，可间接读取)协程，协程 promise_type，挂起点，等待体，范围生成器，协程抛异常，格式化器特化，基本格式化器，格式串格式，显式对象形参(C++23)

---

5.哈希表
对哈希表的细节要求很高，比如哈希表的冲突；
Linux 系统下可能还会问什么是 daemon 进程，如何产生 daemo 进程，什么是僵尸进程，僵尸进程如何产 生和消除(bilibili 问过)突检测、哈希函数常用实现、算法复杂度;比如百度二面就让我写一个哈希表插入元素算法，元素类型是任意类型，

1. AVL 树和 B 树的概念、细节。
   例如会问 mysql 数据库的索引的实现原理，基本上就等于问你 B 树了
   红黑树、b+树

---

3.操作系统原理性的东西
Linux 下 elf 文件的节结构，映射到进程地址空间后分别对应哪些段
相关的问题还有，全局变量、静态存储在进程地址空间的哪里;
堆和栈的区别，栈的结构，栈的细节一点要搞的特别清楚，因为一些对技术要求比较高的公司会问的比较深入，例如京东的一面是让我先写一个从 1 加到 100 的求和函数，然后让我写出这个函数的汇编代码，如果你对栈的结构(如函数参数入栈顺序、函数局部变量在栈中的布局、栈帧指针和栈顶指针位置)不熟悉的话，这题目就无法答对了:
栈的问题，可能会以常见的函数调用方式来提问，常见的函数调用有如下 cdecl/stdcal/ thiscal/ fastcall 的区别，比如像 printf 这样具有不定参数的函数为什么不能使用 stdcall;
饿了么二面问了操作系统的保护模式实模式 9，中断向量表，Linux 下的 CAS,
以上这些问题的答案，《程序员的自我修养 9:链接、装载与库》这本程序员必读书只中都有。感谢某位网友的分享:

如果希望一个类 B 不可以被继承，首先得让 B 继承自 A，A 的构造函数是私有化，但声明 B 是 A 的友元，因此 B 能够正常构造，但是当 C 继承 B 的时候，C 就不能调用 A 的构造。 从而使得 C 不可被构造，是这个意思吗？

图形学，游戏服务器，网络通讯架构，虚拟现实，嵌入式系统，设备驱动，音频视频，ai 底层。
网络通讯架构能够拿到这个月薪；

std::variant + std::visit

```cpp
std::optional<std::reference_wrapper<int>> get(size_t index);

auto x = **vec.get(3);         // 性能读
auto x = *vec.get(3).value();  // 安全读
*vec.get(3) = 42;              // 性能写
vec.get(3).value() = 42;       // 安全写
```

C++17 的 CTAD 语法

## insert 不会替换现有值

```cpp
map<string, int> table;
table.insert({"小彭老师", 24});
table.insert({"小彭老师", 42});
```

这时，`table["小彭老师"]` 仍然会是 24，而不是 42。因为 insert 不会替换 map 里已经存在的值。

## insert 不会替换现有值

（避免不必要的构造？）

```cpp
map<string, int> table;
table["小彭老师"] = 24;
table["小彭老师"] = 42;
```

C++17 提供了比 `[]` 运算符更适合覆盖性插入的 insert_or_assign 函数：

```cpp
map<string, int> table;
table.insert_or_assign("小彭老师", 24);
table.insert_or_assign("小彭老师", 42);
```

## 高效删除 vector 元素

back swap erase

lower_bound

模板元编程的时候要明白，c++编译器能处理的是类型, 常量。
为了扩展能力，这些概念在编译器下都需要进一步发展。

- 类型
  - 类 traits，类型能够特化和偏特化，
- 常量
  - 字面量/ 常量表达式/
    编译器没有变量的概念。

一些实时性要求很高的领域就不能用 unordered_map。

一门编程语言需要提供以下基本能力，以便开发者能够编写功能丰富、灵活且高效的程序：

1. 数据表示和操作
2. 条件判断能力（if）
3. 循环能力（loop）
4. 变量和常量
5. 函数和过程
6. 输入和输出
7. 错误处理
8. 模块化和命名空间
9. 面向对象编程（OOP）
10. 并发和并行

> 模板函数实现多态的解决方案是有的，那就是 std::variant + std::visit，但那是更后来出现的函数式设计模式了，今天我们先把面向对象学明白了再说。

内建函数是和机器指令直接相关的，不会产生函数调用。

编译器之所以能够实现所谓的“开洞”行为，主要是因为它在编译过程中对源代码有深入的理解和控制。编译器的工作流程大致可以分为以下几个阶段：

1. **预处理（Preprocessing）**：

   - 处理预处理指令，如宏定义的展开、条件编译指令、头文件的包含等。这一阶段，编译器会根据预处理指令修改源代码。

2. **词法分析（Lexical Analysis）**：

   - 将源代码分解成一系列的标记（Tokens），如关键字、标识符、字面量等。

3. **语法分析（Syntax Analysis）**：

   - 根据语言的语法规则，将标记序列组织成抽象语法树（Abstract Syntax Tree, AST）。

4. **语义分析（Semantic Analysis）**：

   - 检查 AST 中的语义错误，如类型不匹配、未定义的标识符等，并生成中间表示（Intermediate Representation, IR）。

5. **优化（Optimization）**：

   - 对 IR 进行优化，以提高程序的性能或减少资源消耗。这一阶段，编译器会利用其对程序结构和语义的深入理解来执行各种优化。

6. **代码生成（Code Generation）**：

   - 将优化后的 IR 转换成目标代码，可能是汇编代码或直接的机器代码。

7. **链接（Linking）**：
   - 将编译生成的目标代码与库文件和其他模块链接在一起，生成可执行文件。

编译器能够实现“开洞”行为的关键因素包括：

- **全局视角**：编译器可以看到整个源代码，因此可以进行全局优化和分析，而用户代码只能看到局部。

- **语言和平台特性**：编译器了解目标编程语言的规范和特性，以及目标平台的硬件特性，因此可以利用这些信息进行优化。

- **控制编译过程**：编译器控制着从源代码到目标代码的整个转换过程，可以在任何阶段插入特殊的处理逻辑。

- **访问底层信息**：编译器可以访问底层的硬件和操作系统信息，这使得它能够生成针对特定平台优化的代码。

- **编译器扩展和内置函数**：编译器通常提供一些特殊的内置函数和扩展，这些是专门为编译器设计的，用户代码无法直接使用。

通过这些能力，编译器能够在编译过程中实现那些用户代码难以或无法实现的特殊功能。

哑元表

```c++
#pragma omp parallel for default(shared) firstprivate(eps)  private(c, j)
    for (int i = 0; i < N_POINTS; i++) {
        for (int j = 0; j < N_POINTS; j++) {
            c.r = -2.0 + 2.5 * (double)(i) / (double)(N_POINTS) + eps;
            c.i = 1.125 * (double)(j) / (double)(N_POINTS) + eps;
            testpoint(c);
        }
    }
```
傅里叶变化，可以将一个任意曲线函数，转成若干个三角函数表示对吗？
然后如果一个曲线函数是有限时间域内的，就可以转成频域的多个三个函数内。

std::mem_fn 的实现

https://hansimov.gitbook.io/csapp/part1/ch04-processor-architecture
https://github.com/CDDSCLab/training-plan?tab=readme-ov-file




# 地理哈希和四叉树

## 地理哈希

地理哈希是一种用于将地理坐标（如纬度和经度）编码为短的字母数字字符串的[地理编码](https://en.wikipedia.org/wiki/Address_geocoding)方法。它由 [Gustavo Niemeyer](https://twitter.com/gniemeyer) 于 2008 年创建。

例如，坐标为 `37.7564, -122.4016` 的旧金山可以用地理哈希表示为 [`9q8yy9mf`]。

### 地理哈希如何工作？

地理哈希是一种分层空间索引，使用 Base-32 字母编码。地理哈希的第一个字符将初始位置标识为 32 个单元格之一。这个单元格还包含 32 个单元格。这意味着要表示一个点，世界会随着每个附加位递归地划分为越来越小的单元格，直到达到所需的精度。精度因子还决定了单元格的大小。

![geohashing](https://raw.githubusercontent.com/karanpratapsingh/portfolio/master/public/static/courses/system-design/chapter-IV/geohashing-and-quadtrees/geohashing.png)

地理哈希保证如果地理哈希共享更长的前缀，则点在空间上更接近，这意味着字符串中的字符越多，位置越精确。例如，地理哈希 [`9q8yy9mf`] 和 [`9q8yy9vx`]. 在空间上更接近，因为它们共享前缀 [`9q8yy9`]."。

地理哈希还可以用于提供一定程度的匿名性，因为我们不需要暴露用户的确切位置，因为根据地理哈希的长度，我们只知道他们在某个区域内。

不同长度的地理哈希的单元格大小如下：

| 地理哈希长度 | 单元格宽度 | 单元格高度 |
| -------------- | ---------- | ----------- |
| 1              | 5000 公里  | 5000 公里   |
| 2              | 1250 公里  | 1250 公里   |
| 3              | 156 公里   | 156 公里    |
| 4              | 39.1 公里  | 19.5 公里   |
| 5              | 4.89 公里  | 4.89 公里   |
| 6              | 1.22 公里  | 0.61 公里   |
| 7              | 153 米     | 153 米      |
| 8              | 38.2 米    | 19.1 米     |
| 9              | 4.77 米    | 4.77 米     |
| 10             | 1.19 米    | 0.596 米    |
| 11             | 149 毫米   | 149 毫米    |
| 12             | 37.2 毫米  | 18.6 毫米   |

### 用例

以下是地理哈希的一些常见用例：

- 它是一种在数据库中表示和存储位置的简单方法。
- 它也可以作为 URL 在社交媒体上共享，因为它比纬度和经度更容易共享和记住。
- 我们可以通过非常简单的字符串比较和高效的索引搜索来高效地找到一个点的最近邻居。

### 示例

地理哈希被广泛使用，并且被流行的数据库支持。

- [MySQL](https://www.mysql.com)
- [Redis](http://redis.io)
- [Amazon DynamoDB](https://aws.amazon.com/dynamodb)
- [Google Cloud Firestore](https://cloud.google.com/firestore)

## 四叉树

四叉树是一种树数据结构，其中每个内部节点恰好有四个子节点。它们通常用于通过递归将二维空间划分为四个象限或区域来进行分区。每个子节点或叶节点存储空间信息。四叉树是 [八叉树](https://en.wikipedia.org/wiki/Octree) 的二维类比，八叉树用于分区三维空间。

![quadtree](https://raw.githubusercontent.com/karanpratapsingh/portfolio/master/public/static/courses/system-design/chapter-IV/geohashing-and-quadtrees/quadtree.png)

### 四叉树的类型

四叉树可以根据它们表示的数据类型进行分类，包括区域、点、线和曲线。以下是一些常见的四叉树类型：

- 点四叉树
- 点区域 (PR) 四叉树
- 多边形地图 (PM) 四叉树
- 压缩四叉树
- 边四叉树

### 为什么我们需要四叉树？

仅使用纬度和经度不够吗？为什么我们需要四叉树？虽然理论上使用纬度和经度我们可以通过[欧几里得距离](https://en.wikipedia.org/wiki/Euclidean_distance)确定点之间的距离，但对于实际用例来说，由于其对大数据集的 CPU 密集性，这种方法并不具有可扩展性。

![quadtree-subdivision](https://raw.githubusercontent.com/karanpratapsingh/portfolio/master/public/static/courses/system-design/chapter-IV/geohashing-and-quadtrees/quadtree-subdivision.png)

四叉树使我们能够高效地在二维范围内搜索点，这些点定义为纬度/经度坐标或笛卡尔 (x, y) 坐标。此外，我们可以通过仅在达到某个阈值后细分节点来节省进一步的计算。通过应用诸如 [Hilbert 曲线](https://en.wikipedia.org/wiki/Hilbert_curve) 之类的映射算法，我们可以轻松提高范围查询性能。

### 用例

以下是四叉树的一些常见用例：

- 图像表示、处理和压缩。
- 空间索引和范围查询。
- 基于位置的服务，如 Google 地图、Uber 等。
- 网格生成和计算机图形学。
- 稀疏数据存储。


# SLA、SLO、SLI

让我们简要讨论一下 SLA、SLO 和 SLI。这些主要与业务和站点可靠性相关，但了解它们仍然很有用。

## 为什么它们很重要？

SLA、SLO 和 SLI 允许公司定义、跟踪和监控对用户服务的承诺。SLA、SLO 和 SLI 应该帮助团队在其服务中生成更多的用户信任，并强调对事件管理和响应过程的持续改进。

## SLA

SLA，即服务级别协议，是公司与其服务用户之间达成的协议。SLA 定义了公司对用户在特定指标（如服务可用性）方面做出的不同承诺。

_SLA 通常由公司的业务或法律团队编写。_

## SLO

SLO，即服务级别目标，是公司对用户在特定指标（如事件响应或正常运行时间）方面做出的承诺。SLO 存在于 SLA 中，作为完整用户协议中的单个承诺。SLO 是服务必须满足的具体目标，以符合 SLA。SLO 应始终简单、明确定义且易于衡量，以确定目标是否得到实现。

## SLI

SLI，即服务级别指标，是用于确定 SLO 是否得到满足的关键指标。它是 SLO 中描述的指标的测量值。为了保持对 SLA 的遵守，SLI 的值必须始终达到或超过 SLO 确定的值。