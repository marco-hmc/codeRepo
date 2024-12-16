### 代理类

#### 例子：实现二维数组类

以下是一个实现二维数组类的示例，通过两次重载 `operator[]` 运算符来实现对二维数组的访问：

```cpp
#include <iostream>

template<class T>
class Array2D {
public:
    Array2D(int dim1, int dim2) : dim1_(dim1), dim2_(dim2) {
        data_ = new T*[dim1];
        for (int i = 0; i < dim1; ++i) {
            data_[i] = new T[dim2];
        }
    }

    ~Array2D() {
        for (int i = 0; i < dim1_; ++i) {
            delete[] data_[i];
        }
        delete[] data_;
    }

    class Array1D {
    public:
        Array1D(T* array) : array_(array) {}

        T& operator[](int index) {
            return array_[index];
        }

        const T& operator[](int index) const {
            return array_[index];
        }

    private:
        T* array_;
    };

    Array1D operator[](int index) {
        return Array1D(data_[index]);
    }

    const Array1D operator[](int index) const {
        return Array1D(data_[index]);
    }

private:
    int dim1_, dim2_;
    T** data_;
};

int main() {
    Array2D<int> data(10, 20);
    data[3][6] = 42;
    std::cout << data[3][6] << std::endl; // 输出: 42
    return 0;
}
```

#### 例子：代理类区分 `[]` 操作符的读写

采用延迟计算方法，修改 `operator[]` 让它返回一个代理对象而不是字符对象本身，并且判断之后这个代理对象怎么被使用，从而判断是读还是写操作。

```cpp
#include <iostream>
#include <memory>

class String {
public:
    class CharProxy {
    public:
        CharProxy(String& str, int index) : theString_(str), charIndex_(index) {}

        CharProxy& operator=(const CharProxy& rhs) {
            if (this != &rhs) {
                theString_.setChar(charIndex_, rhs.theString_.getChar(rhs.charIndex_));
            }
            return *this;
        }

        CharProxy& operator=(char c) {
            theString_.setChar(charIndex_, c);
            return *this;
        }

        operator char() const {
            return theString_.getChar(charIndex_);
        }

    private:
        String& theString_;
        int charIndex_;
    };

    const CharProxy operator[](int index) const {
        return CharProxy(const_cast<String&>(*this), index);
    }

    CharProxy operator[](int index) {
        return CharProxy(*this, index);
    }

    void setChar(int index, char c) {
        value_[index] = c;
    }

    char getChar(int index) const {
        return value_[index];
    }

private:
    std::string value_;
};

int main() {
    String str;
    str.setChar(0, 'H');
    str.setChar(1, 'e');
    str.setChar(2, 'l');
    str.setChar(3, 'l');
    str.setChar(4, 'o');

    std::cout << str[0] << str[1] << str[2] << str[3] << str[4] << std::endl; // 输出: Hello

    str[0] = 'h';
    std::cout << str[0] << str[1] << str[2] << str[3] << str[4] << std::endl; // 输出: hello

    return 0;
}
```

### 解释

1. **二维数组类**：
   - `Array2D` 类实现了一个二维数组，通过两次重载 `operator[]` 运算符来实现对二维数组的访问。
   - `Array1D` 类是 `Array2D` 类的内部类，用于表示一维数组，并重载了 `operator[]` 运算符。

2. **代理类区分 `[]` 操作符的读写**：
   - `String` 类实现了一个字符串类，通过代理类 `CharProxy` 来区分 `[]` 操作符的读写操作。
   - `CharProxy` 类是 `String` 类的内部类，通过重载 `operator=` 和类型转换运算符来实现读写操作的区分。

通过这些示例，可以看到代理类的应用场景和实现方式。代理类可以用于延迟计算、控制访问权限、记录日志等场景。