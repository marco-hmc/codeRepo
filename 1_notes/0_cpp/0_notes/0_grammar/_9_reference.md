## reference 

### 1. concepts

### 2. 右值引用

### 3. 完美转发

### 99. quiz

#### 1. 为什么多线程

**33. 对于std::forward的auto&&形参使用decltype**

在C++14中，我们可以在lambda表达式里面使用auto了，那么我们想要把传统的完美转发用lambda表达式写出来应该是什么样子的呢：
    
    class SomeClass{
    public:
        template<typename T>
        auto operator()(T x) const{
            return func(normalize(x));
        }
    }
    
    auto f=[](auto&& x){
        return func(normalize(std::forward<decltype(x)>(x)));
    };


引用绑定到临时对象的规则:
右值引用: 当使用右值引用(&&)绑定到返回的右值(例如函数返回的临时对象)时,编译器会延长右值的生命周期,使得引用继续有效.

cpp
Copy code
const T& constRef = getTemporary();  // const 引用绑定到临时对象
为什么需要引用绑定到临时对象:
避免不必要的拷贝: 当函数返回临时对象时,使用引用绑定可以避免不必要的拷贝构造,提高性能.

允许延迟析构: 通过延长临时对象的生命周期,允许在整个语句块中使用临时对象,而不会在引用失效时导致未定义行为.

* 什么时候需要用move
  * 对于callback函数来说
  * 对于将对象插入到容器来说
  * 交换两个对象
  * 
* 为什么右值可以被常量左值引用 引用?
   ```cpp
   const std::string& lv2 = lv1 + lv1; // 合法, 常量左值引用能够延长临时变量的生命周期
   ```
* 拷贝构造函数的参数可以不加引用吗?为什么