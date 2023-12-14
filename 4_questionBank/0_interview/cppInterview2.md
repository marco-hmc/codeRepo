### static和const分别怎么用，类里面的static和const可以同时修饰成员函数吗？

那这个成员函数我们可以看到，static是访问不了num，因为始终记得，这个static成员是独立于对象而存在的，所以，并没有this指针，也就是当前的类成员是没有办法访问的，也只有static成员，例如例中的count是可以访问。<br>
我们继续来看这个🌰
```cpp
class TestStatic{
    public:
        TestStatic(int _num):num(_num){

        }
        static void set_default();
    private:
        //static int count;
        int num;
        static TestStatic teststat;
};

TestStatic TestStatic::teststat(1);

void TestStatic::set_default(){
    teststat = {2};
    cout << teststat.num << endl;
}

// int TestStatic::count = 42;
int main(){
    TestStatic testStat(9);
    testStat.set_default();
   return 0;
}
```
这个已经很明显的证明了，static，的的确确是独立在对象之外。<br>
为什么说static类成员不是每个类对象的一部分呢？始终记得static是静态分配，这里的静态成员是通过类外定义的，然鹅，普通的类成员，num就是必须在类内定义。这个可以说是并不是对象的一部分，因为如果是一部分，是可以在类内自定义的。<br>
但是，凡事都有一个例外，我们看一下以下的代码
```cpp
class Curious{
    public:
        static const int c1 = 7;
        static int c3 = 11; // ❌ 非const
        // 不是常量也不行
        static constexpr float c5 = 7.0; // 类内初始化成员不是整型，要用constexpr
};
```

```cpp
    const int i = 8;// 声明了i是不能改变
    const int *p = &i; //  声明了p指针指向的变量是const，不改变
    int const*p = &i; // 声明了p指针不能改变所指的方向或地址
    int *const p = &i; // 效果同上
    // 所以看来const的承诺的变量必须是有初始化的
    int ii = 49;
    cptr = &ii; // 允许指向非常量的指针转换成指向常量类型的指针 引用也是
    const int &cii = ii;
    const int *const ccptr = &i; // 指向常量的常量指针（不能修改指针）
```

好了const的时候，大概是这样了，在cpp primer中，可以这样地去定义，顶层const就是原本就是一个常量，底层const就是指向的是一个const常量。<br>
```cpp
class Quote{
    public:
    int cfuncc(const int &t) const{ // 这里的作用式修改隐式*this指针的类型 表示this是一个指向常量的指针
        int s = t;
        cout << s << endl;
        i = 90; // ❌！
        x = 89; // ✅
        return t;
    } // 使得常量或常量引用都只能调用常量成员函数
    private:
        int i;
        mutable int x;
};
```
cfuncc函数告诉编译器，我这个函数，并不会改变你类里面的所有的数据成员的值。因为我这个this指针类型都是指向一个常量的指针，除非你说要改变，就是讲变量设为mutable，那么，就可以修改这个数据了。mutable的知识点后面会继续讲。<br>
所以这就是常量成员函数的使用，可以说确实是比较灵活，保证了封装性，调用并不改变原来初始化的值。在平常开发中还是很值得去使用的<br>
那么constexpr呢？
先来看一个constexpr常用的🌰
```cpp
constexpr int isqrt_helper(int sq,int d,int a){
    return sq <= a?isqrt_helper(sq+d,d+2,a):d;
}

constexpr int isqrt(int x){
    return isqrt_helper(1,3,x)/2-1;
}
```
这两个足够简单的表达式也凸显了constexpr确实是用于字面值求值。编译时就能发现错误。<br>
既然在函数可以足够简单，那在类里面呢？<br>
来看下面这个🌰
```cpp
class TestStatic{
    public:
        constexpr TestStatic(int _num = 4):num(_num){
            cout << num << endl;
        }
        static void set_default();
    private:
        //static int count;
        int num;
        static TestStatic teststat;
};
TestStatic TestStatic::teststat(1);
void TestStatic::set_default(){
    teststat = {2};
    cout << teststat.num << endl;
}

// int TestStatic::count = 42;
int main(){
    TestStatic testStat(9);
    testStat.set_default();
   return 0;
}
```
这个是上面的🌰，只是在构造函数前添加了一个constexpr，编译是通过的。constexpr一般用于函数表达式足够简单的情况，也就是说要简单到可以在编译时求值，如果无法在编译时初始化声明的变量，那么就会在编译器中报❌<br>
其实使用constexpr始终都谨记，这是一个关于值的概念。<br>
关于地址
```cpp
    constexpr const char *p1 = "asdf";
    constexpr const char *p2 = p1;
    constexpr const char *p2 = p1+2; // ❌编译器不知道这类地址的常量值是多少
    constexpr char c = p1[2];
```
好了，讲到这里，我们清楚的知道static和const怎么用，那么他们在类里面能同时修饰成员函数嘛？<br>
答案是不可以的，为什么？
```cpp
class Curious{
    public:
        static const int c1 = 7;
        static int c3 = 11; // ❌ 非const
        // 不是常量也不行
        static constexpr float c5 = 7.0; // 类内初始化成员不是整型，要用constexpr
};
```
先来看这个例外。他确实能在类里修饰成员变量，但是要是修饰成员函数，就改变了成员函数的this指针了，static的成员函数是不能访问非static成员的，因为他是独立于对象之外，却与类关联的，而且没有this指针。而const 成员函数是指承诺this是指向常量的指针，里面指向的常量不能改变，除非你是mutable。所以两种用法是冲突的，这样用也就与之前所说的是矛盾的。
#### 未完待续...