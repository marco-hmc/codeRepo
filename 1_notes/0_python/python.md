## python

* python的环境管理
Python的环境管理通常通过虚拟环境(Virtual Environments)来实现.虚拟环境是一个独立的Python环境,可以有自己的Python解释器/库和模块,这样可以避免不同项目之间的依赖冲突.
python虚拟环境管理有以下三种
  * venv
  * pipenv
  * conda

* python的yield有啥用？
`yield`是Python的一个关键字,主要用于在函数中创建一个生成器(generator).生成器是一种特殊的迭代器,它的特点是可以在产生每个值后暂停函数的执行,而不是一次性计算所有的值.

当你调用一个包含`yield`的函数时,函数的代码并不会立即执行,而是返回一个生成器对象.当你从生成器中请求值(例如通过`next()`函数或在`for`循环中)时,函数才会执行,直到遇到`yield`语句,然后产生一个值并暂停执行.下次请求值时,函数会从上次暂停的地方继续执行.

使用`yield`的主要优点是节省内存.因为生成器只在需要时才会计算下一个值,所以它可以用于处理大规模数据,或者用于创建无限序列.

以下是一个使用`yield`的简单例子:

```python
def count_up_to(n):
    i = 1
    while i <= n:
        yield i
        i += 1

for number in count_up_to(5):
    print(number)
```

在这个例子中,`count_up_to`函数是一个生成器,它会依次产生从1到n的所有数字.在`for`循环中,我们从生成器中获取值,并打印出来.

* python有私有成员吗？怎么实现的？是真正的私有成员吗？
Python确实有一种机制可以创建类的私有成员,这主要通过在成员名前加两个下划线`__`来实现.例如:

```python
class MyClass:
    def __init__(self):
        self.__private_member = 0
```

在这个例子中,`__private_member`就是一个私有成员.Python会对这种成员名进行名称改编(name mangling),在其前面加上`_classname`,这样就可以防止它被子类中的同名成员覆盖.所以,你不能直接通过`object.__private_member`来访问这个成员,而应该使用`object._MyClass__private_member`.

然而,需要注意的是,Python的这种私有成员并不是真正的私有.在Python中,所有的属性和方法都是公开的.私有成员只是一种编程约定,用来提示这个成员不应该在类外部直接访问.实际上,你仍然可以通过名称改编后的名字来访问这个成员,所以它并不是真正的私有.

总的来说,Python的私有成员主要是用来避免命名冲突和保护内部状态,而不是用来严格限制访问.

* python的装饰器要在什么场景使用？
https://www.zhihu.com/question/31265857

* python的property装饰器有啥用？

* python的魔法方法是什么东西？
Python的魔法方法,也被称为特殊方法或者双下划线方法,是Python类中的一种特殊的方法,它们有固定的名称,以双下划线开始和结束,例如`__init__`/`__str__`等.

魔法方法定义了类的一些特殊行为.例如,`__init__`方法定义了类的初始化行为,`__str__`方法定义了类的字符串表示形式,`__add__`方法定义了类的加法行为等.

Python解释器在遇到特定的语法时会自动调用相应的魔法方法.例如,当你创建一个类的实例时,Python会自动调用`__init__`方法;当你打印一个类的实例时,Python会自动调用`__str__`方法;当你使用`+`运算符对两个类的实例进行加法运算时,Python会自动调用`__add__`方法.

通过定义魔法方法,你可以自定义类的行为,使得类的实例可以像内置类型一样使用.例如,你可以定义一个`Vector`类,然后通过定义`__add__`方法,使得两个`Vector`实例可以直接使用`+`运算符进行加法运算.

总的来说,Python的魔法方法是一种非常强大的工具,它使得你可以自定义类的行为,使得类的实例更加易用和直观.


* python的反射机制是什么东西？

* python的多线程编程
https://www.liujiangblog.com/course/python/79

* python的网络编程

* python语法进阶
https://python3-cookbook.readthedocs.io/zh-cn/latest/copyright.html