#include <iostream>
#include <vector>

#include <algorithm>
#include <iostream>
#include <vector>

// 定义协程上下文结构
struct CoroutineContext {
  int state;    // 状态机的当前状态
  int localVar; // 局部变量
};

// 定义协程入口函数类型
using CoroutineEntry = void (*)(CoroutineContext *);

// 协程函数1
void coroutineFunction1(CoroutineContext *context) {
  switch (context->state) {
  case 0:
    std::cout << "Coroutine 1 started" << std::endl;
    context->localVar = 42;
    context->state = 1;
    return;
  case 1:
    std::cout << "Coroutine 1 resumed, localVar = " << context->localVar
              << std::endl;
    context->state = 2;
    return;
  case 2:
    std::cout << "Coroutine 1 finished" << std::endl;
    return;
  }
}

// 协程函数2
void coroutineFunction2(CoroutineContext *context) {
  switch (context->state) {
  case 0:
    std::cout << "Coroutine 2 started" << std::endl;
    context->localVar = 84;
    context->state = 1;
    return;
  case 1:
    std::cout << "Coroutine 2 resumed, localVar = " << context->localVar
              << std::endl;
    context->state = 2;
    return;
  case 2:
    std::cout << "Coroutine 2 finished" << std::endl;
    return;
  }
}

int main() {
  std::vector<int> source = {1, 2, 3, 4, 5};

  {
    std::vector<int> target(source.size());
    std::transform(source.begin(), source.end(), target.begin(),
                   [](const auto &x) { return x * 2; });
  }

  {
    std::vector<int> target;
    target.reserve(source.size());
    std::transform(source.begin(), source.end(), target.begin(),
                   [](const auto &x) { return x * 2; });
  }

  return 0;
}