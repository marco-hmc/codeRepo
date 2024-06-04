* 为什么stl中的内存分配器要设计为一个模板参数而不是一个构造函数参数?

### 内存空间

### Lambda capture initializers
The name given to the captured value does not need to be related to any variables in the enclosing scopes and introduces a new name inside the lambda body. 
The initializing expression is evaluated when the lambda is _created_ (not when it is _invoked_).
```c++
int factory(int i) { return i * 10; }
auto f = [x = factory(2)] { return x; }; // returns 20

auto generator = [x = 0] () mutable {
  // this would not compile without 'mutable' as we are modifying x on each call
  return x++;
};
auto a = generator(); // == 0
auto b = generator(); // == 1
auto c = generator(); // == 2
```
Because it is now possible to _move_ (or _forward_) values into a lambda that could previously be only captured by copy or reference we can now capture move-only types in a lambda by value. 

Note that in the below example the `p` in the capture-list of `task2` on the left-hand-side of `=` is a new variable private to the lambda body and does not refer to the original `p`.

```c++
auto p = std::make_unique<int>(1);

auto task1 = [=] { *p = 5; }; // ERROR: std::unique_ptr cannot be copied
// vs.
auto task2 = [p = std::move(p)] { *p = 5; }; // OK: p is move-constructed into the closure object
// the original p is empty after task2 is created
```
Using this reference-captures can have different names than the referenced variable.
```c++
auto x = 1;
auto f = [&r = x, x = x * 10] {
  ++r;
  return r + x;
};
f(); // sets x to 2 and returns 12
```


### Compile-time integer sequences
The class template `std::integer_sequence` represents a compile-time sequence of integers. There are a few helpers built on top:
* `std::make_integer_sequence<T, N>` - creates a sequence of `0, ..., N - 1` with type `T`.
* `std::index_sequence_for<T...>` - converts a template parameter pack into an integer sequence.

Convert an array into a tuple:
```c++
template<typename Array, std::size_t... I>
decltype(auto) a2t_impl(const Array& a, std::integer_sequence<std::size_t, I...>) {
  return std::make_tuple(a[I]...);
}

template<typename T, std::size_t N, typename Indices = std::make_index_sequence<N>>
decltype(auto) a2t(const std::array<T, N>& a) {
  return a2t_impl(a, Indices());
}
```


### Ref-qualified member functions
Member functions can now be qualified depending on whether `*this` is an lvalue or rvalue reference.

```c++
struct Bar {
  // ...
};

struct Foo {
  Bar getBar() & { return bar; }
  Bar getBar() const& { return bar; }
  Bar getBar() && { return std::move(bar); }
private:
  Bar bar;
};

Foo foo{};
Bar bar = foo.getBar(); // calls `Bar getBar() &`

const Foo foo2{};
Bar bar2 = foo2.getBar(); // calls `Bar Foo::getBar() const&`

Foo{}.getBar(); // calls `Bar Foo::getBar() &&`
std::move(foo).getBar(); // calls `Bar Foo::getBar() &&`

std::move(foo2).getBar(); // calls `Bar Foo::getBar() const&&`
```

引用绑定到临时对象的规则:
右值引用: 当使用右值引用(&&)绑定到返回的右值(例如函数返回的临时对象)时,编译器会延长右值的生命周期,使得引用继续有效.

cpp
Copy code
const T& constRef = getTemporary();  // const 引用绑定到临时对象
为什么需要引用绑定到临时对象:
避免不必要的拷贝: 当函数返回临时对象时,使用引用绑定可以避免不必要的拷贝构造,提高性能.

允许延迟析构: 通过延长临时对象的生命周期,允许在整个语句块中使用临时对象,而不会在引用失效时导致未定义行为.

* ***UniquePtr(const UniquePtr &) = delete;禁用拷贝构造***
    拷贝构造函数的参数通常是常量引用(const reference),而不是值(value),主要有以下两个原因:

1. **性能**:当参数是值时,会创建该对象的一个新的副本,这涉及到对象的复制操作,可能会消耗大量的时间和内存.特别是当对象较大时,复制的代价会非常高.而当参数是常量引用时,只需要传递引用,不需要复制对象,因此性能更高.

2. **避免无限递归**:如果拷贝构造函数的参数是值,那么在调用拷贝构造函数时,需要先创建一个新的对象,这又需要调用拷贝构造函数,从而形成无限递归,导致程序崩溃.而当参数是常量引用时,不会触发拷贝构造函数,因此可以避免无限递归.

所以,拷贝构造函数的参数通常是常量引用,而不是值.

* **一个new出来的指针,被delete两次会怎么样**
如果一个指针被`delete`两次,会导致未定义行为(Undefined Behavior).这是因为在第一次`delete`后,该指针已经不再指向有效的内存区域,再次尝试`delete`就是对无效内存的操作,这是非法的.

未定义行为可能会导致各种各样的问题,包括但不限于:

- 程序崩溃
- 数据损坏
- 难以预测和解释的行为

为了避免这种情况,你应该确保每个`new`操作都有一个对应的`delete`操作,并且每个`delete`操作都只执行一次.在你的代码中,`UniquePtr`类就是通过封装`new`和`delete`操作来确保资源的正确管理,避免了这种问题.

* ***为什么delete之后,都会设置nullptr***

在C++中,`delete`一个指针后,通常会将其设置为`nullptr`,主要有以下几个原因:

1. **避免悬挂指针**:`delete`一个指针后,该指针就变成了悬挂指针(Dangling Pointer),它不再指向有效的内存区域,但仍然保留了原来的地址值.如果你试图再次使用这个悬挂指针,就会导致未定义行为.将指针设置为`nullptr`可以避免这种情况,因为`nullptr`是一个特殊的指针值,表示该指针不指向任何对象.

2. **安全地重复`delete`**:在C++中,`delete`一个`nullptr`是安全的,不会有任何效果.所以,如果你将一个指针设置为`nullptr`,就可以安全地重复`delete`它,而不会导致未定义行为.

3. **检查指针是否已经被`delete`**:如果你将一个指针设置为`nullptr`,就可以通过检查该指针是否为`nullptr`来判断它是否已经被`delete`.

所以,`delete`一个指针后,通常会将其设置为`nullptr`,以提高程序的安全性和稳定性.


* ***基类析构函数要是虚函数***
    如果不是虚函数的话,可能会有内存泄漏的问题
    如果你有一个基类指针指向一个派生类对象:
    ```c++
    Copy code
    Base* ptr = new Derived();
    delete ptr; // 这里会首先调用Derived的析构函数,然后调用Base的析构函数
    ```
    如果基类的析构函数不是虚函数,那么只会调用基类的析构函数,而Derived的析构函数将不会被调用,可能导致资源泄漏.

* ***vector问题***
    尽量不要在vector中存放bool类型,vector为了做优化,它的内部存放的其实不是bool.

* ***vector删除***
```c++
    std::vector<int> vec(1000000, 42);  // 创建一个包含1000000个元素的vector,并初始化为42
    vec.clear();  // 使用clear方法清空vector,但容量仍然是1000000
    // 在这之后,vec仍然占用着大量内存,即使已经没有实际的元素

    std::vector<int>().swap(vec);  // 使用swap方法将一个新的空vector与vec交换
```


算法
1/计算表达式 (改成后缀表达式进行处理)
2/朋友圈问题,求总共有多少个朋友圈 (使用并查集)
3/一个数组找中位数(通过快排思想,常数级的若干次求position,直到恰好是中心,时间复杂度是O(n),如果是海量数据呢2g数据,500内存如何处理?->hash之后分成小文件,再外部排序,使用归并,可以使用最大堆,直到数据过半)

编程/算法
1/一个文件无序存放了1w个数字,每行1个.数字范围1-1w,现在随机删除2个数字.请把他们2个找出来.
答:使用hash数组,遍历文件,每遍历到一个数字,就以该数字为下标的数组元素置1,不用加1,因为数字不重复的.最后再遍历一遍数组,值为0的元素的下标就是所求数字.

2/如何对你申请的内存进行优化?
答:可以使用bitmap,每一bit可以代表一个数字,这样可以压缩内存.

3/压缩率是多少?
答:每个bit一个数字,而之前数组一个元素是int类型的,占32位,所以压缩率是32倍.

4/什么场景用bitmap?
答:我说数据较为密集,而且你这里数据是连续不重复,就符合,而且你的数据是有范围的.

5/如果数据有重复呢?
答:可以使用2-bitmap,00代表不出现,01代表出现1次,10代表出现2次,11表示无定义,这样遍历一遍就可以找到是哪几个数字
他回答:不是,比如数字3,具体有多少出现,这个这需要知道的. 我说:10bit可以表示的数是1024,而你每个数字不可能超过1w次.所以要记录次数的话,就还是用bitmap但是不是1位,大概1个数用14bit吧,但相比32位一个数要好些.


笔试:
特殊链表(每个节点带一个随机指针),对该链表进行复制,输出复制后的新链表.(剑指offer原题)

百度云二面

1/socket和epoll的关系区别?(不太懂他意思,反正对epoll的底层进行了阐述)
2/红黑树是线程安全的吗
3/有哪些同步手段
6/计数如何保证线程安全?(cas***作/***作系统底层指令支持)

oppo二面

2/介绍usb的项目/功能/架构

3/这个io复用模型跟普通多线程/多进程的区别
答: io复用,多个链接复用一个线程,而普通多线程是一个链接一个线程,所以必然创建线程的数目就多,现成的创建是有开销的,所以io复用这种开销小.

4/网络传输的数据协议
主要有3个段,前8bit是数据type,中间是length,最后是具体的data.

5/如果协议是这样.如果两个数据包连在一起,怎么分开?
答:在首部再加几个bit,作为隔离位.

6/如何实现你的fd是负载均衡的
答:分类处理

7/多个用户访问同一个资源,如何加锁
答:不太明白他的意思,epoll内部处理事件是同步依次执行的,而且这里的锁是线程资源

8/tcp是如何处理粘包?

9/tcp是如何关闭的?就是说4次挥手过程

10/如果tcp关闭的第四个分节没有被收到,那么怎么办?

11/tcp的拥塞控制过程

18/如何使用信号量制作出一个互斥锁

19/系统调用的返回有什么变化?

20/描述一下系统中断的过程

21/c++多态是如何实现的?

22/c++多继承是如何实现?如何处理同名变量

