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