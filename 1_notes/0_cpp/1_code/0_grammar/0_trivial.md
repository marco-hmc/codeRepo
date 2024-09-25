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