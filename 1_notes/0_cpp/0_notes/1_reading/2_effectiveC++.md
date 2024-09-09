#### 七、模板与泛型编程 (Templates and Generic Programming)

**43. 学习处理模板化基类内的名称 （Know how to access names in templatized base classes)**

原代码：
```c++    
    class CompanyA{
    public:
        void sendCleartext(const std::string& msg);
        ....
    }
    class CompanyB{....}
    
    template <typename Company>
    class MsgSender{
    public:
        void sendClear(const MsgInfo& info){
            std::string msg;
            Company c;
            c.sendCleartext(msg);
        }
    }
    template<typename Company>//想要在发送消息的时候同时写入log，因此有了这个类
    class LoggingMsgSender:public MsgSender<Company>{
        public:
        void sendClearMsg(const MsgInfo& info){
            //记录log
            sendClear(info);//无法通过编译，因为找不到一个特例化的MsgSender<company>
        }
    }
```

解决方法1（认为不是特别好）：
```c++
    template <> // 生成一个全特例化的模板
    class MsgSender<CompanyZ>{  //和一般的template，但是没有sendClear,当Company==CompanyZ的时候就没有sendClear了
    public:
        void sendSecret(const MsgInfo& info){....}
    }
```
解决方法2（使用this）：
```c++
    template<typename Company>
    class LoggingMsgSender:public MsgSender<Company>{
        public:
        void sendClearMsg(const MsgInfo& info){
            //记录log
            this->sendClear(info);//假设sendClear将被继承
        }
    }
```
解决方法3（使用using）：
```c++
    template<typename Company>
    class LoggingMsgSender:public MsgSender<Company>{
        public:
    
        using MsgSender<Company>::sendClear; //告诉编译器，请他假设sendClear位于base class里面
    
        void sendClearMsg(const MsgInfo& info){
            //记录log
            sendClear(info);//假设sendClear将被继承
        }
    }
```
解决方法4（指明位置）：
```c++
    template<typename Company>
    class LoggingMsgSender:public MsgSender<Company>{
        public:
        void sendClearMsg(const MsgInfo& info){
            //记录log
            MsgSender<Company>::sendClear(info);//假设sendClear将被继承
        }
    }
```
上面那些做法都是对编译器说：base class template的任何特例化版本都支持其一般版本所提供的接口



**47. 请使用traits classes表现类型信息 （Use traits classes for information about types)**

traits是一种允许你在编译期间取得某些类型信息的技术，或者受是一种协议。这个技术的要求之一是：他对内置类型和用户自定义类型的表现必须是一样的。
```c++
    template<typename T>
    struct iterator_traits;  //迭代器分类的相关信息
                             //iterator_traits的运作方式是，针对某一个类型IterT，在struct iterator_traits<IterT>内一定声明//某个typedef名为iterator_category。这个typedef 用来确认IterT的迭代器分类
    一个针对deque迭代器而设计的class大概是这样的
    template<....>
    class deque{
        public:
        class iterator{
            public:
            typedef random_access_iterator_tag iterator_category;
        }
    }
    对于用户自定义的iterator_traits，就是有一种“IterT说它自己是什么”的意思
    template<typename IterT>
    struct iterator_traits{
        typedef typename IterT::iterator_category iterator_category;
    }
    //iterator_traits为指针指定的迭代器类型是：
    template<typename IterT>
    struct iterator_traits<IterT*>{
        typedef random_access_iterator_tag iterator_category;
    }
```
综上所述，设计并实现一个traits class：
+ 确认若干你希望将来可取得的类型相关信息，例如对迭代器而言，我们希望将来可取得其分类
+ 为该信息选择一个名称（例如iterator_category）
+ 提供一个template和一组特化版本（例如iterator_traits)，内含你希望支持的类型相关信息

在设计实现一个traits class以后，我们就需要使用这个traits class：
```c++ 
    template<typename IterT, typename DistT>
    void doAdvance(IterT& iter, DistT d, std::random_access_iterator_tag){ iter += d; }//用于实现random access迭代器
    template<typename IterT, typename DistT>
    void doAdvance(IterT& iter, DistT d, std::bidirectional_iterator_tag){ //用于实现bidirectional迭代器
        if(d >=0){
            while(d--)
                ++iter;
        }
        else{
            while(d++)
                --iter;
        }
    }
    
    template<typename IterT, typename DistT>
    void advance(IterT& iter, DistT d){
        doAdvance(iter, d, typename std::iterator_traits<IterT>::iterator_category());
    }
```
使用一个traits class:
+ 建立一组重载函数（像劳工）或者函数模板（例如doAdvance），彼此间的差异只在于各自的traits参数，令每个函数实现码与其接受traits信息相应
+ 建立一个控制函数（像工头）或者函数模板（例如advance），用于调用上述重载函数并且传递traits class所提供的信息


#### 八、定制new和delete (Customizing new and delete)

**49. 了解new-handler的行为 （Understand the behavior of the new-handler)**

当new无法申请到新的内存的时候，会不断的调用new-handler，直到找到足够的内存,new_handler是一个错误处理函数：
```c++
namespace std{
    typedef void(*new_handler)();
    new_handler set_new_handler(new_handler p) throw();
}
```

一个设计良好的new-handler要做下面的事情：
+ 让更多内存可以被使用
+ 安装另一个new-handler，如果目前这个new-handler无法取得更多可用内存，或许他知道另外哪个new-handler有这个能力，然后用那个new-handler替换自己
+ 卸除new-handler
+ 抛出bad_alloc的异常
+ 不返回，调用abort或者exit

new-handler无法给每个class进行定制，但是可以重写new运算符，设计出自己的new-handler
此时这个new应该类似于下面的实现方式：
```c++
void* Widget::operator new(std::size_t size) throw(std::bad_alloc){
    NewHandlerHolder h(std::set_new_handler(currentHandler));      // 安装Widget的new-handler
    return ::operator new(size);                                   //分配内存或者抛出异常，恢复global new-handler
}
```

总结：
+ set_new_handler允许客户制定一个函数，在内存分配无法获得满足时被调用
+ Nothrow new是一个没什么用的东西

**52. 写了placement new也要写placement delete（Write placement delete if you write placement new)**

如果operator new接受的参数除了一定会有的size_t之外还有其他的参数，这个就是所谓的palcement new

void* operator new(std::size_t, void* pMemory) throw(); //placement new
static void operator delete(void* pMemory) throw();     //palcement delete，此时要注意名称遮掩问题

#### 二、运算符

**5. 小心用户自定义的转换函数**

因为可能会出现一些无法理解的并且也是无能为力的运算，而且在不需要这些类型转换函数的时候，仍然可能会调用这些转换，例如下面的代码：
```c++
    // 有理数类
    class Rational{
    public:
        Rational(int numerator = 0, int denominator = 1)
        operator double() const;
    }
    
    Rational r(1, 2);
    double d = 0.5 * r; //将r转换成了double进行计算
    
    cout << r; //会调用最接近的类型转换函数double，将r转换成double打印出来，而不是想要的1/2，
```
上面问题的解决方法是，把double变成
    
    double asDouble() const;这样就可以直接用了

但是即使这样做还有可能会出现隐式转换的现象：
```c++
    template<class T>
    class Array{
    public:
        Array(int size);
        T& operator[](int index);
    };
    
    bool operator==(const Array<int> &lhs, const Array<int> & rhs);
    Array<int> a(10), b(10);
    if(a == b[3]) //想要写 a[3] == b[3]，但是这时候编译器并不会报错，解决方法是使用explicit关键字
    
    explicit Array(int size); 
    if(a == b[3]) // 错误，无法进行隐式转换
```
其实还有一种很骚的操作：
```c++
    class Array { 
    public:  
        class ArraySize {                    // 这个类是新的 
            public: 
            ArraySize(int numElements):theSize(numElements){}
            int size() const { return theSize;}
        private: 
            int theSize;
        };
        Array(int lowBound, int highBound); 
        Array(ArraySize size);                  // 注意新的声明
        ... 
    }; 
```
这样写的代码在Array<int> a(10);的时候，编译器会先通过类型转换转换成ArraySize，然后再进行构造，虽然麻烦很多，效率也低了很多，但是在一定程度上可以避免隐式转换带来的问题

**8. 理解new和delete在不同情形下的含义**

两种new: new 操作符（new operator）和new操作（operator new）的区别

    string *ps = new string("Memory Management"); //使用的是new操作符，这个操作符像sizeof一样是内置的，无法改变
    
    void* operator new(size_t size); // new操作，可以重写这个函数来改变如何分配内存

一般不会直接调用operator new，但是可以像调用其他函数一样调用他：

    void* rawMemory = operator new(sizeof(String));

placement new : placement new 是有一些已经被分配但是没有被处理的内存，需要在这个内存里面构造一个对象，使用placement new 可以实现这个需求，实现方法：
    
    class Widget{
        public:
            Widget(int widgetSize);
        ....
    };
    
    Widget* constructWidgetInBuffer(void *buffer, int widgetSize){
        return new(buffer) Widget(widgetSize);
    }

这样就返回一个指针，指向一个Widget对象，对象在传递给函数的buffer里面分配

同样的道理：
    delete buffer; //指的是先调用buffer的析构函数，然后再释放内存
    operator delete(buffer); //指的是只释放内存，但是不调用析构函数

而placement new 出来的内存，就不应该直接使用delete操作符，因为delete操作符使用operator delete来释放内存，但是包含对象的内存最初不是被operator new分配的，而应该显示调用析构函数来消除构造函数的影响

new[]和delete[]就相当于对每一个数组元素调用构造和析构函数

#### 三、异常

**12. 理解“抛出异常”，“传递参数”和“调用虚函数”之间的不同**

传递参数的函数：

    void f1(Widget w);
catch子句：    

    catch(widget w)... 

上面两行代码的相同点：传递函数参数与异常的途径可以是传值、传递引用或者传递指针

上面两行代码的不同点：系统所需要完成操作的过程是完全不同的。调用函数时程序的控制权还会返回到函数的调用处，但是抛出一个异常时，控制权永远都不会回到抛出异常的地方
三种捕获异常的方法：
    
    catch(Widget w);
    catch(Widget& w);
    catch(const Widget& w);

一个被抛出的对象可以通过普通的引用捕获，它不需要通过指向const对象的引用捕获，但是在函数调用中不允许传递一个临时对象到一个非const引用类型的参数里面
同时异常抛出的时候实际上是抛出对象创建的临时对象的拷贝，

另外一个区别就是在try语句块里面，抛出的异常不会进行类型转换（除了继承类和基类之间的类型转换，和类型化指针转变成无类型指针的变换），例如：
    
    void f(int value){
        try{
            throw value; //value可以是int也可以是double等其他类型的值
        }
        catch(double d){
            ....         //这里只处理double类型的异常，如果遇到int或者其他类型的异常则不予理会
        }
    }

最后一个区别就是，异常catch的时候是按照顺序来的，即如果两个catch并且存在的话，会优先进入到第一个catch里面，但是函数则是匹配最优的

**13. 通过引用捕获异常**

使用指针方式捕获异常：不需要拷贝对象，是最快的,但是，程序员很容易忘记写static，如果忘记写static的话，会导致异常在抛出后，因为离开了作用域而失效：
    
    void someFunction(){
        static exception ex;
        throw &ex;
    }
    void doSomething(){
        try{
            someFunction();
        }
        catch(exception *ex){...}
    }
创建堆对象抛出异常：new exception 不会出现异常失效的问题，但是会出现在捕捉以后是否应该删除他们接受的指针，在哪一个层级删除指针的问题
通过值捕获异常：不会出现上述问题，但是会在被抛出时系统将异常对象拷贝两次，而且会出现派生类和基类的slicing problem，即派生类的异常对象被作为基类异常对象捕获时，会把派生类的一部分切掉，例如：
    
    class exception{
    public:
        virtual const char *what() throw();
    };
    class runtime_error : public exception{...};
    void someFunction(){
        if(true){
            throw runtime_error();
        }
    }
    void doSomething(){
        try{
            someFunction();
        }
        catch(exception ex){
            cerr << ex.what(); //这个时候调用的就是基类的what而不是runtime_error里面的what了，而这个并不是我们想要的
        }
    }

通过引用捕获异常：可以避免上面所有的问题，异常对象也只会被拷贝一次：
    
    void someFunction(){...} //和上面一样
    void doSomething(){
        try{...}             //和上面一样
        catch(exception& ex){
            cerr << ex.what(); //这个时候就是调用的runtime_error而不是基类的exception::what()了，其他和上面其实是一样的
        }
    }


**17. 考虑使用延迟计算**

一个延迟计算的例子：

    class String{....}
    String s1 = "Hello";
    String s2 = s1;  //在正常的情况下，这一句需要调用new操作符分配堆内存，然后调用strcpy将s1内的数据拷贝到s2里面。但是我们此时s2并没有被使用，所以我们不需要s2，这个时候如果让s2和s1共享一个值，就可以减小这些开销

使用延迟计算进行读操作和写操作：

    String s = "Homer's Iliad";
    cout << s[3];
    s[3] = 'x';
首先调用operator[] 用来读取string的部分值，但是第二次调用该函数式为了完成写操作。读取效率较高，写入因为需要拷贝，所以效率较低，这个时候可以推迟作出是读操作还是写操作的决定。

延迟策略进行数据库操作：有点类似之前写web 的时候，把数据放在内存和数据库两份，更新的时候只更新内存，然后隔一段时间（或者等到使用的时候）去更新数据库。
在effective c++里面，则是更加专业的将这个操作封装成了一个类，然后把是否更新数据库弄成一个flag。以及使用了mutable关键字，来修改数据

延迟表达式：
    
    Matrix<int> m1(1000, 1000), m2(1000, 1000);
    m3 = m1 + m2;
    因为矩阵的加法计算量太大（1000*1000）次计算，所以可以先用表达式表示m3是m1和m2的和，然后真正需要计算出值的时候再真的进行计算（甚至计算的时候也只计算m3[3][2]这样某一个位置的值）


#### 五、技巧

**25. 使构造函数和非成员函数具有虚函数的行为**
```c++
    class NewsLetter{
    private:
        static NLComponent *readComponent(istream& str);
        virtual NLComponent *clone() const = 0;
    };
    NewsLetter::NewsLetter(istream& str){
        while(str){
            components.push_back(readComponent(str));
        }
    }
    class TextBlock: public NLComponent{
    public:
        virtual TextBlock*clone()const{
            return new TextBlock(*this);
        }
    }
```
在上面那段代码当中，readComponent就是一个具有构造函数行为（因为能够创建出新的对象）的函数，我们叫做虚拟构造函数

clone() 叫做虚拟拷贝构造函数,相当于拷贝一个新的对象

通过这种方法，我们上面的NewsLetter构造函数就可以这样：
```c++
    NewsLetter::NewsLetter(const NewsLetter& rhs){
        while(str){
            for(list<NLComponent*>::const_iterator it=rhs.component.begin(); it!=rhs.component.end();it++){
                components.push_back((*it)->clone());
            }
        }
    }
```
这样每一个TextBlock都可以调用他自己的clone，其他的子类也可以调用他们自己对应的clone()


**31. 基于多个对象的虚函数**

考虑两个对象碰撞的问题：
    
    class GameObject{....};
    class SpaceShip : public GameObject{....};
    class SpaceStation : public GameObject{....};
    class Asteroid : public GameObject{....};
    
    void checkForCollision(GameObject& object1, GameObject& object2){
        processCollision(object1, object2);
    }

当我们调用processCollision的时候，该函数取决于两个不同的对象，但是这个函数并不知道其object1和object2的真实类型，这个时候就要基于多个对象设计虚函数 

解决方法有很多：
    
使用虚函数+RTTI：

    class GameObject{
    public:
        virtual void collide(GameObject& otherObject) = 0;
    };
    class SpaceShip:public GameObject{
    public:
        virtual void collide(GameObject& otherObject);
    };
    
    void SpaceShip:collide(GameObject& otherObject){
        const type_info& objectType = typeid(otherObject);
        if(objectType == typeid(SpaceShip)){
            SpaceShip& ss = static_cast<SpaceShip&>(otherObject);
        }
        else if(objectType == typeid(SpaceStation)).......
    }
只使用虚函数：
    
    class SpaceShip; // forward declaration
    class SpaceStation;
    class Asteroid;
    class GameObject { 
    public:
        virtual void collide(GameObject&   otherObject) = 0;
        virtual void collide(SpaceShip&    otherObject) = 0;
        virtual void collide(SpaceStation& otherObject) = 0;
        virtual void collide(Asteroid&     otherObject) = 0;
        ...
    };
模拟虚函数表（对继承体系中的函数做一些修改）：

    class SpaceShip : public GameObject { 
    public:
        virtual void collide(GameObject&   otherObject);
        virtual void hitSpaceShip(SpaceShip&    otherObject);
        virtual void hitSpaceStation(SpaceStation& otherObject);
        virtual void hitAsteroid(Asteroid&     otherObject);
        ...
    };
初始化模拟虚函数表：
    
    class GameObject { // this is unchanged 
    public: 
        virtual void collide(GameObject& otherObject) = 0;
        ...
    };
    
    class SpaceShip: public GameObject {
    public:
        virtual void collide(GameObject& otherObject);
        // these functions now all take a GameObject parameter
        virtual void hitSpaceShip(GameObject& spaceShip);
        virtual void hitSpaceStation(GameObject& spaceStation);
        virtual void hitAsteroid(GameObject& asteroid);
        ...
    };
    
    SpaceShip::HitMap * SpaceShip::initializeCollisionMap(){
        HitMap *phm = new HitMap;
        (*phm)["SpaceShip"] = &hitSpaceShip;
        (*phm)["SpaceStation"]= &hitSpaceStation;
        (*phm)["Asteroid"] = &hitAsteroid;
        return phm; 
    
