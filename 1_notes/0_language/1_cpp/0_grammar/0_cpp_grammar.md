

## trivial grammar

### 1. attribute
```c++
#include <iostream>

[[deprecated("This function is deprecated. Use newFunction() instead.")]] void
oldFunction() {
  std::cout << "This is the old function." << std::endl;
}

[[nodiscard]] int calculate() { return 42; }

int main() {
  oldFunction(); // Generates a deprecation warning
  int result =
      calculate(); // Generates a warning if the return value is ignored

  return 0;
}
```
这段代码展示了C++17标准中引入的两个新属性：`[[deprecated]]`和`[[nodiscard]]`。

- `[[deprecated]]`属性用于标记已经被废弃的函数。当你试图使用被`[[deprecated]]`标记的函数时，编译器会生成一个警告，告诉你这个函数已经被废弃，你应该使用其他函数代替。在这个例子中，`oldFunction`函数被标记为废弃，所以在`main`函数中调用`oldFunction`时，编译器会生成一个警告。

- `[[nodiscard]]`属性用于标记那些返回值不应该被忽略的函数。如果你调用了被`[[nodiscard]]`标记的函数，但没有使用它的返回值，编译器会生成一个警告。在这个例子中，`calculate`函数被标记为`[[nodiscard]]`，所以在`main`函数中调用`calculate`但没有使用它的返回值时，编译器会生成一个警告。

除了`[[deprecated]]`和`[[nodiscard]]`，C++还有其他的属性，如`[[maybe_unused]]`（用于标记可能未被使用的变量，以避免编译器生成未使用变量的警告）、`[[likely]]`和`[[unlikely]]`（用于给编译器提供分支预测的提示，这两个属性在C++20中引入）等。

### 2. literals

```c++
#include <cmath>
#include <iostream>
#include <string>

// 是使用字面量方式实现的.在C++中,字面量是表示固定值的文本形式.整数字面量可以加上后缀来指定其类型.
unsigned int x = 1u;
unsigned long y = 1ul; // 可以32位,一般64位
unsigned long z = 1LU;
unsigned long long w = 1ull; // 至少64位
unsigned long long v = 1LLU;
long a = 1l;
long b = 1L;
long long c = 1ll;
long long d = 1LL;

const char *utf8Str = u8"这是一个UTF-8字符串";
const char16_t *utf16Str = u"这是一个UTF-16字符串";
const char32_t *utf32Str = U"这是一个UTF-32字符串";
const wchar_t *wideStr = L"这是一个宽字符串";

// Usage: 24_celsius; // == 75
long long operator"" _celsius(unsigned long long tempCelsius) {
  return std::llround(tempCelsius * 1.8 + 32);
}

// Usage: "123"_int; // == 123, with type `int`
int operator"" _int(const char *str) { return std::stoi(str); }

int main() {
  // 使用_celsius字面量将摄氏温度转换为华氏温度
  long long tempFahrenheit = 24_celsius;
  std::cout << "24 degrees Celsius is " << tempFahrenheit
            << " degrees Fahrenheit.\n";

  // 使用_int字面量将字符串转换为整数
  int num = "123"_int;
  std::cout << "The integer value of the string \"123\" is " << num << ".\n";

  return 0;
}
```

### 3. Ref-qualified member functions

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

```c++
auto x = 1;
auto f = [&r = x, x = x * 10] {
  ++r;
  return r + x;
};
f(); // sets x to 2 and returns 12
```

在C++11之前，成员函数只能根据是否修改了对象的状态（即是否为const）进行重载。C++11引入了引用限定的成员函数，允许你根据*this是左值引用还是右值引用来重载成员函数。

在这个例子中，Foo类有三个getBar成员函数，它们的区别在于*this的类型：

Bar getBar() &：当*this是非const左值引用时，调用这个版本的函数。
Bar getBar() const&：当*this是const左值引用时，调用这个版本的函数。
Bar getBar() &&：当*this是右值引用时，调用这个版本的函数。
这种特性在你需要根据对象是左值还是右值来选择不同的行为时非常有用。例如，当对象是右值时，你可能希望移动（而不是拷贝）它的成员，以提高性能。

在这个例子中，当Foo对象是右值时，getBar函数会返回bar成员的移动版本，而不是拷贝版本。这可以避免不必要的拷贝，从而提高性能。

此外，这段代码还展示了C++14引入的一种新特性：初始化捕获（Init capture）。这种特性允许你在lambda表达式的捕获列表中进行初始化。在这个例子中，lambda表达式捕获了x的引用和x * 10的值。


**3. 理解decltype**

    template<typename Container, typename Index> // works, but requires refinements
    auto authAndAccess(Container& c, Index i) -> decltype(c[i])
    {
        authenticateUser();
        return c[i];
    }
    在上面的这段代码里面，C++14可以把后面的->decltype(c[i])删掉，但是auto实际推倒的类型是container而不带引用。因为 authAndAccess(d, 5) = 10这样是编译器不允许的情况。
如果想要返回引用的话，需要将上面的那一段代码重写成下面的样子：
    
    template<typename Container, typename Index> // works, but still requires refinements
    decltype(auto) authAndAccess(Container& c, Index i)
    {
        authenticateUser();
        return c[i];
    }
如果想要这个函数既返回左值（可以修改）又可以返回右值（不能修改）的话，可以用下面的写法：
    
    template<typename Container, typename Index>
    decltype(auto) authAndAccess(Container&& c, Index i){//C++14
        authenticateUser();
        return std::forward<Container>(c)[i];
    }
decltype的一些让人意外的应用：
    
    decltype(auto) f2(){
        int x = 0 ;
        return x;     // 返回的是int;
    }
    decltype(auto) f2(){
        int x = 0;
        return (x);   //返回的是int&
    }




**22. 考虑使用op=来取代单独的op运算符**

operator+ 和operator+=是不一样的，所以如果想要重载+号，就最好重载+=，那么一个比较好的方法就是把+号用+=来实现，当然如果可以的话，可以使用模板编写：
```c++
    template<class T>
    const T operator+(const T& lhs, const T& rhs)
    {
        return T(lhs) += rhs;
    }
    template<class T>
    const T operator-(const T& lhs, const T& rhs){
        return T(lhs) -= rhs; 
    }
```


**24. 理解虚函数、多重继承、虚基类以及RTTI所带来的开销**

C++的特性和编译器会很大程度上影响程序的效率，所以我们有必要知道编译器在一个C++特性后面做了些什么事情。

例如虚函数，指向对象的指针或者引用的类型是不重要的，大多数编译器使用的是virtual table(vtbl)和virtual table pointers(vptr)来进行实现

vtbl:  

    class C1{
    public:
        C1();
        virtual ~C1();
        virtual void f1();
        virtual int f2(char c)const;
        virtual void f3(const string& s);
        void f4()const
    }

vtbl的虚拟表类似于下面这样,只有虚函数在里面，非虚函数的f4不在里面：

     ___
    |___| → ~C1()
    |___| → f1()
    |___| → f2()
    |___| → f3()

如果按照上面的这种，每一个虚函数都需要一个地址空间的话，那么如果拥有大量虚函数的类，就会需要大量的地址存储这些东西，这个vtbl放在哪里根据编译器的不同而不同

vptr：

     __________
    |__________| → 存放类的数据
    |__________| → 存放vptr

每一个对象都只存储一个指针，但是在对象很小的时候，多于的vptr将会看起来非常占地方。在使用vptr的时候，编译器会先通过vptr找到对应的vtbl，然后通过vtbl开始找到指向的函数
事实上对于函数：
    
    pC1->f1();
他的本质是：

    (*pC1->vptr[i])(pC1);

在使用多继承的时候，vptr会占用很大的地方，并且非常恶心，所以不要用多继承

RTTI：能够让我们在runtime找到对象的类信息，那么就肯定有一个地方存储了这些信息，这个特性也可以使用vtbl实现，把每一个对象，都添加一个隐形的数据成员type_info，来存储这些东西，从而占用很大的空间

### 4. release模式防止变量被优化
    volatile

### 5. 函数遮蔽

* 什么是函数遮蔽？
函数遮蔽（Function Hiding）是指在派生类中定义一个与基类中同名的函数，这会导致基类中的同名函数在派生类中被隐藏。即使基类中的函数和派生类中的函数具有不同的参数列表，基类中的函数也会被隐藏。

* 什么是静态绑定？
静态绑定（Static Binding），也称为早期绑定（Early Binding），是在编译时决定函数调用的绑定方式。静态绑定通常用于非虚函数调用，编译器在编译时确定函数调用的具体实现。

* 对于一个非虚函数，如果父类和子类都声明了这个同名函数方法，不管参数列表是否相同，都是调用的静态绑定的方法。

* c++怎么处理函数调用？
首先进行名称查找（Name Lookup），然后才是类型匹配（Type Matching）：

1. **名称查找**：编译器首先查找与函数调用匹配的函数名。这一步不考虑函数的参数类型。如果在派生类中找到了同名函数，名称查找就会停止，不再继续到基类中查找。
2. **类型匹配**：一旦找到了同名函数，编译器接下来会根据函数调用的实参类型，从找到的函数中选择最合适的一个进行调用。

* 如果想保留父类和子类的同名方法，又不用虚函数，请使用using

### 6. 通过引用捕获异常

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


这段文字讨论了在 C++ 中抛出异常、传递参数和调用虚函数之间的不同点，特别是它们在处理方式和行为上的差异。以下是对这段文字的详细解释：

### 7. 传递参数和捕获异常的相同点和不同点

* **相同点**

传递参数和捕获异常的方式可以是传值、传引用或者传指针。例如：

- 传递参数的函数：
  ```cpp
  void f1(Widget w);
  ```

- 捕获异常的 [`catch`]子句：
  ```cpp
  catch(Widget w)...
  ```

这两种方式都可以通过传值、传引用或传指针来进行参数传递或异常捕获。

* **不同点**

- **控制权的返回**：
  - 调用函数时，程序的控制权会返回到函数的调用处。
  - 抛出异常时，控制权永远不会回到抛出异常的地方。

* **三种捕获异常的方法**

1. **传值捕获**：
   ```cpp
   catch(Widget w);
   ```
   - 捕获异常对象的副本。

2. **传引用捕获**：
   ```cpp
   catch(Widget& w);
   ```
   - 捕获异常对象的引用。

3. **传常量引用捕获**：
   ```cpp
   catch(const Widget& w);
   ```
   - 捕获异常对象的常量引用。

* **捕获异常的注意事项**

- 一个被抛出的对象可以通过普通的引用捕获，不需要通过指向 [`const`]对象的引用捕获。
- 在函数调用中，不允许传递一个临时对象到一个非 [`const`]引用类型的参数中。
- 异常抛出时实际上是抛出对象创建的临时对象的拷贝。

* **类型转换**

在 [`try`]语句块中，抛出的异常不会进行类型转换（除了继承类和基类之间的类型转换，以及类型化指针转变成无类型指针的转换）。例如：

```cpp
void f(int value) {
    try {
        throw value; // value 可以是 int 也可以是 double 等其他类型的值
    }
    catch(double d) {
        // 这里只处理 double 类型的异常，如果遇到 int 或者其他类型的异常则不予理会
    }
}
```

在这个例子中，[`catch`]子句只处理 [`double`]类型的异常，如果抛出的是 [`int`]类型的异常，则不会被捕获。

* **捕获异常的顺序**

异常捕获是按照顺序进行的。如果有多个 [`catch`]子句，程序会优先进入第一个匹配的 [`catch`]子句。例如：

```cpp
try {
    // 可能抛出异常的代码
}
catch(const std::exception& e) {
    // 捕获 std::exception 类型的异常
}
catch(...) {
    // 捕获所有类型的异常
}
```

在这个例子中，如果抛出的是 `std::exception` 类型的异常，会优先进入第一个 [`catch`]子句。如果没有匹配的 [`catch`]子句，则会进入第二个捕获所有类型异常的 [`catch`]子句。

* **总结**

- **传递参数和捕获异常的方式**：可以是传值、传引用或传指针。
- **控制权的返回**：函数调用会返回控制权，异常抛出不会。
- **捕获异常的方法**：可以通过传值、传引用或传常量引用捕获异常。
- **类型转换**：异常抛出时不会进行类型转换，除了继承类和基类之间的类型转换。
- **捕获顺序**：异常捕获是按照顺序进行的，优先进入第一个匹配的 [`catch`]子句。

通过理解这些差异，可以更好地编写和调试 C++ 程序，确保异常处理机制的正确性和有效性。

### 8. placement new

placement new 是 C++ 中的一种特殊的 new 运算符，用于在指定的内存位置上构造对象，而不分配新的内存。它的意义在于提供了对内存管理的精细控制，允许程序员在预先分配的内存块上构造对象。这在某些高性能、内存受限或需要自定义内存管理的场景中非常有用。

```cpp
#include <iostream>
#include <new>  // 用于 placement new
#include <string>

// 定义一个联合体，包含复杂类型
union ComplexData {
    int intValue;
    float floatValue;
    std::string strValue;

    // 默认构造函数
    ComplexData() {}

    // 析构函数
    ~ComplexData() {}
};

int main() {
    ComplexData data;  // 创建一个联合体实例

    // 使用 placement new 在指定内存位置上构造 std::string 对象
    new (&data.strValue) std::string("Hello, Complex Union");
    std::cout << "data.strValue: " << data.strValue << std::endl;

    // 显式调用 std::string 的析构函数
    data.strValue.~std::string();

    return 0;
}
```

* **常用场景**

1. **内存池**：
   - 在内存池中预先分配一大块内存，然后使用 `placement new` 在这块内存上构造对象。这样可以减少频繁的内存分配和释放，提高性能。

2. **联合体**：
   - 在联合体中管理复杂类型的对象。由于联合体的所有成员共享同一块内存，需要使用 `placement new` 显式调用构造函数，并在对象生命周期结束时显式调用析构函数。

3. **自定义内存管理器**：
   - 在自定义内存管理器中，使用 `placement new` 在预先分配的内存块上构造对象，以便更精细地控制内存分配和释放。

4. **嵌入式系统**：
   - 在嵌入式系统中，内存资源有限，使用 `placement new` 可以更高效地利用内存，避免不必要的内存分配和释放。

* **注意事项**

- **内存管理**：使用 `placement new` 时，需要确保提供的内存足够大以容纳对象，并且在对象生命周期结束时显式调用析构函数。
- **未定义行为**：如果在同一块内存上多次使用 `placement new` 而不调用析构函数，可能会导致未定义行为。
- **用途**：`placement new` 常用于内存池、联合体和自定义内存管理器等场景。

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


### 9. 尾回归类型
```c++
#include <iostream>

void f(...) { std::cout << "fallback\n"; }

template <class T>
auto f(T t) -> decltype((void)(t.x), void()) {
    std::cout << "has x member\n";
}

struct A {
    int x;
};
struct B {};

int main() {
    f(A{});  // 输出 "has x member\n"
    f(B{});  // 输出 "fallback\n"
    return 0;
}

/*
在现代C++中，尾置返回类型（trailing return type）主要用于以下几种情况：

1. 当返回类型依赖于函数参数类型时，尤其是在模板函数中，这可以提供更清晰的语法。
2. 在Lambda表达式中，尤其是当返回类型不容易直接推断时。
3. 当函数返回类型较复杂时，使用尾置返回类型可以提高代码的可读性。
*/
```

### 10. ADL
```c++
#include <iostream>

// 模板编程通过类型可以找到对应的函数(如不同命名空间下的),这个就叫做ADL.
// 下面这个例子展示了如何通过模板编程和ADL，使得模板函数能够在不知道具体类型的情况下，利用参数的类型在相应的命名空间中查找相应的函数。

namespace MyNamespace {
    struct MyType {};

    void someFunction(MyType myArg) {
      std::cout << "Function in MyNamespace called" << '\n';
    }
}

template <typename T>
void myTemplateFunction(T arg) {
    someFunction(arg); // 依赖于ADL查找someFunction
}

int main() {
    MyNamespace::MyType obj;
    myTemplateFunction(obj); // 调用myTemplateFunction
    return 0;
}
```

### 99. books

* [C++程序设计语言_特别版](http://pan.baidu.com/s/1o6jX3iq)
* [C++编程惯用法__高级程序员常用方法和技巧](http://pan.baidu.com/s/1i3sVhJZ)
* [C++编程规范-101条规则准则与最佳实践](http://pan.baidu.com/s/1ntDfM21)
* [C++语言的设计和演化](http://pan.baidu.com/s/1kT3a2dp)
* [C++释难解惑](http://pan.baidu.com/s/1nt4ssrf)
* [C和C++安全编码(中文版)](http://pan.baidu.com/s/1hqqVtp6)
* [Exceptional C++ Style(Herb Sutter).中文版](http://pan.baidu.com/s/1qWCtFOC)
* [Exceptional C++ 中文版](http://pan.baidu.com/s/1pLCHC)
* [More Exceptional C++(中文版)](http://pan.baidu.com/s/1qWLNgZE)
* [Linux C编程一站式学习6.14--宋劲衫](http://pan.baidu.com/s/1bny7ga7)
* [从缺陷中学习C/C++](http://pan.baidu.com/s/1c0GLTOs)
* [你必须知道的222个C++语言问题.范立锋.扫描版](http://pan.baidu.com/s/1c03oHVE)
* [深入学习:GNU C++ for Linux 编程技术](http://pan.baidu.com/s/1dDkVKVB)
* [编写高质量代码  改善C++程序的150个建议.李健.扫描版](http://pan.baidu.com/s/1pJlXxk3)
* [Accelerated C++中文版 ]
* [Advanced c++ Programming  Styles and Idioms中文版]
* [C++ API设计]
* [C++代码设计与重用]
* [C++标准库__自学教程与参考手册(第2版)英文版]
* [C++沉思录(Ruminations on C++)中文第2版]
* [C++设计新思维(Modern_C++_Design)]
* [大规模C++程序设计]
* [模板编程与OO编程范型--混搭]
* [深度探索C++对象模型]
* [高质量C++／C编程指南]
* [Imperfect C++]