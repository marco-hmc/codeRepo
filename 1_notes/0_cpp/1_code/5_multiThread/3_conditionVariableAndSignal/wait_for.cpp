#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

std::condition_variable_any cv;
int value;

void read_value() {
 std::cin >> value;
 cv.notify_one();
}

int main ()
{
 std::cout << "Please, enter an integer (I'll be printing dots): ";
 std::thread th (read_value);

 std::mutex mtx;
 mtx.lock();
 while (cv.wait_for(mtx, std::chrono::seconds(1)) == std::cv_status::timeout) {
   std::cout << '.';
 }

 std::cout << "You entered: " << value << '\n';
 mtx.unlock();

 th.join();

 return 0;
}
