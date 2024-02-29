#include <iostream>
#include <thread>

int main() {	
	std::thread t1([]() {std::cout << "hello "; });
	t1.join();

	std::thread t2([](std::string str) {std::cout << str << std::endl; }, "world");
	t2.join();

	return 0;
}