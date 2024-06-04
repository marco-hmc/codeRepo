# 多继承5个父类,如果5个父类都有虚函数的话,派生类就有5个vptr,对吗? 不同的vptr怎么id?

在C++中,如果一个派生类从多个基类继承,每个基类都有虚函数,那么派生类的对象会有多个虚函数表指针(vptr).每个基类的vptr指向其自己的虚函数表(vtable).所以,如果一个派生类从5个都有虚函数的基类继承,那么这个派生类的对象就会有5个vptr.

这是因为在C++中,每个类都有自己的虚函数表,这个表中包含了类的所有虚函数的地址.当一个类被继承时,派生类会继承基类的所有成员,包括vptr.所以,如果一个派生类从多个基类继承,那么它就会有多个vptr.

需要注意的是,虽然派生类有多个vptr,但是它只有一个自己的虚函数表.这个表中包含了派生类自己的虚函数,以及从基类继承过来的虚函数.当我们通过基类指针调用虚函数时,编译器会根据vptr找到正确的虚函数表,然后在这个表中查找并调用虚函数.这就是C++中多态性的实现原理.


21/c++多态是如何实现的?

22/c++多继承是如何实现?如何处理同名变量


* ***基类析构函数要是虚函数***
    如果不是虚函数的话,可能会有内存泄漏的问题
    如果你有一个基类指针指向一个派生类对象:
    ```c++
    Copy code
    Base* ptr = new Derived();
    delete ptr; // 这里会首先调用Derived的析构函数,然后调用Base的析构函数
    ```
    如果基类的析构函数不是虚函数,那么只会调用基类的析构函数,而Derived的析构函数将不会被调用,可能导致资源泄漏.



## 多态

### 1. 
这段代码的主要目标是防止不同类型的动物之间进行赋值操作，同时允许同类型的动物之间进行赋值。为了实现这个目标，它引入了一个抽象基类`AbstractAnimal`，并将赋值操作符`operator=`设为`protected`，这样只有`AbstractAnimal`的子类可以访问它。

然后，每个具体的动物类（如`Lizard`和`Chicken`）都提供了自己的赋值操作符，这样就可以在同类型的动物之间进行赋值。

以下是一个完整的例子：

```cpp
class AbstractAnimal {
protected:
    AbstractAnimal& operator=(const AbstractAnimal& rhs) {
        // 假设这里进行了一些通用的赋值操作
        return *this;
    }
public:
    virtual ~AbstractAnimal() = 0; // 纯虚析构函数
};

AbstractAnimal::~AbstractAnimal() {} // 纯虚析构函数的定义

class Lizard : public AbstractAnimal {
public:
    Lizard& operator=(const Lizard& rhs) {
        AbstractAnimal::operator=(rhs); // 调用基类的赋值操作符
        // 这里可以添加一些针对Lizard的赋值操作
        return *this;
    }
};

class Chicken : public AbstractAnimal {
public:
    Chicken& operator=(const Chicken& rhs) {
        AbstractAnimal::operator=(rhs); // 调用基类的赋值操作符
        // 这里可以添加一些针对Chicken的赋值操作
        return *this;
    }
};

int main() {
    Lizard liz1, liz2;
    liz1 = liz2; // 正确，把一个lizard赋值给了一个lizard

    Chicken chick;
    // liz1 = chick; // 错误，不能把一个chicken赋值给一个lizard

    return 0;
}
```

在这个例子中，我们不能把一个`Chicken`赋值给一个`Lizard`，因为`Lizard::operator=`只接受`Lizard`类型的参数。但我们可以在两个`Lizard`之间进行赋值，因为`Lizard::operator=`接受`Lizard`类型的参数。

### 



## 虚继承

* 虚继承用于解决多继承条件下的菱形继承问题（浪费存储空间、存在二义性）
* 底层实现原理与编译器相关，一般通过**虚基类指针**和**虚基类表**实现，**每个虚继承的子类都有一个虚基类指针**（占用一个指针的存储空间，4/8字节）和**虚基类表**（不占用类对象的存储空间）（需要强调的是，虚基类依旧会在子类里面存在拷贝，只是仅仅最多存在一份而已，并不是不在子类里面了）；当虚继承的子类被当做父类继承时，虚基类指针也会被继承
* 实际上，**vbptr 指的是虚基类表指针**（virtual base table pointer），该指针指向了一个**虚基类表**（virtual table），**虚表中记录了虚基类与本类的偏移地址**；通过偏移地址，这样就找到了虚基类成员，而虚继承也不用像普通多继承那样维持着公共基类（虚基类）的两份同样的拷贝，节省了存储空间

## 虚继承、虚函数区别

- 相同之处：都利用了虚指针（均占用类的存储空间）和虚表（均不占用类的存储空间）

- 不同之处：

- - 虚函数不占用存储空间
  - 虚函数表存储的是虚函数地址
  - 虚基类依旧存在继承类中，只占用存储空间
  - 虚基类表存储的是虚基类相对直接继承类的偏移
  - 虚继承
  - 虚函数



## 99. quiz
## 构造函数或析构函数调用虚函数

* 简要结论： 
  1. **从语法上讲，调用完全没有问题**
  2. 但是从效果上看，往往不能达到需要的目的
* Effective 的解释是： 
  * 派生类对象构造期间进入基类的构造函数时，对象类型变成了基类类型，而不是派生类类型
  * 同样，进入基类析构函数时，对象也是基类类型

