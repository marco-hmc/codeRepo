### 内存空间
在计算机系统中,内存空间通常被划分为以下几个部分:

1. **代码段(Text Segment)**:也被称为文本区域,这部分空间存储程序的机器代码.

2. **数据段(Data Segment)**:这部分空间存储程序中的全局变量和静态变量.

3. **堆(Heap)**:堆是用于动态内存分配的区域,如C++中的new操作符和C中的malloc函数分配的内存.

4. **栈(Stack)**:栈用于存储局部变量和函数调用的信息.每当一个函数被调用时,一个新的栈帧就会被压入栈中,这个栈帧包含了函数的局部变量和返回地址.

5. **常量段(Constant Segment)**:这部分空间存储程序中的常量值.

6. **BSS段(Block Started by Symbol)**:这部分空间存储程序中未初始化的全局变量和静态变量.

在多线程环境中,每个线程都有自己的栈空间,但所有线程共享同一个堆空间.

需要注意的是,这些内存划分是逻辑上的划分,物理内存的实际布局可能会因操作系统和硬件的不同而有所不同.

#### 1. 常量段和数据段为什么要分开?
常量段和数据段被分开主要是出于以下几个原因:

1. **保护**:常量段中的数据是只读的,不应被修改.将常量段和数据段分开可以让操作系统设置不同的内存保护权限,防止程序错误地修改常量数据.

2. **优化**:编译器和链接器可以对常量数据进行优化.例如,如果一个常量在程序中被多次使用,编译器可以只在常量段中存储一份该常量的副本.

3. **内存管理**:在某些系统中,常量段可能被映射到只读的物理内存或者ROM中,这样可以节省可读写的物理内存.

总的来说,将常量段和数据段分开可以提高程序的安全性和效率,同时也有助于内存管理.

#### 2. bss段和数据段为什么要分开?
BSS段和数据段被分开主要是出于以下几个原因:

1. **初始化**:数据段中的变量在程序开始运行之前就已经被初始化了,而BSS段中的变量则在程序开始运行时被自动初始化为0.将这两种变量分开可以让操作系统和编译器更有效地处理它们.

2. **存储优化**:在程序的可执行文件中,BSS段的变量不需要占用任何实际的存储空间,只需要记录它们的位置和大小.这是因为BSS段的变量在程序开始运行时都会被初始化为0,所以没有必要在可执行文件中为它们存储实际的数据.这可以减小可执行文件的大小,节省磁盘空间.

3. **内存管理**:将BSS段和数据段分开可以让操作系统更有效地管理内存.例如,操作系统可以将数据段映射到只读的物理内存中,而将BSS段映射到可读写的物理内存中.

总的来说,将BSS段和数据段分开可以提高程序的效率,减小可执行文件的大小,同时也有助于内存管理.

#### 3. 多线程的内存空间是如何管理的
多线程的内存空间是怎么管理的?
在C++中,每个线程都有自己的栈空间,这个栈空间是在线程创建时由操作系统自动分配的.线程的栈空间通常用于存储线程的局部变量和函数调用的上下文信息.

线程的栈空间通常位于进程的虚拟地址空间中,每个线程的栈空间都是独立的,互不干扰.线程的栈空间大小通常有一个默认值,但是在某些系统和编程环境中,你可以在创建线程时指定栈空间的大小.

需要注意的是,虽然每个线程都有自己的栈空间,但是所有线程共享同一个进程的堆空间.这意味着线程可以通过堆来共享数据,但是需要注意同步和数据一致性的问题.


#### 4. 多进程的内存空间是如何管理的

### Lambda capture initializers
This allows creating lambda captures initialized with arbitrary expressions. The name given to the captured value does not need to be related to any variables in the enclosing scopes and introduces a new name inside the lambda body. The initializing expression is evaluated when the lambda is _created_ (not when it is _invoked_).
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
Because it is now possible to _move_ (or _forward_) values into a lambda that could previously be only captured by copy or reference we can now capture move-only types in a lambda by value. Note that in the below example the `p` in the capture-list of `task2` on the left-hand-side of `=` is a new variable private to the lambda body and does not refer to the original `p`.
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


* 向量化是什么意思?
* 为什么c++的成员不可以既是template又是virtual的
* enable_share_from_this是做什么的
* 为什么stl中的内存分配器要设计为一个模板参数而不是一个构造函数参数?
* 如何实现一个引用计数指针,以及其中要注意的点?
* 拷贝构造函数的参数可以不加引用吗?为什么
* 定义一个类B,它有一个A*类型的成员变量.并写出它的拷贝构造函数.
考察一下对于深拷贝,浅拷贝的思考.
* shared_ptr的引用计数是怎么存储的?    多线程场景怎么解决
* 模板类A中有一个static变量x,那么该程序中变量x的实例有几分?
* shared ptr<T>怎么实现一个普通指针的const T*效果?
* shared ptr修改指向的时候,分析一下过程,性能开销如何?

* 如果一个函数有多处return,我想每个return都加一些相同的处理,最好怎么实现?
这里最好的写法就是RAII模式的应用.不过很多时候我们也不必每次新建一个RAII模式的类.可以使用用unique ptr来完成.

* vecotra;a在堆上还是栈上? vecotraa;a中数据在堆上还是栈上?


* 
<!-- int main() {
  int a[2][5] = {{1, 2, 3, 4, 5}, {1, 2, 3, 4, 5}};
  cout << a << endl;
  cout << *a << endl;
  cout << *a[0] << endl;
  return 0;
} -->

* if(a)这个也可以重载

### Non-static data member initializers
Allows non-static data members to be initialized where they are declared, potentially cleaning up constructors of default initializations.
```c++
// Default initialization prior to C++11
class Human {
    Human() : age{0} {}
  private:
    unsigned age;
};
// Default initialization on C++11
class Human {
  private:
    unsigned age {0};
};
```


* 临时变量可以绑定到左值引用吗?
引用绑定到临时对象是一种语言特性,它确保通过引用绑定的临时对象在整个语句块中都保持有效.这个特性通常与 const 引用一起使用.

引用绑定到临时对象的规则:
右值引用: 当使用右值引用(&&)绑定到返回的右值(例如函数返回的临时对象)时,编译器会延长右值的生命周期,使得引用继续有效.

cpp
Copy code
T&& rvalue = getRvalue();  // rvalue 引用绑定到右值
const 引用: 当使用 const 引用绑定到右值(临时对象)时,编译器也会延长右值的生命周期.

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

* ***既然如此,为什么delete不内置设置为nullptr的操作***
`delete`操作符在C++中的设计是不会自动将指针设置为`nullptr`的,这主要是由于以下几个原因:

1. **兼容性**:C++是C语言的扩展,为了保持与C语言的兼容性,`delete`操作符的行为与C语言中的`free`函数类似,都不会自动将指针设置为`nullptr`.

2. **灵活性**:在某些情况下,程序员可能不希望`delete`后自动将指针设置为`nullptr`.例如,如果一个指针被多个对象共享,`delete`其中一个对象后,其他对象可能仍需要使用该指针.如果`delete`自动将指针设置为`nullptr`,就会破坏这种共享关系.

3. **性能**:自动将指针设置为`nullptr`需要额外的操作,这可能会对性能产生影响.在性能敏感的程序中,这可能是一个问题.

因此,C++的设计者选择让`delete`操作符的行为更简单/更直接,不自动将指针设置为`nullptr`.这样,程序员可以根据需要自行决定是否将指针设置为`nullptr`.

* ***无符号整数的错误使用***
    ```c++
    for (unsigned int i = 10; i >= 0; --i) { ... }
    ```

* ***容器的size()返回类型是无符号整数***
    ```c++
    std::vector<int> vec;
    vec.push_back(1);
    for (auto idx = vec.size(); idx >= 0; idx--) {
        cout << "===== \n";
    }
    ```

* ***STL遍历删除时注意迭代器失效问题***
    ```c++
    void erase(std::vector<int> &vec, int a) {
        for (auto iter = vec.begin(); iter != vec.end();) { // 这个正确
            if (*iter == a) {
                iter = vec.erase(iter);
            } else {
                ++iter;
            }
        }

        for (auto iter = vec.begin(); iter != vec.end(); ++iter) {  // error
            if (*iter == a) {
                vec.erase(iter); // error
            }
        }
    }
    ```

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

* 为什么右值可以被常量左值引用 引用?
   ```cpp
   const std::string& lv2 = lv1 + lv1; // 合法, 常量左值引用能够延长临时变量的生命周期
   ```

* unique_ptr是怎么实现的?为什么把形参为左值引用的禁了,只放开了形参为右值引用的?

* shared_ptr是怎么实现的?为什么refCount要是指针?

* 为什么静态变量不可以在类里面初始化?

* 类型放松 协变返回:
只能用于返回类型是指针或引用的情况
覆盖函数的类型必须与它所覆盖的虚函数类型完全一致,但是C++吧,就觉得既然都is-a,那么可以说,如果原返回类型是Base*,那么覆盖的函数可以返回Derived*,类似的,返回的类型是Base&,那么覆盖函数可以返回Derived&.这叫协变返回.<br>

腾讯OMG团队(实习)

1/画出tcp头部的协议格式.
扩展: udp头部/ip头部/http头部
2/Http的报文头部

9/引用和指针的区别
答:引用是一个已有对象的别称,指针是一个地址,从非空性上说,引用不能为空,指针本身是个值,可以为空;在编码的时候,对引用我们不需要判断,但是对于指针,我们必须对其非空性进行判断;当指向的对象可能在发生变化的时候,往往使用指针,而引用一定固定的.

11/tcp的三次握手过程和四次挥手过程
答:这个建议将函数调用的情况添加进去说明.详细:TCP建立连接三次握手和释放连接四次握手.note

12/c++多态的实现原理
答:c++多态主要是通过虚函数表实现的,c++多态的体现,主要是通过父类指针指向一个子类对象,此时调用的函数就是子类的函数,体现了多态性,因为在调用过程中,通过钱4个字节的虚表指针找到了虚函数表,此时由于实际对象是子类对象,那么其虚函数表是子类的虚函数表,对于同一个虚函数,子类的虚函数将会覆盖掉父类的虚函数,构建出自己的虚函数表,所以此时通过虚表指针访问放的虚函数就是子类的虚函数,这就是c++的多态的体现.

13/c++对象的内存模型
答:在内存中,前4个字节代表了其虚表指针,指向的是子类的虚函数表,接下来存放的是父类的对象的成员,再是子类成员部分.

14c++的内存模型
答:内存分为5个段,从低地址往高地址,一次是代码段/数据段/bss段/堆/栈.然后balabala....

15/滑动窗口的作用
答:主要就是为了实现流量控制,控制了发送包的速率,每次发送方只能发送滑动窗口内部的数据包,才能保证接收方不会因为发送过快造成流量淹没,数据包的丢失.他的大小是 拥塞窗口和通告窗口 两者的最小值.

项目
1/如何实现断点续传,如何提高上传速

算法
1/计算表达式 (改成后缀表达式进行处理)
2/朋友圈问题,求总共有多少个朋友圈 (使用并查集)
3/链表逆序 (剑指offer上有,但是如果不改变内存结构,那就只能改变值,使用栈进行存储)
4/一个数组找中位数(通过快排思想,常数级的若干次求position,直到恰好是中心,时间复杂度是O(n),如果是海量数据呢2g数据,500内存如何处理?->hash之后分成小文件,再外部排序,使用归并,可以使用最大堆,直到数据过半)

腾讯SNG(实习一面)

1/系统调用和库函数有什么区别和联系
2/epoll和select的区别
3/epoll的高效,有几种工作模式( LT/ET)
4/TCP 和 UDP的区别
5/TIMEWAIT是什么,为什么要设置TIMEWAIT状态
6/TCP的可靠性是如何实现的?(流量控制/拥塞控制/确认序号/校验???)
暂时记不起来了.

oppo(一面)

首先介绍项目,我给他介绍了一下这个项目的架构,功能.

问题1:你觉得这个项目的难点在于哪里?(懵逼了)
答:难点到不太多,可以说一下学到了什么,优化了什么,比如数据传输协议用到了protobuf,更快,更安全/数据量更小.

问题2:io复用和异步io有什么区别?
答:IO复用其实一种同步IO,他只是将事件通知统一交给了select或者epoll,所以,对于IO复用,其实Select或者epoll在检测可用时是阻塞的,里面的读写一般也是阻塞的,而异步IO是不会阻塞的,数据从内核态拷贝到用户态缓冲区完成后,***作系统会发送信号,通知进程处理,这个过程进程是可以继续执行的,这个就是异步io.

问题3:多进程和多线程有什么区别?如果给你一个业务场景,你是如何选择多进程还是多线程?
答:多线程共享同一个地址空间,带来的好处就是他们进行通信比较方便,可以通过全局变量等,但是也有隐患,需要处理好竞争问题,而且一旦一个线程崩掉了,整个进程就死了,影响其他进程.多进程相反..此外,线程的创建开销更小.多进程的场景举例:比如你要进行主机迁移,多进程的话,你可以将某个进程迁移到另外的主机,不受影响,但是多线程没法迁移.

问题4:讲一讲c++的虚函数表呢?
答:c++的多态就是通过虚函数表来实现的,该表是在编译期生成,存放在rodata段,我们知道一个类的对象的内存结构是前4个字节是其虚表指针,即vptr,指向了其虚表,虚表中装的就是该类的虚函数.c++多态的体现,往往是通过父类指针,指向子类对象,我们发现调用的虚函数是子类的虚函数,而不是父类的就是因为此时的对象是子类对象,其虚表是子类的虚表,其中的同名虚函数早在编译期就已经被覆盖成子类的虚函数了,所以此时调用的是子类的虚函数,多态就是这么体现的.

问题5:构造函数/析构函数的顺序,为什么析构函数是反向的?
答:构造:先父类再子类; 析构:先子类再父类. 这是c++的规则.

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

14/STL的迭代器的类型有哪几种?

15/STL hashmap的实现?

16/线程间同步的手段

17/进程间通信的方式

18/如何使用信号量制作出一个互斥锁

19/系统调用的返回有什么变化?

20/描述一下系统中断的过程

21/c++多态是如何实现的?

22/c++多继承是如何实现?如何处理同名变量

23/怎么实现无锁***作

26/你对哪些技术感兴趣?

百度云一面

1/C++多态的实现
2/多重继承下,多个父类含有同一同名函数,子类对象调用会有问题吗?
答:首先 AB2个父类中的函数假设就是普通成员函数f(),那么子类C没有自己的f函数,其对象c.f()的时候就会报错,编译报错,存在二义性.如果C有自己的f函数,此时不会报错,调用的是自己c类的f()函数,也就是说此时父类的函数就被隐藏了.如果AB中的f()是虚函数,那么也不受影响,还是调c的.如果2个f的参数类型也不一样,也会报二义性错误.(为什么呢?)
3/static变量
4/tcp三次握手 /2次/4次?
5/tcp可靠性的实现原因
6/滑动窗口的作用
7/原子***作如何实现(锁/cas***作)
8/如何实现一个互斥锁,互斥锁的实现原理

想不起来了
笔试:
特殊链表(每个节点带一个随机指针),对该链表进行复制,输出复制后的新链表.(剑指offer原题)


百度云二面

1/socket和epoll的关系区别?(不太懂他意思,反正对epoll的底层进行了阐述)
2/红黑树是线程安全的吗
3/有哪些同步手段
4/用过哪种锁(mutex)
5/读写锁了解过吗,自己实现一下,提出思路即可(对读***作进行计数)
6/计数如何保证线程安全?(cas***作/***作系统底层指令支持)
7/vector的插入pushback的时间复杂度是多少(O(n))
8/如果vectorpushback的时候扩容了,比如pushback n个数,时间复杂度是多少?(我给他阐述了内存拷贝的过程,但是不知道怎么求,他回答说:其实是一个等差数列,最后求得还是O(n))
11/c++多态的实现(run time的多态:指针或者引用 结合 虚函数表实现)
13/ move除了用于指针,还可以用于哪些?比如哪些数据结构 (vector)


360二面
1/使用stl如何保证线程安全(除了锁以外)
2/交给sub 线程的文件描述符如何回收的?
3/tcp粘包
8/IO和reactor模式 (吹的select和epoll)
9/linux下 进程cpu占用是怎么计算的(大致是:通过/proc/stat 读取CPU总的时间,再通过/proc/pid/stat下读取进程的占用时间,做除法.(比较粗略的阐述))
10/linux下 tmp目录里面的内容会被清除吗(会,系统会执行tmpwatch脚本,一般传入参数是时间,比如 tmpwatch 10 /tmp/ 表示的就是会删除10天内没有修改/访问的文件.)
11/怎么查动态依赖的库有哪些?(readelf -a [程序名] |grep library)


腾讯IEG魔方工作室(简历面)

tcp udp 游戏
容器线程安全
新链接 何时注册写事件
主线程如何将fd交给sub线程?
为什么这个回调函数在本函数执行,是线程安全的?
rehash
切换的性能损耗
strncpy
容器的线程安全是怎么保证的?如何判断一个容器是否是线程安全的?