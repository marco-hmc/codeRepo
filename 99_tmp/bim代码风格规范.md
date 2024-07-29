## c++通用规范

这次培训从三个层次展开
1. 写出符合格式规范的代码
2. 写出好的代码
3. 个人经验分享

### 1. BIM代码规范
#### 1. 命名规范
* 不要乱用缩写,如果用了缩写，确保是英文语境下通用的缩写，而不是自己创造的缩写
```c++
    class ObjectId;
    ObjectId defId;
    ObjectId tarId;
    ObjectId tgtId;
    void xlateObject();
```
* 缩写命名的大小写情况
```c++
    // 一般原则上, 连续缩写的，最后一个字母小写，如下面的PCDB,CCTV例子
    class BmCCTvCmd; // 
    class BmPCDbFoo; // Project coloration database
    auto objId = barId();
```
* 原则上而言，现代c++风格规范都是摈弃匈牙利风格的了，但是代码沿袭下来的习惯而言，指针变量和布尔变量的命名前面还是带着类型。
* 函数/变量命名多考虑动宾结构`checkStatus()`，不考虑时态，没有三单，但需要注意词性
* 类型-大驼峰
* 函数-小驼峰
* 全局变量-小驼峰
* 静态变量-无特殊函数
* 宏-大写+下划线
* 枚举值-k+大驼峰

```c++
// bim_module_train.cpp
#define BIM_XXX_XXX 1

struct BmModuleAXXX
{

};

class BmBar;

int g_foo;  // g前缀一般用于全局变量

enum 
{
    kOne,
    kTwo
}

void useFoo()
{
    int foo;
    static int bar;
};
```

#### 2. 格式规范
* utf8编码
* 4空格，不用tab
* 所有for,if的执行体都用{}括住，哪怕就一行
    ```c++
    if (xxx)
    {
        return xxx;
    }
    ```
* 换行
    * for和if结尾的}一般换一行，嵌套且连续的不换
    * 文件结尾一个空行
    ```c++
    if (xxx)
    {
        if (xxx)
        {

        } // 嵌套且连续的不换
    }

    if (xxx)
    {

    } // 不嵌套，换一行

    for (xxx)
    {

    }

    ```

* switch语句规范
    ```c++
    switch ()
    {
        case BmEnum::kCase1:
        {
            ...
            break;
        }

        case BmEnum::kCase2:
        {
            ...
            break;
        }

        default:
        {
            break;
        }
    }
    ```

#### 3. 引用规范
* 引用顺序
  * 自己
  * 同模块
  * bim其他模块
  * 平台模块
  * stl
  ```c++
  #include "bm_moduleA_self.h"

  #include "bm_moduleA_aaa.h"
  #include "bm_moduleA_bbb.h"

  #include "bm_moduleB_aaa.h"
  #include "bm_moduleC_bbb.h"

  #include "wukong_moduleA_aaa.h"
  #include "wukong_moduleB_aaa.h"

  #include <map>
  ```
* 原则和原因
  * 把不稳定性的提前发现出来
  * 同等级的头文件按顺序排，

* 不引用多余头文件
  * vs-resharper插件可以检查
  * vs code-clangd插件可以检查

#### 4. 类的设计规范
* 三五零原则
  * 如果一个类需要自定义析构函数、拷贝构造函数或拷贝赋值运算符中的任何一个，那么它很可能需要自定义所有这三个。
    这是因为这个类可能管理着它自己的资源，如动态内存，需要确保复制和销毁的正确性。
  * C++11引入了移动语义和两个新的特殊成员函数：移动构造函数和移动赋值运算符。
    因此，如果你的类需要自定义析构函数、拷贝构造函数、拷贝赋值运算符中的任何一个，为了完全支持移动操作，你也应该考虑提供移动构造函数和移动赋值运算符。
  * "零法则"建议类不应该自定义任何特殊的成员函数，而是应该使用现有的资源管理类（如std::string、std::vector等）或智能指针（如std::unique_ptr、std::shared_ptr）来管理资源。
    遵循这一原则可以使得资源管理更加简单、安全。

* 什么时候使用继承，什么时候使用组合？

* 什么时候使用多继承？什么时候继承是非pubic的？

* 成员函数形参，如果不涉及所有权，能用`const T&`或者`T&`就这引用类型的

* 不改变成员变量的，且意图也是不能修改成员变量的成员函数，用`const`修饰

* `friend`会增加耦合，慎用

* 类的成员变量用`m_`前缀

* 单个形参的构造函数用`explicit`

* `final`, `default`, `delete`该用就用

* 不建议在头文件使用inline给出短函数的实现
    * 现代C++编译器会自己决定是否inline，你的inline用法，只是建议编译器怎么做，编译器可能会忽略的，而编译器肯定比我们聪明。
    * 头文件使用inline函数给出实现，不方便调试。

#### 5. 现代C++的使用
1. **what's too much for `auto`?**
    * 不要用auto处理&的
    * 简单类型，还是不要用auto
    * 一般不要用auto去接函数返回值
    * 类型信息不重要/ 类型信息被变量名包含时，可以看情况用 
    * 减少信息重复度时可以用
    ```c++
    Vector<Foo> bmBar;
    std::for_each(bmBar.begin(), bmBar.end(), [](const auto& bar){...})

    auto enumType = static_cast<int>getEnumType();
    ```

2. **std::bind还要不要用？**
   `std::bind`在C++11中引入，用于生成可调用对象。但随着C++14引入的lambda表达式的增强，`std::bind`的使用变得不那么频繁。Lambda表达式通常提供了一种更清晰、更直接的方式来实现相同的功能。因此，除非有特定的理由，否则推荐使用lambda表达式代替`std::bind`。
   ```c++

   auto foo1 = [](int a, int b) { return a+b; };

   int aVal = 5;
   auto foo2 = [foo1, aVal](int b){ return foo1(aVal, b); };
   auto bar2 = std::bind(foo1, std::placeholders::_1, aVal);
   ```
   但是使用lambda时注意捕捉值还是引用，以及对象生命周期的问题

3. **push_back还是emplace_back?**
   `push_back`和`emplace_back`都用于向容器添加元素，但`emplace_back`可以直接在容器内构造元素，避免了额外的复制或移动操作。因此，当需要构造而非复制元素到容器时，`emplace_back`通常是更高效的选择。然而，如果已经有一个对象实例，使用`push_back`可能更直观。

4. **cast的使用**
    * static_cast：用于编译时可以确定类型的转换，有一定的安全检查。多用于向上转换，基本类型转换
    * dynamic_cast: 用于运行时的类型转换，有更强的安全检查能力。多用于向下转换
    * reinterpret_cast: 多用于将指针转为整数、地址、void*之类的，用于区分动态静态转换意图，表明是重新解释。一般成对出现使用。
    ---
    * bim这里不用dynamic_cast
      * dynamic_cast依赖type_info，运行时的执行，性能大一些。
      * dynamic_cast一般是判断父类是否能安全转子类的，用了这个就说明类的设计不太对。需要改。
    * bim有自己的类型识别系统，这个能力是类似于反射的概念
      * 反射：运行时能够获取自己的类型信息，更强一点的反射，可以知道自己对象的属性和方法，并调用。
      * bim的类型识别系统简述：通过宏的方式注册，注册完之后会有一个类似于classDictionary的字典记录派生结构以及一定的类型信息，具体体现如下
      ```c++
        BmBar::desc() // 类型信息
        class BmFoo : public BmBar;
        BmFoo->isSubClassOf(BmBar::desc()) // 派生结构关系
        BmFoo* foo = new BmFoo();

        // 
        void abc(BmBar* bar) 
        {
            auto foo = BmBar::cast(bar);
        }

        abc(foo);
      ```

5. **map在右边的时候要慎重使用**
    ```c++
    // 不要把map放在右边用，建议用find
    if (curObj == myMap[idx])
    ```

6. **常量的表示方法**
    ```c++
    // A. 宏定义方法
    #define MAXSIZE 100
    class MyClass {
    public:
        int arr[MaxSize];
        // ...
    };

    // B. 更通用的
    class MyClass {
    public:
        static const int MaxSize = 100;
    public:
        int arr[MaxSize];
        // ...
    };

    // C. c11前, enum hack
    class MyClass {
    public:
        enum { MaxSize = 100 };
    public:
        int arr[MaxSize];
        // ...
    };

    // D. c11及以后
    class MyClass {
    public:
        static constexpr int MaxSize = 100;
        // ...
    public: 
        int arr[MaxSize];
    };
    ```
    四种方法的优缺点是什么？
    BIM目前用的是A，D方式。
    D方法中的static有什么用？有没有其他方式？

#### 6. 宏的使用
* 宏的实现是不便于调试的，如果宏里面有你可能需要关心的变量状态，状态流的跳转，不要上宏。
* 数字常量，字符串常量，一般是使用宏定义的方式，而不是`const xxx`的方式。一是因为历史原因，统一规范。二是为了便于检索。
* 不能用带副作用的宏。
  ```c++
  // 带副作用的宏，容易使用错，一般不要用这种带控制语句，或者修改入参的宏，这些行为叫副作用行为。
  #define BIM_CHECK_OK(input) \
    if ((input) != "ok")        \
    {                           \
        return false;           \
    }
  
  // 对于宏函数，有部分规范认为如果实在要用宏函数的话，会强调用do while(0)套起来，但bim这里不强调。为什么？
  #define BIM_FOO_BLOCK(block) \
  do                                 \
  {                                  \
    ...                              \
  }                                  \
  while (0)

  // 但是对于宏函数内部有变量声明的，最好还是使用括号括起来。
  #define BIM_BAR_BLOCK(block) \
  {                                  \
    ...                              \
  }                                  

  ```

#### 7. 杂项
* CMakeLists.txt按照名称排序，避免合并冲突
* rxClass初始化顺序，父类init>子类init，先init的后uninit.
* #include什么时候用"",什么时候用<>
* 没有使用的参数，用BIM_UNUSED()
* 临时代码，临时方案，用BIM_TO_DO
* 用using，而不是typedef
* UUID全用大写。
* 异常安全
   编写异常安全的代码意味着即使在面对异常抛出的情况下，程序也能保持一致的状态，不会泄露资源或导致数据损坏。
   实现异常安全通常涉及到三个级别：
    * 基本保证：出现异常不影响
    * 强保证：出现了异常通过guard, transaction等操作会回滚到初始状态
    * 不抛出：不会出现异常
 在设计和实现代码时，应该考虑其对异常的处理方式，确保资源管理正确（如使用智能指针）。
* 函数内部是const类型的，就用const
    ```c++
    const bool isFinished = getFinishedFlag()
    ```
* 变量左边还是变量右边
    ```c++
    #define STATUS_OK true
    #define STATUS_ERROR false
    if (STATUS_OK == stat) // 老的风格规范，避免将==写成=，如果对左值使用=就会报错
    if (stat == STATUS_OK) 
    // 新的风格规范，编译器一般会对上面情况给出警告，但是警告太多了，不一定会看的。
    // 特别是todo项也给出了警告，未使用参数也给出警告。所以有人不用。
    // 但是现在新的ide会对下面`if (a=1)`单独给出警告了，但又不是每个人的ide都有这种功能
    ```
* 字符串用公司封装的String，不用std::string
  * C11之前的std::string实现用了一些优化，是写时复制的，是非线程安全的。而且std::string设计上是有一定问题的，所以都用公司封装的。
  * 除此之外string有编码问题，api是严禁使用stl的，就是类的public方法，对外的方法不能用std::string
  * 而内部的尽量使用平台已提供的容器，如果有性能开销，可以考虑使用stl
* 对于容器来说：
  * 内存连续存储的容器一般都是用公司封装的Array。
  * 理论上来说，有序数据容器用map，无序的话用unordered_map，bim目前没要求。
* 字符串使用ZW_T("")宏封装
    ```c++
    #define ZW_T(x) L ## x
    String str = ZW_T("xxx");
    ```
*  不要随便用c++黑魔法
    ```c++
    for (int i = 0; i < n; i++) 
    {
        cout << ans[i] << " \n"[i == n - 1]; 
    }
    ```
    c++黑魔法一般指利用隐式转换，编译器特殊行为，位操作等。
    黑魔法会使得可读性极差，实在不行也要用函数封装起来。

---

### 2. 怎么写出好代码
#### 2.1 遵守代码设计原则
* 代码实现原则
  * 低重复
    * 不存在不会被修改和删除的代码，修改重复代码的时候，如何避免遗漏是很头疼的。
    * 只能事先尽可能降低重复代码
  * 圈复杂度低
    
    * 多层嵌套if-else很难读的
  * 代码可读（代码可维护）
    ```c++
    if (Math::isZero((pnt2-pn1)*line)) // not east for understanding.
    if (isVertical(pnt2-pnt1, line)) // easy for understanding
    ```
    可读性强意味着可维护性强，不要写出让别人看不懂的代码。复杂的逻辑要写注释
  * 

---
* 设计原则
  * 高内聚，低耦合
  * 迪米特法则
    * 一个类尽可能少调用其他对象的方法
    * 不要直接暴露对象内部结构
  * SOLID原则
    * single responsibility
      * 单一职责
    * open/closed responsibility
      * 扩展开发，修改封闭
    * liskov substitution
      * 里氏替换，子类能够替换父类
    * interface segregation
      * 接口隔离，调用方不应该被强迫使用不需要的接口，即被调用方的接口应该尽可能小和具体的接口，而不是一个笼统的大的接口。
    * dependency inversion
      * 依赖倒置，高层不应该依赖于底层

#### 2.2 卫语句
```c++
// 使用了卫语句
void foo()
{
    if (!isValid())
    {
        return;
    }

    if (isA())
    {
        ...
    }
}

// 没使用卫语句
void bar()
{
    if (isValid())
    {
        if (isA())
        {
            ...
        }
    }
}
```


### 3. 个人经验
#### 3.1 代码阅读上
* 查看继承，查找所有引用，跳转定义，智能提示ctrl+enter
* refactor: F2, change signature, extract function
* 正则搜索：
    `word1(?:.*\){0,10}.*word2` // 匹配word1开头，word2结尾，两个单词相差行数在0到10行的字符串
    `foo\(.*::kEnum1`  // 用于匹配某一个函数使用特定枚举值的
    (?<!d)ESC(?!md|on) // 带ESC，开头没有d,后面没有md或者on

#### 3.2 代码开发上
* 熟悉stl
    * container
    * iterator
    * algorithm
    * functor
    * type_traits
* 知道pimpl, D/Q指针，raii，反射，序列化/反序列化，命令工厂概念
* 类的成员变量多通过get/set的方法去暴露，特别是set方法对于调试来说是很有意义的。

#### 3.3 工具使用上
* git
    * 多用rebase而不是merge，如果是多人合作的分支，或者确定有其他人拉了你的分支，建议用merge
    * `git push --force-with-lease`
    * 多用`git stash`
    * `git alias`
    * `gitjk`
* sniPaste
* everything
* spaceSniffer

#### 3.4 个人偏好
* 一般而言，前向声明来减少不必要的头文件引用是没太大意义的
  * 如果一个类本身是属于私有和保护的，可以用

* 明确控制流
```c++
SystemStatus doSomething()
{
    auto ss = SystemStatus::Err_Ok;
    ss = subStage1();
    if (!BIM_SUCCESS(ss))
    {
        return ss;
    }

    ss = subStage2();
    if (!BIM_SUCCESS(ss))
    {
        return ss;
    }

    return SystemStatus::Err_Ok;
}
```

##### 3.4.1 类成员变量的初始化

类成员变量的初始化方式取决于具体情况和编码风格。两种主要的初始化方式是：
* 在头文件中直接初始化
* 在构造函数的初始化列表中初始化。

* 在头文件中直接初始化（非静态成员变量）
优点：
- **简洁性**：代码更简洁，易于理解，尤其是对于默认值。
- **减少错误**：确保即使添加了新的构造函数，成员变量也总是有初始值，减少忘记初始化成员变量的错误。
- **统一初始化**：对于所有构造函数，成员变量的初始值都是一致的，除非在构造函数初始化列表中明确指定了其他值。

```c++
class Example {
public:
    Example() = default;
    explicit Example(int val) : m_value(val) {}

private:
    int m_value{0}; // 在头文件中直接初始化
};
```

* 在构造函数的初始化列表中初始化
优点：
- **灵活性**：允许基于不同的构造函数参数进行不同的初始化。
- **性能**：对于某些类型（尤其是容器和复杂对象），在初始化列表中初始化可以更高效，因为它避免了先默认初始化然后再赋值的过程。
- **依赖关系**：如果成员变量的初始化依赖于构造函数的参数或者其他成员变量的值，初始化列表是必须的。

```c++
class Example {
public:
    Example(int val) : m_value(val) {} // 在构造函数的初始化列表中初始化

private:
    int m_value;
};
```

这两种都有人用，但是最好在一个文件内部，统一使用同一种风格。

### 99. 习题

#### 1. 函数/ 变量命名
```c++
// 返回成员变量Bar bar值的函数怎么命名好，四选二
Bar getBar();                   // A
void getBar(Bar& bar);          // B
SystemStatus getBar(Bar& bar);  // C
Bar barValue();                 // D
```

```c++
// 一个变量用于判断是否需要提前跳出，下面哪一个变量命名最不好
bool earlyExit;                 // A
bool breakFlag;                 // B
bool shouldExit;                // C
bool exitEarly;                 // D
bool isBreak;                   // E
bool onlyContinueIfYes          // F
```

```c++
// bim风格命名，下面要改成bim风格的
// db_wall.cpp
class Wall
{
    public:
        bool isModified;
        ObjectId wallId;
};

```

#### 2. 格式化 
```c++
// 主观题，改到比较符合我们规范
bool tmp = cur->foo() == other.foo()? BmEnumType::theSame : BmEnumType::notTheSame; 

// p.s.: 旧的规范是不提倡用三目表达式的，但我个人觉得能用就用，可以减少圈复杂度，代码也简洁一点。
//       BIM这边也没有要求。但是嵌套三目表达式一定是不可取的
```

```c++
// 主观题，提升可读性
if (cur.ctxInfo.environment.c_str() == "project_environment" && getCurStage() != BmStage::kFinish)
// p.s.: C++通用代码规范对这个有建议要求，BIM无要求
```

```c++
// 主观题，哪个可读性好
if (nullptr != dev)
if (dev != nullptr)
if (dev)

// p.s.: 指针是可以隐式转换为bool量的，但如果是智能指针也想要这种隐式判断能力，需要重载operator bool()函数
// p.s.: C++通用代码规范对这个有明确要求，BIM无要求
```

#### 3. 语法题
1. 编译单元是什么意思？
2. 头文件能不能使用匿名命名空间？
3. constexpr声明的变量都是不占用内存的吗？
4. 给一个正确使用多继承的例子，如果不用多继承的话，是怎么设计的？
5. private继承的意义是什么？protected继承的意义是什么？
6. const T&作为形参的时候，可以输入右值吗？
7. 下面代码有什么问题？
```c++
std::vector<int> vec;
vec.push_back(1);
for (auto idx = vec.size(); idx >= 0; idx--) {
    cout << "===== \n";
}
```

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

#### 4. 重构练习
```c++
bool isEligibleForDiscount(int age, bool hasCoupon) {
    if (age > 60 || hasCoupon) {
        return true;
    } else {
        return false;
    }
}
```

```c++
void printUserDetails(int userId) {
    if (userId == 1) {
        cout << "User 1: Alice" << endl;
        cout << "Age: 30" << endl;
        cout << "Email: alice@example.com" << endl;
    } else if (userId == 2) {
        cout << "User 2: Bob" << endl;
        cout << "Age: 25" << endl;
        cout << "Email: bob@example.com" << endl;
    }
}
```

```c++
void processMatrix(vector<vector<int>>& matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            // ...
            if (matrix[j][i] % 2 == 0) {
                // ...
            }
        }
    }
}
```

### 100. 语法补充

#### 1. explicit怎么用
`explicit`关键字在C++中用于防止类构造函数、转换运算符或其他特定函数进行隐式类型转换。其主要目的是增加代码的清晰度和预防意外的类型转换，从而避免可能的错误。

使用`explicit`的情况：

1. **对于单参数构造函数**：
   - 防止构造函数被隐式用作类型转换运算符。例如，如果有一个接受`int`参数的构造函数，没有`explicit`关键字，编译器可以自动将`int`类型的值转换为该类的对象。使用`explicit`可以阻止这种隐式转换。

   ```c++
   class Foo {
   public:
       explicit Foo(int x) {}
   };

   Foo obj = 10; // 错误：不能隐式转换
   Foo obj2(10); // 正确：显式调用构造函数
   ```
2. **对于有默认参数的构造函数**
    ```c++
    class Foo {
    public:
        explicit Foo(int x, int y = 0);
    };

    Foo myFoo1(10); // 正确，显式调用构造函数
    Foo myFoo2 = Foo(10); // 也正确，显式调用构造函数
    Foo myFoo3 = 10; // 如果没有explicit，也会构造出来
    ```

3. **对于构造函数接受`std::initializer_list`作为参数**：
   
   - 类似地，防止通过花括号初始化语法隐式转换。
4. **对于类型转换运算符**：
   - 防止类的对象被隐式转换为其他类型。

   ```c++
   class Foo {
   public:
       explicit operator bool() const { return true; }
   };

   Foo foo;
   bool x = foo; // 错误：不能隐式转换
   bool y = static_cast<bool>(foo); // 正确：显式转换
   ```

`explicit`的优点：

- **增加代码清晰度**：使用`explicit`可以明确表示构造函数或转换运算符需要显式调用，提高代码的可读性。
- **避免意外的类型转换**：防止编译器自动进行可能导致错误的类型转换。
- **提高类型安全**：通过限制隐式转换，`explicit`关键字有助于维护类型安全，减少运行时错误。

总的来说，`explicit`关键字是C++中一个重要的特性，它通过防止隐式类型转换来帮助程序员编写更安全、更清晰的代码。