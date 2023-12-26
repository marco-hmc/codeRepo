### 首先我们来看一下第一个问题，什么是智能指针？

### 一个人的独享，感觉拥有了全世界(unique_ptr独享所有权)

```cpp
template<typename T,typename D = default_delete<T> > // default_delete是一个无状态类
class unique_ptr{
    public:
        using pointer = ptr;
        using element_type = T;
        using deleter_type = D;
        constexpr unique_ptr() noexcept;
        constexpr unique_ptr(nullptr_t) noexcept:unique_ptr(){} // 空指针类型
        explicit unique_ptr(pointer p) noexcept; // from pointer
        unique_ptr(pointer p,typename conditional<is_reference<D>::value,D,const D&> del) noexcept; // lvalue
        unique_ptr(pointer p,typename remove_reference<D>::type&& del) noexcept; // rvalue
        unique_ptr(unique_ptr&& x) noexcept;// 右值 移动构造函数
        template<class U,class E>
            unique_ptr(unique_ptr<U,E>&& x)noexcept; // 特例化
        template<class U>
            unique_ptr(auto_ptr<U>&& x)noexcept; // 不抛出异常
        Unique_ptr(const unique_ptr&) = delete; // 不允许拷贝

        unique_ptr& operator=(unique_ptr&& x) noexcept; // 移动赋值运算
        unique_ptr& operator=(nullptr_t) noexcept; // 空指针类型
        template<class U,class E>
            unique_ptr& operator=(unique_ptr<U,E>&& x)noexcept; // 强制类型转换
        unique_ptr& operator=(const unique_ptr&) = delete; // 不允许赋值
};
```
为了不抛出异常，都设置了noexpect，以上包括了右值引用操作，左值引用操作，以及某一构造函数特例化操作。基本囊括而且也解释了为什么不拷贝不赋值。<br>
**release()和reset()** 这两个函数都是将指针的所有权从一个(非const)unique_ptr转移给另一个unique_ptr。<br>
reset()还能好一点，可以释放内存，但是release()就不行了，release()必须有 **接盘侠**，接了要么可以自动负责释放，要么负责手动释放。<br>
接下来我们看看这两个的实现方式<br>
```cpp
void reset(pointer p = pointer()) noexcept;
// 这里有一个默认值
pointer release() noexcept;
// 这里返回一个值
```
release()是返回一个pointer，所以说它需要一个接盘侠。<br>
* unique_ptr 保存一个指针，当他自身被销毁时(例如线程控制流离开unique_ptr的作用域)，使用关联的释放器(deleter)释放所指向的对象<br>
释放器又是什么呢？当一个unique_ptr被销毁，就会调用其自己的释放器销毁所拥有的对象。
```cpp
deleter_type& get_deleter() noexcept;
const deleter_type& get_deleter() const noexcept;
```
1. 局部变量的释放器应该啥也不干<br>
2. 内存池应该将对象归还给内存池，是否销毁它依赖于内存池如何定义。<br>
3. 默认调用delete释放它所指向的对象<br>
管理释放器又分为在运行时绑定和在编译时绑定，这两个区别适用于区别shared_ptr和unique_ptr的，下面讲完shared_ptr会统一讲解，现在只要记住，unique_ptr管理释放器时编译时绑定的。<br>
那怎么传递释放器呢？我们来看一个🌰
```cpp
#include <memory>
#include <iostream>
#include <string>
using namespace std;

class Role{
    public:
        Role(const string &crole):role(crole){
            cout << role << endl;
        }
        ~Role(){
            cout << "delete" << endl;
        }
        void delRole(){
            cout << "delete Role outside" << endl;
        }
    private:
        string role;
};

void outdelRole(Role *r){
    r->delRole();
}

int main(){
    unique_ptr<Role,decltype(outdelRole)*> p1(new Role("trans"),outdelRole);
    return 0;
}
```
输出trans
delete Role outside<br>
这个🌰，充分说明了，我们可以重载释放器，如果是函数的释放器，那么他的参数类型必须是一个objT类型的指针，这样才有删除的意义。decltype是一般用来指明类型的
```cpp
unique_ptr<objT,delT>p(new objT,fcn); // fcn是delT类型对象
```
这样你想怎么删，删什么就由你自个儿来定了。<br>
也可以这样做
```cpp
#include <iostream>
#include <memory>
using namespace std;
class state_deleter {  // a deleter class with state
  int count_;
public:
  state_deleter() : count_(0) {}
  template <class T>
  void operator()(T* p) {
    cout << "[deleted #" << ++count_ << "]\n";
    delete p;
  }
};

state_deleter del;
unique_ptr<int,state_deleter> alpha (new int);
unique_ptr<int,state_deleter> beta (new int,alpha.get_deleter());

// gamma and delta share the deleter "del" (deleter type is a reference!):
unique_ptr<int,state_deleter&> gamma (new int,del);
unique_ptr<int,state_deleter&> delta (new int,gamma.get_deleter());
```
再来看一段比较陷阱的代码
```cpp
unique_ptr<string> p1;
cout << *p1 << endl;
```
这段代码代表p1是一个空指针，那这个空指针，没有指向一个对象，那下面这一段呢？
```cpp
unique_ptr<string> p1();
cout << *p1 << endl;
```
输出的是1，为什么呢？因为`unique_ptr<string> p1()`声明一个无参函数p1，返回的类型是unique_ptr类型的指针，所以要是*p1，那只能是1，他是一个函数体<br>
#### 用途
* 为动态分配的内存提供异常安全<br>
unique_ptr可以理解为一个简单的指针(指向一个对象)或一对指针(包含释放器deleter的情况)<br>
* 将动态分配内存的所有权传递给函数<br>
* 从函数返回动态分配的内存<br>
* 从容器中保存指针<br>
⚠️这里有一个get()的用法
```cpp
pointer get() const noexcept;
```
get()是托管一个对象的指针或者空指针
```cpp
unique_ptr<string> p1(new string("hello world"));
string *pstr = p1.get();
cout << *pstr << endl;
```
他与release()不同，它只是托管，get并是将pstr指向了p1指向的对象，但是并没有释放p1的内存，pstr并没有获取到这个智能指针的所有权，只是得到了它的对象。p1还是需要在某个时刻删除托管数据pstr。<br>
再来看一下解引用运算符
```cpp
typename add_lvalue_reference<element_type>::type operator*() const;
```
作用支持指针操作呗
```cpp
unique_ptr<string> p1(new string("hello world"));
cout << *p1 << endl;
```
再看看->运算符
```cpp
pointer operator->()const noexcept;
```
支持指针行为的操作
```cpp
  unique_ptr<C> foo (new C);
  unique_ptr<C> bar;

  foo->a = 10;
  foo->b = 20;

  bar = std::move(foo); // 支持右值移动操作 foo就释放了
```
那好，我们知道整个unique_ptr都会支持指针的行为，那我们看看它的特例化版本。什么是特例化？就是对于特别的🌰进行特别的处理。不同的版本
```cpp
template<class T,class D> class unique_ptr<T[],D>;
```
```cpp
// 用于内置函数
unique_ptr<int[]> make_sequence(int n){
    unique_ptr<int[]> p{new int[n]};
    for(int i = 0;i<n;++i)
        p[i] = i;
    return p; // 返回局部对象
}
```
这里当然要新增加独一[]运算符的作用，也就是重载 []运算符。<br>
```cpp
element_type& operator[](size_t i)const;
```
不同担心匹配问题，我们提供特例化版本只是帮编译器做了匹配的工作而已。<br>
那交换指针？交换也是移动操作呀！
```cpp
template <class T,class D>
void(unique_ptr<T,D>& x,unique_ptr<T,D>& y)noexpect;
```
交换两方的所有权，你要我的，我要你的。当然这是非成员函数，也有成员函数的写法
```cpp
void swap(unique_ptr& x) noexcept;
```
就是`a.swap(b)`酱紫。<br>
### 共享对象😁，你的对象我共享✨o✨(shared_ptr共享所有权)
既然讲完了unique_ptr，那我们就来讲讲这个让社会更美好的shared_ptr，共享指针。<br>
先来看看怎么用
```cpp
shared_ptr<string> p1; 
shared_ptr<list<int> > p2;
```
通过默认初始化，p1和p2都是空指针。当然这两个操作，都没有分配和使用动态内存。要怎么做呢？我们尝试这样。<br>
```cpp
shared_ptr<string> p1(new string("hehehe"));
cout << *p1 << endl;
```
也可以试一下这样
```cpp
shared_ptr<int> clone(int p){
    return shared_ptr<int>(new int(p));
}
```
也可以管理内置指针inum
```cpp
int *inum = new int(42);
shared_ptr<int> p2(inum);
```
停🤚停🤚停🛑，先说明白，shared_ptr共享指针到底是什么？<br>
shared_ptr表示共享所有权，和unique_ptr指针不同，shared_ptr可以共享一个对象。当两段代码需要访问同一个数据，但两者都没有独享所有权(负责销毁对象)时，可以使用shared_ptr。shared_ptr是一种计数指针，当计数(use_count)变为0时释放所指向的对象。<br>
可以理解为包含两个指针的结构，一个指针指向对象，另一个指针指向计数器(use_count)。<br>
而仅仅是因为当计数变为0才会销毁所指向的对象，它的释放器(deleter)与unique_ptr就不一样，是一个非成员函数。但是是一个可调用对象，可调用对象后面我会专门去讲，但是在这里就要明白，shared_ptr的是释放器是 **运行时绑定**的，而不是 **编译时就绑定**的。而unique_ptr就是编译时绑定的释放器。默认的释放器是`delete`，这个却没有变。(调用对象的析构函数并释放自由存储空间)<br>
它的重点就在于使用计数上，那这个计数又是怎么定义的呢？来看一段代码。<br>
```cpp
shared_ptr<int> p3 = make_shared<int>(42);
cout << p3.use_count() << endl;
```
看吧，这里的use_count()就是用来计数的，现在是1，就是这个对象引用了一次。
```cpp
    shared_ptr<int> p3 = make_shared<int>(42);
    auto r = p3;
    cout << p3.use_count() << endl;
```
这里就是2了，这里会怎样，递增p3的引用计数，那r呢？r的计数是多少？r是2啊，这里就是说这个r也指向p3的对象了，那么这个计数器肯定是一样的。要是r原来有指向的对象呢？那原来r的指向的对象的计数器也要递减，也不影响其他的指针。<br>
所以其实区别就是，这些共享所有权的指针，都没有权利把对象杀死，他把杀对象的事情外包了出去。(不忍心啊!😖)。<br>
所以，这么看来，因为有一个计数器，所以我们可以说，shared_ptr自动销毁所管理的对象。也可以说，shared_ptr自动释放相关联的内存。<br>
可以看一下这段代码，来看看动态内存中的使用
```cpp
#include <iostream>
#include <memory>
#include <string>
#include <initializer_list>
#include <vector>

using namespace std;

class StrBlob{
    public:
        typedef vector<string>::size_type size_type;
        StrBlob():data(make_shared<vector<string> >()){}
        StrBlob(initializer_list<string> il):data(make_shared<vector<string> >(il)){} // 使用参数列表初始化vector
        size_type size() const { return data->size();}
        bool empty() const { return data->empty();}
        void push_back(const string &t){return data->push_back(t);}
        void pop_back();
        string &front();
        string &back();
    private:
        shared_ptr<vector<string> > data; // 共享同一个数据？
        void check(size_type i,const string &msg) const;
};
```
当我们拷贝，赋值或销毁一个StrBlob对象的时候，这个shared_ptr的数据成员将会被拷贝、赋值和销毁。那么每一次都是安全的操作，自动释放。因为计数器，所以安全。<br>
所以其实也不复杂，就是希望我们可以用shared_ptr进行管理动态内存的资源。这里我待会也会着重讲(RAII)<br>
ok，看完了在动态内存的资源管理，那我们熟知的动态内存是怎样的？是那对cp，就是new和delete。其实shared_ptr和new也可以一起用。<br>
```cpp
shared_ptr<double> p1; // shared_ptr 可以指向一个double
shared_ptr<int> p2(new int(42)); // p2指向一个值42的int 直接初始化形式
```
我们看构造函数<br>
```cpp
    template<typename U>
    class shared_ptr{
        public:
            using element_type = U;
            constexpr shared_ptr() noexcept;
            constexpr shared_ptr(nullptr_t):shared_ptr(){} // 空对象
            template <class U> explicit shared_ptr(U* p); // 显式构造 不存在隐式转换
            template <class U,class D> shared_ptr(U* p,D del); // 添加释放器
            template <class D> shared_ptr(nullptr_t p,D del); // 空指针的释放器
            template <class U,class D, class Alloc> shared_ptr(U* p,D del,Alloc alloc); // 分配？
            template <class D,class Alloc> shared_ptr(nullptr_t p,D del,Alloc alloc);
            shared_ptr(const shared_ptr& x) noexcept;
            template<class U> shared_ptr(const shared_ptr<U>& x)noexcept;
            template<class U> explicit shared_ptr(const weak_ptr<U>& x);
            shared_ptr(shared_ptr&& x)(shared_ptr<U>&& x)noexcept; // 右值移动
            template <class U> shared_ptr(auto_ptr<U>&& x);
            template <class U,class D> shared_ptr(unique_ptr<U,D>&& x);// 获得独享指针的所有权
            template <class U> shared_ptr(const shared_ptr<U>& x,element_type* p)noexcept;
    };
```
在构造函数中，接受指针参数的智能指针构造函数是`explicit`，就是显式构造，而不是隐式转换。<br>
```cpp
shared_ptr<int> clone(int p){
    return shared_ptr<int>(new int(p));
}
```
在primer中，建议 **不要混合使用普通指针和智能指针**，怎么才算是混合呢？我们来看一下它给的🌰。
```cpp
void process(shared_ptr<int> ptr){
    // 使用ptr
}// ptr离开作用域，被销毁
```
在这个🌰中，ptr是值传递，大家都知道，值传递会增加拷贝，构造等成本，所以ptr计数值至少为2，很公道，当process结束时，计数值不会变为0。所以局部变量ptr被销毁，ptr指向的内存也不会释放。（所以说使用引用会减少增加引用计数）
```cpp
void process(shared_ptr<int>& ptr){
    cout << ptr.use_count() << endl;
    cout << *ptr << endl;
}
```
当我们使用值传递的时候，引用计数至少为2，但是使用引用传递，引用计数就不会递增
```cpp
    shared_ptr<int> p3 = make_shared<int>(42);
    cout << p3.use_count() << endl;
    // auto r = p3;
    // cout << r.use_count() << endl;
    process(p3);
    cout << p3.use_count() << endl;
```
使用引用计数，输出始终如一。<br>
看来这个🌰只能做引用和值传递的，好像和混合使用普通指针和智能指针没啥搭边啊！<br>
```cpp
    int *x(new int(9));
    process(shared_ptr<int>(x));
    int j = *x;
    cout << j << endl;
```
上面的🌰我们使用的是值传递。嗯。这个🌰说明什么呢？可能不是很懂`shared_ptr<int>(x)`这种骚操作，我们来看一下这样会不会懂了一点
```cpp
shared_ptr<int> ptr = shared_ptr<int>(new int(10));
```
懂了吧。
```cpp
shared_ptr<T> p(q);
```
q是内置指针，p管理这个内置指针所指向的对象。q必须指向new分配的内存且能够转换为T*类型。<br>
所以上上面的例子说明了，这两个混合着用，临时的shared_ptr会被销毁，那所指向的内存也会被释放。所以x估计还指向那个内存，但是，x已经不知不觉中变成空悬指针了。<br>
其实当讲一个shared_ptr绑定到一个普通指针时，我们就将内存的管理责任交给了这位不知名的shared_ptr。所以，我们就不能或者不应该再使用内置指针访问shared_ptr所指向的内存。<br>
primer也建议 **不要使用get初始化另一个智能指针或为智能指针赋值。**<br>
get()函数上面也有简略的介绍，它的作用是，它返回一个内置指针，指向智能指针管理的对象。它的设计是为了在需要向不能使用智能指针的代码传递一个内置指针。什么意思？它只是一个托管指针。来看看这段代码
```cpp
shared_ptr<int> p(new int(42));
int *q = p.get();
{
    // 两个独立的shared_ptr指向相同的内存
    shared_ptr<int>(q);
    // 离开作用域就会释放
}
int foo = *q; // 最后未定义
```
所以这里解释了不能用get()这样的初始化另一个智能指针，get()毕竟是托管，给你的都是已经有的，托管而已，给了你，你也是指向相同的内存。<br>
当然，shared_ptr也可以使用reset操作
```cpp
    string *inum = new string("hhh");
    shared_ptr<string> p5 = make_shared<string>("hi");
    p5.reset(inum);
```
但是他只能用于内置指针传递。<br>
还能传递释放器给shared_ptr `p5.reset(inum,d);`<br>
**那为什么shared_ptr没有release成员？** 没有所有权呗。
讲了那么多，make_shared一直都像是被忽略了。<br>
```cpp
template <class T,class ... Args>
    shared_ptr<T> make_shared(Args&&... args);
```
这是它的源码，他的用途就是制作shared_ptr，返回类型为shared_ptr<T>的对象，该对象拥有并存储指向它的指针(引用次数为1)。<br>
看看怎么使用
```cpp
auto baz =make_shared<pair<int,int> > (30,40);
... baz->first .. << baz->second
```
ok，所以，当我们使用shared_ptr初始化的时候，最好最安全就是使用这个标准库函数，并且使用new肯定还要转换啊，给予所有权，但是make_shared帮你将分配，安全都做好了，而且给你的就是返回的shared_ptr的类型对象，让你的指针指向就行了。<br>
推荐使用哦！<br>
shared_ptr，其实就是一个指针，套上了释放器，套上了计数器，拷贝的时候增加了引用，赋值也增加了引用，相应的也会有递减了引用计数。我们再来看另外一种情况<br>
```cpp
struct Node{
    shared_ptr<Node> pPre;
    shared_ptr<Node> pNext;
    int val;
};
void func(){
    shared_ptr<Node> p1(new Node());
    shared_ptr<Node> p2(new Node());
    cout << p1.use_count() << endl;
    cout <<p2.use_count() << endl;
    p1->pNext = p2;
    p2->pPre = p1;
    cout << p1.use_count() << endl;
    cout <<p2.use_count() << endl;
}
```
我们看到，p1是2，p2也是2，他们互相拷贝引用啊！要想释放p2就要先释放p1，而要想释放p1，就得释放p2，这样就是 **循环引用**了，最后p1和p2指向的内存空间永远都无法释放掉。<br>
那可咋办咧，上面介绍的竟然没有一种能解决，不要慌，不要忙，静静在两旁。<br>
静静往下看看。<br>
### weak_ptr 让静静继续静静 该走的还是让你走
上面这个就是一个环，我们怎样打破这个环，让内存释放呢？使用weak_ptr。介绍一下weak_ptr，一种不控制所指向对象生存期的智能指针，指向由一个shared_ptr管理的对象。看来这也是共享所有权的乐趣，众人帮，不像unique_ptr，一个人孤苦伶仃。<br>
不控制是什么意思？就是weak_ptr，不影响shared_ptr的引用计数。一旦shared_ptr被销毁，那么对象也会被销毁，即使weak_ptr还指向这个对象，这个对象也会被销毁。所以说，该走的还是让你走。<br>
所以它也叫做"弱"共享所有权。<br>
**只引用，不计数**，但是有没有，要检查expired()应运而生。<br>
我们来看一下他的构造以及使用<br>
```cpp
template <class T> class weak_ptr{
    public:
    constexpr weak_ptr() noexcept;
    weak_ptr(const weak_ptr& x) noexcept;
    template <class U> weak_ptr(const weak_ptr<U>& x) noexcept;
    template <class U> weak_ptr(const shared_ptr<U>& x) noexcept;
}
```
所以从构造函数可以看出，这个weak_ptr，可以自己构造，也可以指向share_ptr，而且仅仅是引用。<br>
```cpp
shared_ptr<int> sp(new int(42));
weak_ptr<int> wp(sp);
cout << wp.use_count << endl;
```
那use_count呢？
```cpp
long int use_count() const noexcept;
```
看到了嘛。它并不会改变引用计数。const<br>
那expired是什么？
它只是检查use_count()是不是变为0了，为0返回false，否则返回true。
```cpp
bool expired() const noexcept;
```
这是用来检查一下这个指针所指向的对象是否被销毁了。<br>
所以这就导致对象可能就不存在，因此我们不能使用weak_ptr直接访问对象，况且weak_ptr也没有`*`这个访问运算符重载的过程，就需要调用别的函数，例如lock
```cpp
shared_ptr<T> lock() const noexcept;
```
lock() 会检查weak_ptr所指向的对象是否存在，如果存在就返回一个共享对象shared_ptr。
```cpp
#include <iostream>
#include <memory>

int main () {
  std::shared_ptr<int> sp1,sp2;
  std::weak_ptr<int> wp;
                                       // sharing group:
                                       // --------------
  sp1 = std::make_shared<int> (20);    // sp1
  wp = sp1;                            // sp1, wp

  sp2 = wp.lock();                     // sp1, wp, sp2
  sp1.reset();                         //      wp, sp2

  sp1 = wp.lock();                     // sp1, wp, sp2

  std::cout << "*sp1: " << *sp1 << '\n';
  std::cout << "*sp2: " << *sp2 << '\n';

  return 0;
}
```
很清楚，都输出20。同样，reset就能置空一个weak_ptr<br>
那么为什么，weak_ptr能破环呢？我们继续来看下面这一段代码<br>
```cpp
struct Node{
    weak_ptr<Node> pPre; // 区别⬅️⬅️⬅️
    weak_ptr<Node> pNext; // 区别⬅️⬅️⬅️
    int val;
    Node(){
        cout << "construct" << endl;
    }
    ~Node(){
        cout << "delete" <<endl;
    }
};
void func(){
    shared_ptr<Node> p1(new Node());
    shared_ptr<Node> p2(new Node());
    cout << p1.use_count() << endl;
    cout << p2.use_count() << endl;
    p1->pNext = p2;
    p2->pPre = p1;
    cout << p1.use_count() << endl;
    cout << p2.use_count() << endl;
}
```
这就打破了循环引用的环，因为每一个shared_ptr都会将引用计数设为1，那么每次用都会递增，所以要是不递增，用原来的指向的对象不就解决了嘛。改一下结构就完美解决，而且还能调用了析构函数。<br>
### shared_ptr与unique_ptr释放器 一动一静显神通
讲完了weak_ptr，突然感觉，智能指针的发明确实伟大！单身🐶迷茫的时候容易犯的错误变得不再容易。那么，每次我们都会发现，这两个指针，会有一个释放器。<br>
unique_ptr版本
```cpp
unique_ptr<T,D> up;
```
shared_ptr版本
```cpp
shared_ptr<T> p(q,d);
```
不管大小写的d都是delete，释放器。向unique_ptr我们之前介绍过，这是一个确定的删除器，在编译时就已经决定了它的类型了。<br>
unique_ptr
```cpp
template<typename T,typename D = default_delete<T> > // default_delete是一个无状态类
class unique_ptr{
    public:
        using pointer = ptr;
        using element_type = T;
        using deleter_type = D;
        ...
```
那shared_ptr咧
```cpp
template<typename U>
class shared_ptr{
    public:
        using element_type = U;
        constexpr shared_ptr() noexcept;
        constexpr shared_ptr(nullptr_t):shared_ptr(){} // 空对象
        template <class U> explicit shared_ptr(U* p); // 显式构造 不存在隐式转换
        ...
```
看到这个template就明白，原来shared_ptr一直没有固定类型的释放器，虽然默认是delete，但是也可以使用可调用对象，看看下面这个可调用对象的例子
```cpp
#include <iostream>
#include <memory>

int main () {
   auto deleter = [](Node* p){
    cout << "[deleter called]\n"; 
    delete p;
    };
    // shared_ptr<int> foo (new int,deleter);
    // cout << "use_count: " << foo.use_count() << '\n';
    shared_ptr<Node> bar(new Node(),deleter);
  return 0;                        // [deleter called]
}
```
所以释放器，无论是unique_ptr还是shared_ptr都必须保存为一个指针或一个封装了指针的类。但我们也可以确定，shared_ptr不是将释放器直接保存为一个成员，因为它的类型直到运行时才知道。<br>
因为shared_ptr只有一个模版参数，而unique_ptr有两个模版参数，所以在这个unique_ptr的工作方式，我们可以看出来，这个释放器的类型是unique_ptr类型的一部分，所以释放器可以直接保存在unique_ptr对象中。<br>
两个释放器都是对其保存的指针调用用户提供提供的释放器或执行delete。<br>
所以，总结一下，通过编译时绑定释放器，unique_ptr避免了间接调用释放器的运行时开销。<br>
通过运行时绑定释放器，shared_ptr使用户重载释放器更加方便。<br>
所以这些都是以对象来管理资源的例子，一个一个shared_ptr,unique_ptr都在以对象的形式管理着资源，防止资源的泄露，动态内存再也不用害怕泄漏了。<br>
额，那可调用对象又有哪些呢？怎么用呢？为什么shared_ptr可以这样用可调用对象呢？
### 未完待续...