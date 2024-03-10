#include <memory>

// `std::make_unique`相比于直接使用`new`有以下几个优点:

// 1.
// **异常安全**:`std::make_unique`提供了更好的异常安全性.当你在调用一个函数并将`new`和`std::unique_ptr`一起使用时,如果在`new`和`std::unique_ptr`构造之间发生异常,可能会导致内存泄漏.而`std::make_unique`则可以避免这种情况,因为它在同一步骤中分配内存并构造`std::unique_ptr`.

// 2.
// **避免裸`new`**:在现代C++编程中,通常推荐避免使用裸`new`,因为它很容易导致内存泄漏/难以匹配的`delete`等问题.`std::make_unique`提供了一种更安全/更简洁的方式来创建`std::unique_ptr`.

// 3. **简洁性**:`std::make_unique`的语法更简洁,不需要写出`new`和类型名.

// 所以,尽管在你给出的代码片段中,`std::make_unique`和`new`的效果是一样的,但在实际编程中,推荐使用`std::make_unique`来创建`std::unique_ptr`.

int main() {
  {
    std::unique_ptr<int> ptr = std::make_unique<int>(42);
    *ptr = 100;
  }
  {
    std::unique_ptr<int> ptr(new int(42));
    *ptr = 100;
  }
  {
    // 初始化方式1
    std::unique_ptr<int> sp1(new int(123));

    // 初始化方式2
    std::unique_ptr<int> sp2;
    sp2.reset(new int(123));

    // 初始化方式3
    std::unique_ptr<int> sp3 = std::make_unique<int>(123);
  }
  return 0;
}