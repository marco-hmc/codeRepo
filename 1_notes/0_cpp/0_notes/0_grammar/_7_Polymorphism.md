## 多态

### 1. concepts

#### 1.1 C++的多态是什么？为什要有多态？

多态是面向对象编程的一个重要特性，它允许我们使用一个接口来表示多种形态的对象。在C++中，多态主要通过虚函数和继承来实现。

多态的主要优点是它可以提高代码的可重用性和可扩展性。通过使用多态，我们可以编写出更加通用的代码，这些代码可以处理任何符合特定接口的对象，而不需要关心对象的具体类型。这使得我们可以更容易地添加新的类型，而不需要修改已有的代码。

以下是一个简单的C++代码示例，展示了多态的使用场景：

```cpp
#include <iostream>

// 基类 Shape
class Shape {
public:
    virtual void draw() const {
        std::cout << "Drawing a shape." << std::endl;
    }
};

// 派生类 Circle
class Circle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing a circle." << std::endl;
    }
};

// 派生类 Rectangle
class Rectangle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing a rectangle." << std::endl;
    }
};

void drawShape(const Shape& shape) {
    shape.draw();
}

int main() {
    Circle c;
    Rectangle r;

    drawShape(c);  // 输出: Drawing a circle.
    drawShape(r);  // 输出: Drawing a rectangle.

    return 0;
}
```

在这个例子中，我们定义了一个基类`Shape`和两个派生类`Circle`和`Rectangle`。基类中定义了一个虚函数`draw`，派生类中重写了这个函数。我们还定义了一个函数`drawShape`，它接受一个`Shape`类型的引用，然后调用其`draw`函数。

在`main`函数中，我们创建了一个`Circle`对象和一个`Rectangle`对象，然后分别传递给`drawShape`函数。虽然`drawShape`函数的参数类型是`Shape`，但是由于多态，它可以接受任何`Shape`的派生类对象，并调用其重写的`draw`函数。这就是多态的作用，它使得我们可以编写出更加通用的代码，这些代码可以处理任何符合特定接口的对象，而不需要关心对象的具体类型。

#### 1.2 多态有哪些实现方式？

在C++中，多态主要有以下几种实现方式：

1. 虚函数：通过在基类中声明虚函数，然后在派生类中重写这个虚函数，我们可以实现运行时多态。这种方式的优点是灵活性高，但缺点是有一定的性能开销。

2. 函数重载：通过定义多个同名但参数不同的函数，我们可以实现编译时多态。这种方式的优点是性能高，但缺点是灵活性较低。

3. 模板：通过定义模板函数或模板类，我们可以实现一种更加强大的编译时多态。这种方式的优点是既有高性能，又有高灵活性，但缺点是代码可能会变得复杂。

---

### 2. 虚函数

#### 2.1 虚函数实现原理是什么？

在C++中，虚函数的实现主要依赖于虚函数表（也称为vtable）。每一个有虚函数的类，编译器都会为其生成一个虚函数表，表中存储了该类的虚函数的地址。每一个该类的对象，都会有一个指向虚函数表的指针。

当我们通过基类指针调用虚函数时，实际上是通过这个指针找到虚函数表，然后在表中查找并调用对应的函数。

以下是一个简单的C++代码示例，展示了虚函数的使用：

```cpp
#include <iostream>

// 基类 Shape
class Shape {
public:
    virtual void draw() const {
        std::cout << "Drawing a shape." << std::endl;
    }
};

// 派生类 Circle
class Circle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing a circle." << std::endl;
    }
};

int main() {
    Shape* shape = new Circle();
    shape->draw();  // 输出: Drawing a circle.
    delete shape;
    return 0;
}
```

在这个例子中，我们定义了一个基类`Shape`和一个派生类`Circle`。基类中定义了一个虚函数`draw`，派生类中重写了这个函数。在`main`函数中，我们创建了一个`Circle`对象，然后通过一个`Shape`类型的指针来调用`draw`函数。由于`draw`函数是虚函数，所以实际调用的是`Circle`类的`draw`函数，而不是`Shape`类的`draw`函数。这就是虚函数的作用，它使得我们可以通过基类指针调用派生类的函数。

以下是一个简单的图示，展示了虚函数表的工作原理：

```
  Shape object:    Circle object:    Shape vtable:    Circle vtable:
+-------------+  +-------------+   +-------------+  +-------------+
| vptr        |  | vptr        |   | draw()      |  | draw()      |
| ...         |  | ...         |   | ...         |  | ...         |
+-------------+  +-------------+   +-------------+  +-------------+
  |                |                 |                |
  |                |                 v                v
  |                |               Shape::draw()    Circle::draw()
  |                |
  v                v
Shape::vtable    Circle::vtable
```

在这个图示中，`Shape`对象和`Circle`对象都有一个`vptr`，这是一个指向虚函数表的指针。`Shape`的`vptr`指向`Shape`的虚函数表，`Circle`的`vptr`指向`Circle`的虚函数表。虚函数表中存储了虚函数的地址，所以当我们通过`Shape`指针调用`draw`函数时，实际上是通过`vptr`找到虚函数表，然后在表中查找并调用对应的函数。

简单来说，
* 每一个有虚函数的对象下的都会有一个`vtable`,如上面的`Shape vtable`和`Circle vtable`.
* 每一个从有虚函数的对象下来的实例都会有一个`vptr`,`vptr`指向`vtable`, 如上面的`Shape object`和`Circle object`.
* 当我对某一个`Shape object`调用`draw()`函数时，查询方式都是通过`vptr`找到`vtable`的`draw()`。因为

#### 2.2 当对象调用一个普通成员函数，和调用一个虚函数，编译器是怎么区别对待的？

当对象调用一个普通成员函数和调用一个虚函数时，编译器的处理方式是不同的。

对于普通成员函数，编译器在编译时就能确定函数的地址，所以在生成的汇编代码中，函数调用会直接转换为对应的函数地址。

例如，假设我们有以下的C++代码：

```cpp
class MyClass {
public:
    void normalFunction() { /*...*/ }
};

int main() {
    MyClass obj;
    obj.normalFunction();
    return 0;
}
```

对应的汇编代码可能类似于：

```assembly
mov ecx, obj
call MyClass::normalFunction
```

对于虚函数，编译器在编译时不能确定函数的地址，因为虚函数的调用需要在运行时通过虚函数表来确定。所以在生成的汇编代码中，函数调用会转换为通过虚函数表来查找函数地址。

例如，假设我们有以下的C++代码：

```cpp
class MyBase {
public:
    virtual void virtualFunction() { /*...*/ }
};

class MyDerived : public MyBase {
public:
    void virtualFunction() override { /*...*/ }
};

int main() {
    MyBase* obj = new MyDerived();
    obj->virtualFunction();
    delete obj;
    return 0;
}
```

对应的汇编代码可能类似于：

```assembly
mov ecx, obj
mov edx, [ecx]  // 获取vptr
call [edx]  // 通过vptr调用虚函数
```

以上的汇编代码只是为了说明问题而简化的，实际的汇编代码会更复杂。

简单来说，编译器首先知道这是一个虚函数，那就会生成通过`vptr`找到实际函数的代码。编译器怎么知道这是一个虚函数的，属于汇编原理，这里就不展开了。

但从这里，可以简单认识到为什么虚函数开销要大一些呢


#### 2.2 C++多继承的时候，虚函数是怎么处理的？

在C++的多继承中，每个基类都有自己的虚函数表。当一个类从多个基类继承时，它会有多个虚函数表指针，每个指针指向一个基类的虚函数表。当我们通过基类指针调用虚函数时，会根据指针的类型找到对应的虚函数表，然后在表中查找并调用对应的函数。

一般情况下，如果有多继承，且父类都是有虚函数的话，就会有多个`vptr`。编译器生成代码的时候也能够知道用哪个`vptr`，忽略编译器额外时间开销的话，多继承和单一继承的虚函数调用开销是一样的。

#### 2.3 C++多继承的时候，如何处理同名成员变量？同名成员函数？

如果两个基类有同名的成员变量或成员函数，那么在派生类中需要通过作用域解析运算符（::）来指定要访问哪个基类的成员。

如果是对派生类访问两个基类同名的成员变量，就会报错。

---

### 3. 虚继承

#### 3.1 虚继承是什么？有什么用？

虚继承是C++中的一种特殊的继承方式，主要用于解决多继承中的菱形继承问题。在菱形继承中，如果不使用虚继承，那么最底层的派生类会继承多份基类的数据和方法，这会导致资源的浪费和访问的歧义。而虚继承可以解决这个问题，它会让从多个路径继承来的同一个基类，在内存中只有一份实例。

以下是一个不使用虚继承的菱形继承例子，这将导致编译错误：

```cpp
class Base {
public:
    int x;
};

class Derived1 : public Base {
    // ...
};

class Derived2 : public Base {
    // ...
};

class MostDerived : public Derived1, public Derived2 {
    // ...
};

int main() {
    MostDerived md;
    md.x = 10;  // 编译错误：MostDerived中有两份Base::x，编译器无法确定应该访问哪一份
    return 0;
}
```

在这个例子中，`Derived1`和`Derived2`都继承了`Base`，所以在`MostDerived`中有两份`Base::x`。当我们试图访问`md.x`时，编译器无法确定我们应该访问哪一份`Base::x`，所以会报错。

这个问题可以通过使用虚继承来解决。虚继承会让从多个路径继承来的同一个基类，在派生类中只保留一份拷贝。这样，就不会出现上述的编译错误，因为在`MostDerived`中只有一份`Base::x`。

#### 3.2 虚继承的原理是什么？

虚继承的实现主要依赖于两个机制：虚基类指针（vbptr）和虚基类表（vbtable）。

在虚继承中，虚基类的数据成员不会被直接包含在派生类对象中，而是单独存储。派生类对象中只包含一个指向虚基类的指针，这个指针被称为虚基类指针（vbptr）。

vbptr指向一个虚基类表（vbtable），vbtable中存储了虚基类的数据成员的地址。当我们访问虚基类的数据成员时，实际上是通过vbptr和vbtable找到这些数据成员的。

以下是一个简单的例子：

```cpp
class Base {
public:
    int x;
};

class Derived : virtual public Base {
public:
    int y;
};

int main() {
    Derived d;
    d.x = 10;  // 访问虚基类的数据成员
    return 0;
}
```

在这个例子中，`Derived`虚继承了`Base`，所以`Derived`对象中包含一个vbptr，指向一个vbtable。vbtable中存储了`Base::x`的地址。

在汇编级别，访问`d.x`可能看起来像这样：

```assembly
mov ecx, d  // 将d的地址加载到ecx寄存器
mov edx, [ecx]  // 通过d的地址获取vbptr
mov eax, [edx]  // 通过vbptr获取vbtable的地址
mov ebx, [eax]  // 通过vbtable获取Base::x的地址
mov [ebx], 10  // 将10存储到Base::x的地址
```

请注意，以上的汇编代码只是为了说明问题而简化的，实际的汇编代码会更复杂。

#### 3.3 虚继承是如何具体避免产生多份数据的呢？

虚继承是C++中解决多继承中的菱形继承问题的一种机制。在菱形继承中，如果不使用虚继承，那么最底层的派生类会包含多份基类的数据成员，这是因为基类的数据成员被每个中间层的派生类都继承了一次。

虚继承的工作原理是：虚基类的数据成员不会被直接包含在派生类对象中，而是单独存储。派生类对象中只包含一个指向虚基类的指针，这个指针被称为虚基类指针（vbptr）。

vbptr指向一个虚基类表（vbtable），vbtable中存储了虚基类的数据成员的地址。当我们访问虚基类的数据成员时，实际上是通过vbptr和vbtable找到这些数据成员的。

这样，即使一个类被多次继承，虚基类的数据成员也只会有一份拷贝，因为所有的派生类都通过同一个vbptr和vbtable来访问虚基类的数据成员。这就避免了多份数据的问题。

以下是一个简单的例子：

```cpp
class Base {
public:
    int x;
};

class Derived1 : virtual public Base {
public:
    int y;
};

class Derived2 : virtual public Base {
public:
    int z;
};

class MostDerived : public Derived1, public Derived2 {
public:
    int w;
};

int main() {
    MostDerived md;
    md.x = 10;  // 访问虚基类的数据成员
    return 0;
}
```

在这个例子中，`MostDerived`通过`Derived1`和`Derived2`继承了`Base`，但是`Base::x`只有一份拷贝，因为`Derived1`和`Derived2`都是虚继承`Base`的。当我们访问`md.x`时，实际上是通过vbptr和vbtable找到`Base::x`的地址，然后访问这个地址。

##### 3.3.1 在上面这个例子中Base, Derived1, Derived2和MostDerived身上分别有多少和什么虚指针？

在这个例子中，`Base`、`Derived1`、`Derived2`和`MostDerived`的虚指针如下：

- `Base`：没有虚指针，因为它没有虚函数，也没有虚继承任何类。
- `Derived1`：有一个虚基类指针（vbptr），因为它虚继承了`Base`。
- `Derived2`：有一个虚基类指针（vbptr），因为它虚继承了`Base`。
- `MostDerived`：没有额外的虚基类指针，但从`Derived1`和`Derived2`继承两个虚基类指针。

这里假设没有虚函数。如果有虚函数，那么每个包含虚函数的类都会有一个虚函数指针（vptr）。

那为什么MostDerived只有一个vbptr？简单来说是因为编译器发现这两个vbptr指向同一个vtable，所以优化了。

在这个例子中，`MostDerived`类通过`Derived1`和`Derived2`都间接虚继承了`Base`类，因此它们的虚基类指针（vbptr）都会指向`Base`类的虚基类表（vbtable）。由于这两个vbptr指向的是同一个vbtable，所以编译器会进行优化，只保留一个vbptr。

这样做的好处是可以节省存储空间，同时也避免了不必要的复杂性。因为无论通过哪个路径访问`Base`类的成员，最终都会通过同一个vbptr和vbtable，所以只需要一个vbptr就足够了。

需要注意的是，这种优化是由编译器自动完成的，对于程序员来说是透明的。也就是说，程序员不需要（也不能）手动控制这个优化过程。

简单来说，声明了`virtual public`就表示是虚继承，对于基类的数据，如成员变量都是放在`vbptr`指向的同一个表中。
##### 3.3.2 

虚继承主要用于解决多继承中的菱形继承问题。它让从多个路径继承来的同一个基类，在内存中只有一份实例。虚继承的实现依赖于虚基类指针和虚基类表。

* 虚继承用于解决多继承条件下的菱形继承问题（浪费存储空间、存在二义性）
* 底层实现原理与编译器相关，一般通过**虚基类指针**和**虚基类表**实现，**每个虚继承的子类都有一个虚基类指针**（占用一个指针的存储空间，4/8字节）和**虚基类表**（不占用类对象的存储空间）（需要强调的是，虚基类依旧会在子类里面存在拷贝，只是仅仅最多存在一份而已，并不是不在子类里面了）；当虚继承的子类被当做父类继承时，虚基类指针也会被继承
* 实际上，**vbptr 指的是虚基类表指针**（virtual base table pointer），该指针指向了一个**虚基类表**（virtual table），**虚表中记录了虚基类与本类的偏移地址**；通过偏移地址，这样就找到了虚基类成员，而虚继承也不用像普通多继承那样维持着公共基类（虚基类）的两份同样的拷贝，节省了存储空间


#### 3.4 C++菱形继承，如何避免多份同样的基类数据

在C++的菱形继承中，为了避免基类的数据被多次继承，可以使用虚继承。虚继承会让从多个路径继承来的同一个基类，在内存中只有一份实例。这是通过在派生类中只保留一个指向虚基类的指针来实现的，所有的虚基类的成员都通过这个指针来访问。

#### 3.5 虚继承和虚函数实现的原理是怎么样的？

虚继承的实现也依赖于虚函数表。在虚继承中，虚基类的成员不会被直接包含在派生类对象中，而是通过一个指向虚基类的指针来访问。这个指针存储在虚函数表中，通过这个指针，我们可以找到虚基类的实例。

虚函数的实现也依赖于虚函数表。每一个有虚函数的类，都有一个虚函数表，表中存储了该类的虚函数的地址。当我们通过基类指针调用虚函数时，实际上是通过这个指针找到虚函数表，然后在表中查找并调用对应的函数。

### 4. 函数重载

### 4. 模板

### 99. quiz


#### 1. 多继承5个父类,如果5个父类都有虚函数的话,派生类就有5个vptr,对吗? 不同的vptr怎么id?

在C++中,如果一个派生类从多个基类继承,每个基类都有虚函数,那么派生类的对象会有多个虚函数表指针(vptr).每个基类的vptr指向其自己的虚函数表(vtable).所以,如果一个派生类从5个都有虚函数的基类继承,那么这个派生类的对象就会有5个vptr.

这是因为在C++中,每个类都有自己的虚函数表,这个表中包含了类的所有虚函数的地址.当一个类被继承时,派生类会继承基类的所有成员,包括vptr.所以,如果一个派生类从多个基类继承,那么它就会有多个vptr.

需要注意的是,虽然派生类有多个vptr,但是它只有一个自己的虚函数表.这个表中包含了派生类自己的虚函数,以及从基类继承过来的虚函数.当我们通过基类指针调用虚函数时,编译器会根据vptr找到正确的虚函数表,然后在这个表中查找并调用虚函数.这就是C++中多态性的实现原理.


#### 2. c++多态是如何实现的?

#### 3. c++多继承是如何实现?如何处理同名变量

#### 4. 基类析构函数为什么要是虚函数？
如果不是虚函数的话,可能会有内存泄漏的问题
如果你有一个基类指针指向一个派生类对象:
```c++
Copy code
Base* ptr = new Derived();
delete ptr; // 这里会首先调用Derived的析构函数,然后调用Base的析构函数
```
如果基类的析构函数不是虚函数,那么只会调用基类的析构函数,而Derived的析构函数将不会被调用,可能导致资源泄漏.

#### 5. 虚继承、虚函数区别
- 相同之处：都利用了虚指针（均占用类的存储空间）和虚表（均不占用类的存储空间）
- 不同之处：
  - 虚函数不占用存储空间
  - 虚函数表存储的是虚函数地址
  - 虚基类依旧存在继承类中，只占用存储空间
  - 虚基类表存储的是虚基类相对直接继承类的偏移
  - 虚继承
  - 虚函数



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
