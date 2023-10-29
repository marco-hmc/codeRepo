* ***无符号整数的错误使用***
    ```c++
    for (unsigned int i = 10; i >= 0; --i) { ... }
    ```

* ***容器的size()返回类型是无符号整数***
    ```c++
    std::vector<int> vec;
    vec.push_back(1);
    for (auto idx = vec.size(); idx >= 0; idx--) {
        cout << "===== \n";
    }
    ```

* ***STL遍历删除时注意迭代器失效问题***
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

* ***基类析构函数要是虚函数***
    如果不是虚函数的话,可能会有内存泄漏的问题
    如果你有一个基类指针指向一个派生类对象:
    ```c++
    Copy code
    Base* ptr = new Derived();
    delete ptr; // 这里会首先调用Derived的析构函数,然后调用Base的析构函数
    ```
    如果基类的析构函数不是虚函数,那么只会调用基类的析构函数,而Derived的析构函数将不会被调用,可能导致资源泄漏.

* ***成员变量初始化***
    成员变量没有默认初始化行为,需要手动初始化.

* ***不要返回局部变量的指针或引用?以下面例子具体解释***
    ```c++
    //wrong
    char* func() {
        char a[3] = {'a', 'b', 'c'};
        return a;
    }

    //correct
    char* func() {
        char* a = new char[3];
        a[0] = 'a';
        a[1] = 'b';
        a[2] = 'c';
        return a;
    }
    ```
    函数 func 尝试返回一个指向局部数组 a 的指针.这是一个很危险的做法,因为一旦函数执行完毕,a 将会超出其作用域,它的内存空间将会被释放,这将导致返回的指针指向一个无效的内存位置.

* ***vector问题***
    尽量不要在vector中存放bool类型,vector为了做优化,它的内部存放的其实不是bool.

* ***vector删除***
```c++
    std::vector<int> vec(1000000, 42);  // 创建一个包含1000000个元素的vector,并初始化为42
    vec.clear();  // 使用clear方法清空vector,但容量仍然是1000000
    // 在这之后,vec仍然占用着大量内存,即使已经没有实际的元素

    std::vector<int>().swap(vec);  // 使用swap方法将一个新的空vector与vec交换
```


* ***enum***

使用 `enum class` 而不是普通的 `enum` 有几个重要的优点:

1. **作用域限制**:`enum class` 提供了作用域,可以防止枚举值的名称冲突.普通的 `enum` 的枚举值会污染所在的命名空间,容易造成命名冲突.

   例如:

   ```cpp
   enum Color { Red, Blue, Green };
   enum Fruit { Apple, Banana, Orange };

   Color color = Red; // 合法
   Fruit fruit = Red; // 也合法,但可能是个错误
   ```

   如果使用 `enum class`:

   ```cpp
   enum class Color { Red, Blue, Green };
   enum class Fruit { Apple, Banana, Orange };

   Color color = Color::Red; // 合法
   Fruit fruit = Fruit::Red; // 编译错误,因为Red是Fruit的一个成员
   ```

   使用 `enum class` 可以更加明确地指明枚举值的来源.

2. **类型安全**:`enum class` 是强类型的,不能直接转换为整数类型,也不能与整数进行混合运算.这可以防止一些潜在的类型错误.

   ```cpp
   enum class Color { Red, Blue, Green };
   int colorValue = Color::Red; // 编译错误,不能直接转换为整数

   int intValue = static_cast<int>(Color::Red); // 这样转换是合法的
   ```

3. **前缀指示**:`enum class` 的枚举值需要通过作用域解析符 `::` 来使用,这使得代码更加明确,可以清晰地知道变量的类型.

   ```cpp
   enum class Color { Red, Blue, Green };
   Color color = Color::Red; // 明确指明color是Color类型
   ```

总的来说,使用 `enum class` 提供了更好的封装性/作用域控制和类型安全,使得代码更加清晰/可维护和可靠.因此,在新的 C++ 代码中,推荐使用 `enum class` 来定义枚举类型.

* ***std::remove的使用***
这个remove其实并没有真正的删除元素,需要和erase配合使用

***std::thread的使用***
一定要记得join或这detach,否则会crash.
```c++
void func() {}
int main() {
    std::thread t(func);
    if (t.joinable()) {
        t.join(); // 或者t.detach(); 
    }
    return 0;
}
```
