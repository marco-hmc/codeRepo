#include <iostream>
#include <thread>

// 仿函数
class Fctor {
public:
	// 具有一个参数
	void operator() () {

	}
};
/*
一个仿函数类生成的对象，使用起来就像一个函数一样，比如上面的对象f，当使用f()时就调用operator()运算符。所以也可以让它成为线程类的第一个参数，如果这个仿函数有参数，同样的可以写在线程类的后几个参数上。
而t2之所以编译错误，是因为编译器并没有将Fctor()解释为一个临时对象，而是将其解释为一个函数声明，编译器认为你声明了一个函数，这个函数不接受参数，同时返回一个Factor对象。解决办法就是在Factor()外包一层小括号()，或者在调用std::thread的构造函数时使用{}，这是c++11中的新的列表初始化语法。
但是，如果重载的operator()运算符有参数，就不会发生上面的错误。
*/
int main() {	
	Fctor f;
	std::thread t1(f);
	// std::thread t2(Fctor()); // 编译错误 
	std::thread t3((Fctor())); // ok
	std::thread t4{ Fctor() }; // ok

	t1.join();
	t3.join();
	t4.join();

	return 0;
}
