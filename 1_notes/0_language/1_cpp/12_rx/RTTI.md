# RTTI（Runtime Type Identification，运行时类型识别）
RTTI（Runtime Type Identification，运行时类型识别）是C++语言中的一项机制，允许程序在运行时动态地确定对象的类型。这项机制对于实现诸如类型安全的向下转型（downcasting）、实现基于类型的行为以及调试等场景非常有用。RTTI主要通过两个关键特性实现：``typeid``操作符和``dynamic_cast``操作符。

## typeid操作符
typeid是一个C++关键字，用于在编译时或运行时获取表达式或类型的名字。当应用于一个对象时，它会返回一个包含该对象实际类型信息的std::type_info对象的引用。std::type_info对象包含了类型的名字（通常为人类可读的字符串形式）以及其他可能的类型相关信息，可以用来比较类型是否相同。

使用typeid的一个典型场景是确定对象的动态类型，尤其是在多态环境中。例如，当你有一个指向基类的指针，但实际上它指向的是一个派生类对象，typeid可以帮助你识别出这一点。

## dynamic_cast操作符
dynamic_cast是另一个C++提供的运行时类型转换操作符，它允许安全地将基类的指针或引用转换为派生类的指针或引用。与C风格的强制类型转换（如reinterpret_cast或旧式的C样式cast）不同，dynamic_cast会在转换前检查转换的安全性。如果转换是合法的（即对象实际上是目标派生类的实例），则转换成功；否则，dynamic_cast会返回一个空指针（对于指针类型）或抛出一个std::bad_cast异常（对于引用类型，仅在使用RTTI时）。

dynamic_cast依赖于对象的类型信息，因此只有当转换的源类型含有至少一个虚函数（从而具有虚函数表）时，dynamic_cast才能工作。这是因为虚函数的存在表明了类型系统中存在多态性，而这是dynamic_cast实现其功能的基础。

## RTTI的启用与禁用
RTTI默认在大多数编译器中是启用的，但也可以通过编译器选项禁用，以减少代码体积或提高性能，尤其是在不需要类型识别的环境下。禁用RTTI意味着typeid和dynamic_cast将无法正常工作。

## 何时使用RTTI
尽管RTTI提供了强大的动态类型检查和转换能力，但过度依赖它可能导致代码的结构不够清晰，并可能降低效率。设计良好的面向对象程序往往更倾向于使用虚函数来实现多态行为，减少对RTTI的直接需求。然而，在某些特定情况下，如在日志记录、序列化、或需要进行复杂的类型检查和转换的框架中，RTTI仍是一个不可或缺的工具。

C++引入RTTI的目的：让程序在运行时，通过基类指针或者基类引用来获得这个指针或者引用的所指向的对象的类型。

## RTTI例子
```cpp
	Base *pb = new Derive(); // 父类指针指向一个子类对象
	pb->g();

	Derive myderive;
	Base &yb = myderive;	// 父类引用一个子类对象
	yb.g();
```
1. c++运行时类型识别RTTI，要求父类中必须至少有一个虚函数；如果父类中没有虚函数，那么得到RTTI就不准确；
2. RTTI就可以在执行期间查询一个多态指针，或者多态引用的信息了；
3. RTTI能力靠typeid和dynamic_cast运算符来体现；
```cpp
	cout << typeid(*pb).name() << endl;	// class derive
	cout << typeid(yb).name() << endl;	// class derive

	Derive *pderive = dynamic_cast<Derive *>(pb);
	if (pderive != NULL)
	{
		cout << "pb实际是一个Derive类型" << endl;
		pderive->myselffunc(); //调用自己专属函数
	}	
```
