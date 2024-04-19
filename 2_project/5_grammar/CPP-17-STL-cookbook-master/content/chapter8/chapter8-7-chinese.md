# 存储不同的类型——std::variant

C++中支持使用`struct`和`class`的方式将不同类型的变量进行包装。当我们想要使用一种类型来表示多种类型时，也可以使用`union`。不过`union`的问题在于我们无法知道，其是以哪种类型为基础进行的初始化。

看一下下面的代码：

```c++
union U {
    int a;
    char *b;
    float c;
};
void func(U u) { std::cout << u.b << '\n'; }	
```

当我们调用`func`时，其会将已整型`a`为基础进行初始化的联合体`t`进行打印，当然也无法阻止我们对其他成员进行访问，就像使用字符串指针对成员`b`进行初始化了一样，这段代码会引发各种bug。当我们开始对联合体进行打包之前，有一种辅助变量能够告诉我们其对联合体进行的初始化是安全的，其就是`std::variant`，在C++17中加入STL。

`variant`是一种新的类型，类型安全，并高效的联合体类型。其不使用堆上的内存，所以在时间和空间上都非常高效。基于联合体的解决方案，我们就不用自己再去进行实现了。其能单独存储引用、数组或`void`类型的成员变量。

本节中，我们将会了解一下由`vriant`带来的好处。

## How to do it...

我们实现一个程序，其中有两个类型：`cat`和`dog`。然后将猫狗混合的存储于一个列表中，这个列表并不具备任何运行时多态性：

1. 包含必要的头文件，并声明所使用的命名空间：

   ```c++
   #include <iostream>
   #include <variant>
   #include <list>
   #include <string>
   #include <algorithm>
   
   using namespace std;

   class cat {
       string name;
       
   public:
       cat(string n) : name{n} {}
       
       void meow() const {
       	cout << name << " says Meow!\n";
       }
   };

   class dog {
   	string name;
       
   public:
   	dog(string n) : name{n} {}
       
   	void woof() const {
   		cout << name << " says Woof!\n";
   	}
   };

   using animal = variant<dog, cat>;

   template <typename T>
   bool is_type(const animal &a) {
   	return holds_alternative<T>(a);
   }

   struct animal_voice
   {
       void operator()(const dog &d) const { d.woof(); }
       void operator()(const cat &c) const { c.meow(); }
   };

   int main()
   {
   	list<animal> l {cat{"Tuba"}, dog{"Balou"}, cat{"Bobby"}};

       for (const animal &a : l) {
           switch (a.index()) {
           case 0:
               get<dog>(a).woof();
               break;
           case 1:
               get<cat>(a).meow();
               break;
           }
       }
       cout << "-----\n";

   	for (const animal &a : l) {
           if (const auto d (get_if<dog>(&a)); d) {
           	d->woof();
           } else if (const auto c (get_if<cat>(&a)); c) {
           	c->meow();
           }
       }
       cout << "-----\n";

    	for (const animal &a : l) {
    		visit(animal_voice{}, a);
    	}
    	cout << "-----\n";

        cout << "There are "
            << count_if(begin(l), end(l), is_type<cat>)
            << " cats and "
            << count_if(begin(l), end(l), is_type<dog>)
            << " dogs in the list.\n";
    }
    ```

12. 编译并运行程序，我们就会看到打印三次的结果都是相同的。然后，可以看到`is_type`和`count_if`配合的很不错：

    ```c++
    $ ./variant
    Tuba says Meow!
    Balou says Woof!
    Bobby says Meow!
    -----
    Tuba says Meow!
    Balou says Woof!
    Bobby says Meow!
    -----
    Tuba says Meow!
    Balou says Woof!
    Bobby says Meow!
    -----
    There are 2 cats and 1 dogs in the list.
    ```

## How it works...

`std::variant`与`std::any`类型很相似，因为这两个类型都能持有不同类型的变量，并且我们需要在运行时对不同对象进行区分。

另外，`std::variant`有一个模板列表，需要传入可能在列表中的类型，这点与`std::any`截然不同。也就是说` std::variant<A, B, C>`必须是A、B或C其中一种实例。当然这也意味着其就不能持有其他类型的变量，除了列表中的类型`std::variant`没有其他选择。

` variant<A, B, C>`的类型定义，与以下联合体定义类似：

 ``` c++
union U {
    A a;
    B b;
    C c;
};
 ```

当我们对`a`, `b`或`c`成员变量进行初始化时，联合体中对其进行构建机制需要我们自行区分。`std::variant`类型就没有这个问题。

本节的代码中，我们使用了三种方式来处理`variant`中成员的内容。

首先，使用了`variant`的`index()`成员函数。对变量类型进行索引，`variant<A, B, C>` 中，索引值0代表A类型，1为B类型，2为C类型，以此类推来访问复杂的`variant`对象。

下一种就是使用`get_if<T>`函数进行获取。其能接受一个`variant`对象的地址，并且返回一个类型`T`的指针，指向其内容。如果`T`类型是错误，那么返回的指针就为`null`指针。其也可能对`variant`变量使用`get<T>(x)`来获取对其内容的引用，不过当这样做失败时，函数将会抛出一个异常(使用get-系列函数进行转换之前，需要使用`holds_alternative<T>(x)`对其类型进行检查)。

最后一种方式就是使用`std::visit`函数来进行，其能接受一个函数对象和一个`variant`实例。`visit`函数会对`variant`中内容的类型进行检查，然后调用对应的函数对象的重载`operator()`操作符。

为了这个目的，我们实现为了`animal_voice`类型，将`visit`和`variant<dog, cat>`类型结合在了一起：

```c++
struct animal_voice
{
    void operator()(const dog &d) const { d.woof(); }
    void operator()(const cat &c) const { c.meow(); }
};
```

以`visit`的方式对`variant`进行访问看起来更加的优雅一些，因为使用这种方法就不需要使用硬编码的方式对`variant`内容中的类型进行判别。这就让我们的代码更加容易扩展。

> Note：
>
> `variant`类型不能为空的说法并不完全正确。将[std::monostate](http://zh.cppreference.com/w/cpp/utility/variant/monostate)类型添加到其类型列表中，其就能持有空值了。