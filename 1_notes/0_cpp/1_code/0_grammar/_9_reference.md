
**23. 理解std::move和std::forward**

首先move不move任何东西，forward也不转发任何东西，在运行时，不产生可执行代码，这两个只是执行转换的函数（模板），std::move无条件的将他的参数转换成一个右值，forward只有当特定的条件满足时才会执行他的转换，下面是std::move的伪代码：
    
    template<typename T>
    typename remove_reference<T>::type&& move(T&& param){
        using ReturnType = typename remove_reference<T>::type&&; //see Item 9
        return static_cast<ReturnType>(param);
    }

**24. 区别通用引用和右值引用**

    void f(Widget&& param);       //rvalue reference
    Widget&& var1 = Widget();     //rvalue reference
    auto&& var2 = var1;           //not rvalue reference
    template<typename T>
    void f(std::vector<T>&& param) //rvalue reference
    template<typename T>
    void f(T&& param);             //not rvalue reference

+ 如果一个函数的template parameter有着T&&的格式，且有一个deduce type T.或者一个对象被生命为auto&&,那么这个parameter或者object就是一个universal reference.
+ 如果type的声明的格式不完全是type&&,或者type deduction没有发生，那么type&&表示的是一个rvalue reference.
+ universal reference如果被rvalue初始化，它就是rvalue reference.如果被lvalue初始化，他就是lvaue reference.

**25. 对于右值引用使用std::move，对于通用引用使用std::forward**

右值引用仅会绑定在可以移动的对象上，如果形参类型是右值引用，则他绑定的对象应该是可以移动的

+ 通用引用在转发的时候，应该进行向右值的有条件强制类型转换（用std::forward）
+ 右值引用在转发的时候，应该使用向右值的无条件强制类型转换（用std::move)
+ 如果上面两个方法使用反的话，可能会导致很麻烦的事情（代码冗余或者运行期错误）

在书中一直在强调“move”和"copy"两个操作的区别，因为move在一定程度上会效率更高一些

但是在局部对象中这种想法是错误的：
    
    Widget MakeWidget(){
        Widget w;
        return w; //复制，需要调用一次拷贝构造函数
    }
    
    Widget MakeWidget(){
        Widget w;
        return std::move(w);//错误！！！！！！！会造成负优化
    }

因为在第一段代码中，编译器会启用返回值优化（return value optimization RVO）,这个优化的启动需要满足两个条件：
+ 局部对象类型和函数的返回值类型相同
+ 返回的就是局部对象本身

而下面一段代码是不满足RVO优化的，所以会带来负优化

所以：如果局部对象可以使用返回值优化的时候，不应该使用std::move 和std:forward

**26. 避免重载通用引用**

主要是因为通用引用（特别是模板），会产生和调用函数精确匹配的函数，例如现在有一个：
    
    template<typename T>
    void log(T&& name){}
    
    void log(int name){}
    
    short a;
    log(a);

这个时候如果调用log的话，就会产生精确匹配的log方法，然后调用模板函数

而且在重载过程当中，通用引用模板还会和拷贝构造函数，复制构造函数竞争（这里其实有太多种情况了），只举书上的一个例子：
    
    class Person{
    public:
        template<typename T> explicit Person(T&& n): name(std::forward<T>(n)){} //完美转发构造函数
        explicit Person(int idx); //形参为int的构造函数
    
        Person(const Person& rhs) //默认拷贝构造函数（编译器自动生成）
        Person(Person&& rhs); //默认移动构造函数（编译器生成）
    };
    
    Person p("Nancy");
    auto cloneOfP(p);  //会编译失败，因为p并不是const的，所以在和拷贝构造函数匹配的时候，并不是最优解，而会调用完美转发的构造函数

**27. 熟悉重载通用引用的替代品**

这一条主要是为了解决26点的通用引用重载问题提的几个观点，特别是对构造函数（完美构造函数）进行解决方案

+ 放弃重载，采用替换名字的方案
+ 用传值来替代引用（可以提升性能但却不用增加一点复杂度
+ 采用impl方法：
  
    template<typename T>
    void logAndAdd(T&& name){
        logAndAddImpl(
            std::forward<T>(name), 
            std::is_integral<typename std::remove_reference<T>::type>() //这一句只是为了区分是否是整形
        ); 
    }
+ 对通用引用模板加以限制（使用enable_if）
  
    class Person{
    public:
        template<typename T,
                 typename = typename std::enable_if<condition>::type>//这里的condition只是一个代号，condition可以是：!std::is_same<Person, typename std::decay<T>::type>::value,或者是：!std::is_base_of<Person, typename std::decay<T>::type>::value&&!std::is_integral<std::remove_reference_t<T>>::value
        explicit Person(T&& n);
    }
//说实话这个代码的可读性emmmmmmmm，大概还是我太菜了。。。。

**28. 理解引用折叠**

在实参传递给函数模板的时候，推导出来的模板形参会把实参是左值还是右值的信息编码到结果里面：
    
    template<typename T>
    void func(T&& param);
    
    Widget WidgetFactory() //返回右值
    Widget w;
    
    func(w);               //T的推到结果是左值引用类型，T的结果推倒为Widget&
    func(WidgetFactory);   //T的推到结果是非引用类型（注意这个时候不是右值），T的结果推到为Widget
C++中，“引用的引用”是违法的，但是上面T的推到结果是Widget&时，就会出现 void func(Widget& && param);左值引用+右值引用

所以事实说明，编译器自己确实会出现引用的引用（虽然我们并不能用），所以会有一个规则（我记得C++ primer note里面也讲到过）
+ 如果任一引用是左值引用，则结果是左值引用，否则就是右值引用
+ 引用折叠会在四种语境中发生：模板实例化，auto类型生成、创建和运用typedef和别名声明，以及decltype

**29. 认识移动操作的缺点**

+ 假设移动操作不存在，成本高，未使用
+ 对于那些类型或对于移动语义的支持情况已知的代码，则无需做上述假定

原因在于C++11以下的move确实是低效的，但是C++11及以上的支持让move操作快了一些，但是更多时候编写代码并不知道代码对C++版本的支持，所以要做以上假定

**30. 熟悉完美转发失败的情况**

    template<typename T>
    void fwd(T&& param){           //接受任意实参
        f(std::forward<T>(param)); //转发该实参到f
    }
    
    template<typename... Ts>
    void fwd(Ts&&... param){        //接受任意变长实参
        f(std::forward<Ts>(param)...);
    }

完美转发失败的情况：
    
    （大括号初始化物）
    f({1, 2, 3}); //没问题，{1, 2, 3}会隐式转换成std::vector<int>
    fwd({1, 2, 3}) //错误，因为向为生命为std::initializer_list类型的函数模板形参传递了大括号初始化变量，但是之前说如果是auto的话，会推到为std::initializer_list,就没问题了。。。
    
    （0和NULL空指针）
    （仅仅有声明的整形static const 成员变量）：
    class Widget{
    public:
        static const std::size_t MinVals = 28; //仅仅给出了声明没有给出定义
    };
    fwd(Widget::MinVals);      //错误，应该无法链接，因为通常引用是当成指针处理的，而也需要指定某一块内存来让指针指涉
    
    （重载的函数名字和模板名字）
    void f(int (*fp)(int));
    int processValue(int value);
    int processValue(int value, int priority);
    fwd(processVal); //错误，光秃秃的processVal并没有类型型别
    
    （位域）
    struct IPv4Header{
        std::uint32_t version:4,
        IHL:4,
        DSCP:6,
        ECN:2,
        totalLength:16;
    };
    
    void f(std::size_t sz); IPv4Header h;
    fwd(h.totalLength); //错误
+ 最后，所有的失败情形实际上都归结于模板类型推到失败，或者推到结果是错误的。

## reference 

### 1. concepts

### 2. 右值引用

### 3. 完美转发

### 99. quiz

#### 1. 为什么多线程传引用要用`std::ref`

**33. 对于std::forward的auto&&形参使用decltype**

在C++14中，我们可以在lambda表达式里面使用auto了，那么我们想要把传统的完美转发用lambda表达式写出来应该是什么样子的呢：
    
    class SomeClass{
    public:
        template<typename T>
        auto operator()(T x) const{
            return func(normalize(x));
        }
    }
    
    auto f=[](auto&& x){
        return func(normalize(std::forward<decltype(x)>(x)));
    };


引用绑定到临时对象的规则:
右值引用: 当使用右值引用(&&)绑定到返回的右值(例如函数返回的临时对象)时,编译器会延长右值的生命周期,使得引用继续有效.

cpp
Copy code
const T& constRef = getTemporary();  // const 引用绑定到临时对象
为什么需要引用绑定到临时对象:
避免不必要的拷贝: 当函数返回临时对象时,使用引用绑定可以避免不必要的拷贝构造,提高性能.

允许延迟析构: 通过延长临时对象的生命周期,允许在整个语句块中使用临时对象,而不会在引用失效时导致未定义行为.

* 什么时候需要用move
  * 对于callback函数来说
  * 对于将对象插入到容器来说
  * 交换两个对象
  * 
* 为什么右值可以被常量左值引用 引用?
   ```cpp
   const std::string& lv2 = lv1 + lv1; // 合法, 常量左值引用能够延长临时变量的生命周期
   ```
* 拷贝构造函数的参数可以不加引用吗?为什么



#### 2. 一次浅拷贝和一次移动相比较，性能有很大差距吗？

一次浅拷贝（Shallow Copy）和一次移动（Move）操作在性能上通常存在显著差异，尤其是在涉及到大量数据或资源密集型对象时。这种性能差异主要源于它们处理对象数据和资源的方式。

### 浅拷贝

- 浅拷贝仅复制对象的非静态成员变量的值，对于指针类型的成员变量，浅拷贝只复制指针值（地址），而不复制指针所指向的数据。
- 如果对象包含对动态分配内存的引用，浅拷贝可能导致多个对象指向同一内存地址，从而在析构时可能引发重复释放同一资源的问题（double free）。
- 浅拷贝的性能开销通常较低，因为它不涉及新内存的分配和数据的复制。但在处理复杂对象或资源管理时，可能会引起问题。

### 移动操作

- 移动操作是C++11引入的，它通过转移一个对象的资源（如动态分配的内存）到另一个对象，而不是复制资源。
- 移动操作通常涉及修改原对象的指针或资源句柄，并将其置于一个有效但未定义的状态，这样就避免了不必要的资源复制，从而大大减少了开销。
- 对于包含大量数据或昂贵资源（如大型数组、容器、文件句柄等）的对象，移动操作的性能优势尤为明显。

### 性能差距

- 在处理大型对象或资源密集型对象时，移动操作的性能通常远超过浅拷贝，因为它避免了数据的复制，只是简单地转移了资源的所有权。
- 对于小型或简单的对象，这两者之间的性能差异可能不那么明显，但移动操作仍然提供了更安全和高效的资源管理方式。

总结来说，移动操作相比于浅拷贝，在性能上通常有显著优势，尤其是在涉及大量数据或资源密集型对象时。此外，移动操作还提高了代码的安全性和资源管理的效率。


#### 3. 如果都是值类型的，那浅拷贝和移动有区别吗

没有区别。

只有在引用类型的时候，浅拷贝和移动的性能也差不多，但是资源管理的表现形式不同
