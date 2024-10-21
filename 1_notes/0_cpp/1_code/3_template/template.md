## template


### 1. SFINAE
模板参数推导和替换失败不是错误（SFINAE，Substitution Failure Is Not An Error）。
所以模板替换不是错误，是指模板实例化的时候如果和当前的模板函数匹配错误，不算失败，会继续尝试和其他模板匹配并完成实例化，但是如果没有任何一个模板函数能够完成模板实例化，还是会出现编译错误。
简单来说，当模板实例化过程中发生了类型不匹配或者无法进行某种操作时，这种情况被视为替换失败，而不是一个编译错误。编译器会忽略这个失败的实例化尝试，继续寻找其他可能的模板重载或特化来尝试匹配。如果最终没有任何模板能够匹配，那么编译器才会报错。这个机制允许模板库的设计者编写出更加灵活和通用的代码，通过重载和特化来处理不同的类型和操作。

而选择用哪一个完成模板实例化的能力，叫做重载决议。那重载决议有什么关键点呢？
* 实参的推断要求一致，其本身不会为了编译通过自动做类型转换 在进行重载决议时，编译器会尝试匹配函数调用中实参的类型与各个重载函数形参的类型。这个过程中，虽然某些隐式类型转换是允许的（如从int到double），但编译器不会进行过于复杂的转换尝试。实参类型需要与某个重载版本的形参类型足够“接近”，否则该重载版本不会被选中。这意味着，如果没有任何一个重载版本能够直接或通过简单的隐式转换与实参类型匹配，重载决议会失败。

* 只有在函数调用前声明的重载才会被匹配，即使后续有更优先的匹配，由于不可见也会被忽略。在C++中，函数的可见性是基于声明的位置的。如果在调用一个重载函数时，编译器只能“看到”那些在调用点之前声明的重载版本。即使在调用点之后有一个“更好”的重载版本，由于它在调用时不可见，编译器不会考虑它。这强调了声明顺序的重要性，以及在编写库或大型程序时组织代码的方式。

* 最佳匹配原则：在所有可见的重载函数中，编译器会根据实参和形参的匹配程度来选择“最佳匹配”。这个选择过程考虑了参数的类型、数量、是否有默认参数等因素。如果有多个重载函数同样适合，但没有一个能被确定为最佳匹配，那么会导致编译错误，因为这种情况被认为是模糊的。

* 模板特化和偏特化：对于模板函数，重载决议还会考虑模板特化和偏特化。如果存在特化版本的模板函数，它们通常会被优先考虑，因为特化提供了更具体的实现。

* 参数类型退化：在函数模板重载决议中，参数类型可能会经历退化。例如，数组类型的参数会退化为指针，函数类型的参数会退化为函数指针。这种退化行为可能会影响哪个重载版本被选择。

* 引用折叠和转发引用：C++11引入了转发引用（Forwarding References）和引用折叠规则，这对于模板函数的重载决议尤其重要。转发引用允许函数模板完美地转发参数到另一个函数，而引用折叠规则决定了当模板参数被推导为引用时的行为。这些特性使得模板函数可以更灵活地处理不同的参数类型，包括左值和右值。

* constexpr函数：从C++11开始，constexpr函数提供了在编译时进行计算的能力。在重载决议中，如果一个constexpr函数能够在编译时解析，它可能会被优先选择，这使得编译时优化和运行时性能得到提升。


### 2. 变长参数模板

### 99. quiz
#### 1. std::void_t的实现和用法
```c++
namespace std {
    template<typename... Ts> using void_t = void;
}
```
常用于编译时检查一个类型是否具有某个特定的成员类型、成员函数或属性。
例如，你可以这样使用它：

```c++
struct A { using type = int; };
struct B {};

static_assert(has_type<A, std::void_t<A::type>>::value, "A has a member named type");
static_assert(!has_type<B, std::void_t<B::type>>::value, "B does not have a member named type");
```

#### 2. std::enable_if的实现和用法
```c++
namespace std {
    template<bool B, class T = void>
    struct enable_if {};

    template<class T>
    struct enable_if<true, T> { typedef T type; };
}
```

std::enable_if的第一个参数是一个编译时常量表达式，用于控制是否启用某个函数或类型。
如果表达式为true，std::enable_if将有一个名为type的成员类型，等同于它的第二个参数（如果提供）。

```c++
template <typename T>
typename std::enable_if<std::is_integral<T>::value, T>::type
process(T value) {
    std::cout << "处理整数: " << value << std::endl;
    return value;
}

template <typename T>
typename std::enable_if<std::is_floating_point<T>::value, T>::type
process(T value) {
    std::cout << "处理浮点数: " << value << std::endl;
    return value;
}
```

`std::enable_if_t`另一个常见的用法是用来开启模板

```c++
template <
  class Foo, 
  class Bar, 
  typename = std::enable_if_t<xxx>
>

```
typename =的用法定义了一个默认模板参数，这个参数的存在依赖于std::enable_if_t表达式的结果。如果xxx的结果为true，则这个模板重载被启用；否则，由于SFINAE，这个模板重载被编译器忽略，不会参与到重载解析中。这样，开发者可以根据类型特征在编译时控制模板的选择和使用。

#### 3. std::declval的实现和用用法
```c++
// std::declval的实现
namespace std {
    template<class T>
    add_rvalue_reference_t<T> declval() noexcept; // 仅声明，无需定义
}
```


std::declval是一个在编译时用于类型推断的工具，它可以用来获取一个类型的引用，而不需要实际构造该类型的对象。这在处理无法默认构造或不想构造对象的类型时特别有用。上述代码展示了std::declval的实现（实际上是一个未定义的函数模板，仅用于类型推断）和一个使用场景，即推断类成员函数的返回类型。

```c++
#include <iostream>
#include <type_traits>

// 示例类
class MyClass {
public:
    int myFunction() const {
        return 42;
    }
};

// 用于在编译时推断成员函数的返回类型
template <typename T>
auto testFunctionReturnType() -> decltype(std::declval<T>().myFunction()) {
    // 注意：这里不会实际调用T::myFunction，因此可以用于不可默认构造的类型
    return std::declval<T>().myFunction();
}

int main() {
    // 验证推断的类型是否为int
    static_assert(std::is_same<decltype(testFunctionReturnType<MyClass>()), int>::value, "返回类型应为int");
    std::cout << "推断的返回类型为int" << std::endl;
    return 0;
}
```

#### 4. 

在C++标准库中，除了[`std::declval`](command:_github.copilot.openSymbolFromReferences?%5B%7B%22%24mid%22%3A1%2C%22path%22%3A%22%2Fhome%2Fmarco%2F1_myNotes%2FcodeRepo%2F1_notes%2F0_cpp%2F1_code%2F3_template%2Ftemplate.md%22%2C%22scheme%22%3A%22file%22%7D%2C%7B%22line%22%3A124%2C%22character%22%3A0%7D%5D "1_notes/0_cpp/1_code/3_template/template.md")、[`std::enable_if`](command:_github.copilot.openSymbolFromReferences?%5B%7B%22%24mid%22%3A1%2C%22path%22%3A%22%2Fhome%2Fmarco%2F1_myNotes%2FcodeRepo%2F1_notes%2F0_cpp%2F1_code%2F3_template%2Ftemplate.md%22%2C%22scheme%22%3A%22file%22%7D%2C%7B%22line%22%3A124%2C%22character%22%3A0%7D%5D "1_notes/0_cpp/1_code/3_template/template.md")和[`std::void_t`](command:_github.copilot.openSymbolFromReferences?%5B%7B%22%24mid%22%3A1%2C%22path%22%3A%22%2Fhome%2Fmarco%2F1_myNotes%2FcodeRepo%2F1_notes%2F0_cpp%2F1_code%2F3_template%2Ftemplate.md%22%2C%22scheme%22%3A%22file%22%7D%2C%7B%22line%22%3A124%2C%22character%22%3A0%7D%5D "1_notes/0_cpp/1_code/3_template/template.md")之外，还有许多专门用于模板元编程的类模板和类型特征。以下是一些常用的：

1. **std::conditional**
   ```c++
   template< bool B, class T, class F >
   using conditional = typename conditional<B,T,F>::type;
   ```
   根据布尔常量`B`的值选择两种类型之一。

2. **std::is_same**
   ```c++
   template< class T, class U >
   struct is_same;
   ```
   检查两个类型是否相同。

3. **std::remove_reference**
   ```c++
   template< class T >
   struct remove_reference;
   ```
   移除类型的引用修饰符。

4. **std::remove_const**
   ```c++
   template< class T >
   struct remove_const;
   ```
   移除类型的`const`修饰符。

5. **std::integral_constant**
   ```c++
   template<class T, T v>
   struct integral_constant;
   ```
   表示一个编译时常量值。

6. **std::is_base_of**
   ```c++
   template< class Base, class Derived >
   struct is_base_of;
   ```
   检查一个类型是否是另一个类型的基类。

7. **std::is_convertible**
   ```c++
   template< class From, class To >
   struct is_convertible;
   ```
   检查一个类型是否可以转换为另一个类型。

8. **std::decay**
   ```c++
   template< class T >
   struct decay;
   ```
   将类型转换为它的“衰减”类型，模拟通过值传递参数时的类型转换。

这些工具和类型特征在模板元编程中非常有用，它们可以帮助开发者编写出更通用、更灵活的模板代码。


**44. 将与参数无关的代码抽离templates （Factor parameter-independent code out of templates)**

主要是会让编译器编译出很长的臃肿的二进制码，所以要把参数抽离，看以下代码：
    
    template<typename T, std::size_t n>
    class SquareMatrix{
        public:
        void invert();    //求逆矩阵
    }
    
    SquareMatrix<double, 5> sm1;
    SquareMatrix<double, 10> sm2;
    sm1.invert(); 
    sm2.invert(); //会具现出两个invert并且基本完全相同

修改后的代码：
    
    template<typename T>
    class SquareMatrixBase{
        protected:
        void invert(std::size_t matrixSize);
    }
    
    template<typename T, std::size_t n>
    class SquareMatrix:private SquareMatrixBase<T>{
        private:
        using SquareMatrixBase<T>::invert;  //避免遮掩base版的invert
        public:
        void invert(){ this->invert(n); }   //一个inline调用，调用base class版的invert
    }

当然因为矩阵数据可能会不一样，例如5x5的矩阵和10x10的矩阵计算方式会不一样，输入的矩阵数据也会不一样，采用指针指向矩阵数据的方法会比较好：
    
    template<typename T, std::size_t n>
    class SquareMatrix:: private SquareMatrixBase<T>{
        public:
        SquareMatrix():SquareMatrixBase<T>(n, 0), pData(new T[n*n]){
            this->setDataPtr(pData.get());
        }
        private:
        boost::scoped_array<T> pData; //存在heap里面
    };

总结：
+ templates生成多个classes和多个函数，所以任何template代码都不该与某个造成膨胀的template参数产生依赖关系
+ 因非类型模板参数（non-type template parameters）而造成的代码膨胀，往往可以消除，做法是以函数参数后者class成员变量替换template参数
+ 因类型参数（type parameters）而造成的代码膨胀，往往可以降低，做法是让带有完全相同的二进制表述的具现类型，共享实现码


#### 5. 学习处理模板化基类内的名称

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