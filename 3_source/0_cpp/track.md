* 无符号整数的错误使用
    ```c++
    for (unsigned int i = 10; i >= 0; --i) { ... }
    ```

* 容器的size()返回类型是无符号整数
    ```c++
    std::vector<int> vec;
    vec.push_back(1);
    for (auto idx = vec.size(); idx >= 0; idx--) {
        cout << "===== \n";
    }
    ```

* STL遍历删除时注意迭代器失效问题
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