**49. 了解new-handler的行为 （Understand the behavior of the new-handler)**

当new无法申请到新的内存的时候，会不断的调用new-handler，直到找到足够的内存,new_handler是一个错误处理函数：
```c++
namespace std{
    typedef void(*new_handler)();
    new_handler set_new_handler(new_handler p) throw();
}
```

一个设计良好的new-handler要做下面的事情：
+ 让更多内存可以被使用
+ 安装另一个new-handler，如果目前这个new-handler无法取得更多可用内存，或许他知道另外哪个new-handler有这个能力，然后用那个new-handler替换自己
+ 卸除new-handler
+ 抛出bad_alloc的异常
+ 不返回，调用abort或者exit

new-handler无法给每个class进行定制，但是可以重写new运算符，设计出自己的new-handler
此时这个new应该类似于下面的实现方式：
```c++
void* Widget::operator new(std::size_t size) throw(std::bad_alloc){
    NewHandlerHolder h(std::set_new_handler(currentHandler));      // 安装Widget的new-handler
    return ::operator new(size);                                   //分配内存或者抛出异常，恢复global new-handler
}
```

总结：
+ set_new_handler允许客户制定一个函数，在内存分配无法获得满足时被调用
+ Nothrow new是一个没什么用的东西

**52. 写了placement new也要写placement delete（Write placement delete if you write placement new)**

如果operator new接受的参数除了一定会有的size_t之外还有其他的参数，这个就是所谓的palcement new

void* operator new(std::size_t, void* pMemory) throw(); //placement new
static void operator delete(void* pMemory) throw();     //palcement delete，此时要注意名称遮掩问题

