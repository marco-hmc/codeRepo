## 类型擦除

### 1. concepts

#### 1.1 什么是类型擦除？可以用来做什么？

* **什么是类型擦除**
    在C++中，类型擦除（Type Erasure）是一种编程技术，它允许你在运行时隐藏或“擦除”对象的具体类型信息，只保留对象的行为，从而实现多态性和泛型编程的一种灵活方式。
    类型擦除是一个类似wrapper的行为。

    C++ 中模板提供了编译时的泛型编程能力，使用模板时编译器会根据具体的类型实例化代码。然而，有时我们希望在运行时处理不同类型的对象，而不需要知道它们的具体类型，只关心它们具有某些共同的行为。类型擦除通过创建一个抽象接口，将具体类型的对象包装起来，对外只暴露统一的接口，从而隐藏了具体的类型信息。

    例如，假设有多个不同类型的类 `Dog`、`Cat`、`Bird`，它们都有一个 `speak` 方法。可以通过类型擦除技术，将这些不同类型的对象统一包装在一个类（比如 `AnimalWrapper`）中，使得外部代码可以以相同的方式调用它们的 `speak` 方法，而无需关心具体是哪种动物。

* **类型擦除的用途**
    - **实现多态行为**：除了传统的虚函数多态，类型擦除提供了另一种实现多态的方式。通过类型擦除，不同类型的对象可以被视为具有相同的抽象类型，从而实现更灵活的多态行为。例如，在一个图形绘制系统中，`Circle`、`Rectangle`、`Triangle` 等不同形状的类可以通过类型擦除被统一处理，对外提供统一的 `draw` 接口。
    - **泛型容器**：在自定义容器中，使用类型擦除可以使容器能够存储不同类型的对象，而不需要为每种类型都单独实现一个容器。比如，实现一个 `Any` 类型的容器，它可以存储任意类型的对象，内部通过类型擦除技术来管理这些对象。
    - **简化接口设计**：类型擦除可以使接口更加简洁和通用。客户端代码只需要与抽象的接口交互，而不需要了解具体的实现类型。这有助于提高代码的可维护性和可扩展性。例如，在一个日志记录系统中，不同的日志记录器（如文件日志记录器、控制台日志记录器等）可以通过类型擦除被统一的日志记录接口调用。

#### 1.2 类型擦除实现的基本原理是什么？
    比如说如果我希望实现一个容器，容器能够同时存储任何类型的数据。
    那这个容器存储的一定只能够是指针了。
    那之后如果需要取回来呢？那这个指针指向的类型就做一点特殊处理，比如说我本意是存储int和double，现在变成存储intType和doubleType，intType和doubleType都有一个公共父类type，这个公共父类提供方法获取类型信息。
    那么只要所有指针都是type类型下的，我就实现了根据指针去存储任何类型数据了，然后根据指针调用虚函数方法，得到具体类型，再解码回来了。
    可是这样做了，我直接存储type类型指针，用多态思路去做就好了。而且还要改造存储类型对象。太麻烦了。有没有一种更好的方法呢？

    有，提供包装器的方式将公共父类的概念隐藏到一个自定义类型中。
    

### 2. implementation

```c++
#include <iostream>
#include <memory>
#include <typeinfo>
#include <typeindex>
#include <stdexcept>

class Any {
public:
    Any() = default;

    template <typename T>
    Any(T value) : ptr_(std::make_unique<Model<T>>(std::move(value))) {}

    template <typename T>
    T& get() {
        if (typeid(T) != ptr_->type()) {
            throw std::bad_cast();
        }
        return dynamic_cast<Model<T>&>(*ptr_).data_;
    }

    const std::type_info& type() const {
        return ptr_ ? ptr_->type() : typeid(void);
    }

private:
    struct Concept {
        virtual ~Concept() = default;
        virtual const std::type_info& type() const = 0;
    };

    template <typename T>
    struct Model : Concept {
        Model(T data) : data_(std::move(data)) {}
        const std::type_info& type() const override { return typeid(T); }
        T data_;
    };

    std::unique_ptr<Concept> ptr_;
};

int main() {
    Any a = 42;
    std::cout << a.get<int>() << std::endl;

    a = std::string("Hello, World!");
    std::cout << a.get<std::string>() << std::endl;

    try {
        std::cout << a.get<int>() << std::endl; // This will throw std::bad_cast
    } catch (const std::bad_cast& e) {
        std::cerr << "Bad cast: " << e.what() << std::endl;
    }

    return 0;
}
```

这个就是std::any实现的简易版本了
#### 2.1 std::any如何实现的？

```c++
#include <iostream>
#include <string>
#include <typeinfo>
#include <vector>
#include <stdexcept>

class Any {
public:
    template <typename T>
    Any(T value) : ptr_(new T(std::move(value))), type_(&typeid(T)) {}

    ~Any() {
        if (ptr_) {
            delete ptr_;
        }
    }

    template <typename T>
    T& get() {
        if (typeid(T) != *type_) {
            throw std::bad_cast();
        }
        return *static_cast<T*>(ptr_);
    }

    // 禁止拷贝构造和赋值操作
    Any(const Any&) = delete;
    Any& operator=(const Any&) = delete;

    // 支持移动语义
    Any(Any&& other) noexcept : ptr_(other.ptr_), type_(other.type_) {
        other.ptr_ = nullptr;
        other.type_ = nullptr;
    }

    Any& operator=(Any&& other) noexcept {
        if (this != &other) {
            if (ptr_) {
                delete ptr_;
            }
            ptr_ = other.ptr_;
            type_ = other.type_;
            other.ptr_ = nullptr;
            other.type_ = nullptr;
        }
        return *this;
    }

private:
    void* ptr_;
    const std::type_info* type_;
};

int main() {
    std::vector<Any> container;
    container.emplace_back(42);
    container.emplace_back(std::string("Hello, World!"));
    container.emplace_back(3.14);

    try {
        std::cout << container[0].get<int>() << std::endl;
        std::cout << container[1].get<std::string>() << std::endl;
        std::cout << container[2].get<double>() << std::endl;
    } catch (const std::bad_cast& e) {
        std::cerr << "Bad cast: " << e.what() << std::endl;
    }

    return 0;
}

```
#### 2.1 std::function如何实现的？


```c++
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>

template <typename>
class Function; // Primary template declaration

template <typename R, typename... Args>
class Function<R(Args...)> {
public:
    Function() = default;

    template <typename T>
    Function(T func) : ptr_(std::make_unique<Model<T>>(std::move(func))) {}

    R operator()(Args... args) const {
        if (!ptr_) {
            throw std::bad_function_call();
        }
        return ptr_->invoke(std::forward<Args>(args)...);
    }

private:
    struct Concept {
        virtual ~Concept() = default;
        virtual R invoke(Args... args) const = 0;
    };

    template <typename T>
    struct Model : Concept {
        Model(T func) : func_(std::move(func)) {}
        R invoke(Args... args) const override {
            return func_(std::forward<Args>(args)...);
        }
        T func_;
    };

    std::unique_ptr<Concept> ptr_;
};

int main() {
    Function<void()> f = []() { std::cout << "Hello, World!" << std::endl; };
    f();

    Function<int(int, int)> add = [](int a, int b) { return a + b; };
    std::cout << "3 + 4 = " << add(3, 4) << std::endl;

    return 0;
}
```

这个例子展示了如何使用 `std::function` 来实现一个函数包装器，可以存储和调用不同的函数对象。

简单来说，从目的来说，类型擦除是一种可以实现存储任意类型数据的技术；从实现手法来说，就是存指针，和存类型信息。其中类型信息的存储依赖于构造函数是模板形式的；类型信息如果开启rtti，则可以直接存；如果不开启rtti，则需要通过多态的封装技巧，以及自己实现一种将类型信息，映射为可存储信息的手段。