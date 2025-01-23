#include <iostream>
#include <string>

/*
  ## ADL（Argument-Dependent Lookup，实参依赖查找）

  ADL 是 C++ 中的一种查找函数的机制。当函数调用时，编译器不仅查找局部作用域中的函数，还会根据函数的参数类型查找与其关联的命名空间或类。ADL 使得某些函数可以“隐式地”找到，而不需要显式指定命名空间或类名。

  ## ADL 的基本原理

  当你调用一个函数并传递一个类类型的参数时，编译器会通过 ADL 查找该函数。ADL 查找的范围包括：
  - 函数所在的局部作用域。
  - 与参数类型相关联的命名空间或类。

  示例：ADL 查找函数
*/

namespace jc {

    struct A {};

    void f(const A&) {
        std::cout << "jc::f(const A&)" << std::endl;
    }  // f() 是 A 的逻辑组成部分

}  // namespace jc

int main() {
    jc::A a;
    f(a);  // 通过 ADL 找到 jc::f()，如果没有 ADL，需要写成 jc::f(a)

    std::string s;
    std::cout << s;  // std::operator<<() 是 std::string 的逻辑组成部分
    // 如果没有 ADL，需要写成 std::operator<<(std::cout, s)

    return 0;
}

/*
  在上面的例子中：
  - `f(a)` 通过 ADL 找到 `jc::f()`，而无需显式地写成 `jc::f(a)`。
  - 对于 `std::cout << s;`，通过 ADL 查找到 `std::operator<<()`，无需显式写出 `std::operator<<(std::cout, s)`。

  注意：ADL 不会考虑作用域中的 `using` 声明或 `using namespace` 语句。因此，即使在某个命名空间内通过 `using` 引入了其他命名空间的函数，也不会影响 ADL 的查找过程。


/*

    #include <iostream>
  ## ADL 忽略 `using` 声明

  ADL（Argument-Dependent Lookup，实参依赖查找）不会考虑作用域中的 `using` 声明或 `using namespace` 语句。因此，即使在某个命名空间内通过 `using` 引入了其他命名空间的函数，也不会影响 ADL 的查找过程。

  示例：ADL 忽略 `using` 声明

  ADL 会查找与实参类型关联的命名空间或类，具体的关联规则如下：
  - **内置类型**：没有关联的命名空间或类，ADL 不会发生。
  - **指针和数组类型**：查找所引用类型的关联命名空间和类。
  - **枚举类型**：查找与枚举类型声明所在的命名空间。
  - **类成员**：查找该成员所在的类。
  - **类类型**：查找与该类相关的所有命名空间和类，包括该类本身、直接和间接的基类。
  - **函数类型**：查找函数参数类型和返回类型相关的命名空间和类。
  - **类成员指针类型**：查找类成员所在的类和命名空间。


namespace jc {
    template <typename T>
    constexpr int f(T) {
        return 1;
    }
}  // namespace jc

namespace jd {

    using namespace jc;  // 忽略 using 声明，不会调用 jc::f

    enum Color { red };
    constexpr int f(Color) { return 2; }

}  // namespace jd

constexpr int f(int) { return 3; }

static_assert(::f(jd::red) == 3);  // 受限的函数名称，不使用 ADL
static_assert(f(jd::red) == 2);    // 使用 ADL 找到 jd::f()

int main() {
    std::cout << "::f(jd::red) = " << ::f(jd::red) << std::endl;  // 输出 3
    std::cout << "f(jd::red) = " << f(jd::red) << std::endl;      // 输出 2
    return 0;
}


  在这个例子中：

  - 在 `jd` 命名空间内，`using namespace jc;` 不会影响 ADL。调用 `::f(jd::red)` 会查找全局作用域中的 `f(int)`。
  - `f(jd::red)` 会通过 ADL 查找 `jd::f()`，因为 `jd::f()` 是 `jd::red` 的逻辑组成部分。

*/

/*
// #include <iostream>

// /*
//   ## ADL 与友元函数

//   如果一个类的友元函数所在类是 ADL 的关联类集合的一部分，那么该友元函数可以在外围作用域找到并调用。否则，若该类未实例化，则该友元函数不可见。

//   示例：ADL 与友元函数
// */

// namespace jc {

//     template <typename T>
//     class A {
//         friend void f() { std::cout << "friend void f()" << std::endl; }
//         friend void f(A<T>) { std::cout << "friend void f(A<T>)" << std::endl; }
//     };

//     void g(const A<int>& a) {
//         // f();   // f() 无参数，不能使用 ADL，不可见
//         f(a);  // f(A<int>) 关联类 A<int> 所以可见，若类 A<int> 未实例化则调用时实例化
//     }

// }  // namespace jc

// int main() {
//     jc::A<int> a;
//     jc::g(a);
//     return 0;
// }

// /*
//   在这个示例中：

//   - `f()` 是 `A<T>` 的友元函数，但由于 `f()` 不带参数，它不能通过 ADL 查找。
//   - `f(a)` 使用了 `A<int>` 类型作为参数，因此可以通过 ADL 查找到 `f(A<int>)`，且如果 `A<int>` 类未实例化，调用时会触发类实例化。
// */

/*
// namespace jc {

// extern int x; // 1

// int f(int x) { // 2
//   if (x < 0) {
//     int x = 1; // 3
//     f(x);      // 使用 3
//   }
//   return x + ::x; // 分别使用 2、1
// }

// } // namespace jc

// namespace jc {

// struct A {};
// struct B {};
// void f1(int) {}
// void f2(A) {}

// } // namespace jc

// namespace jd {

// void f1(int i) {
//   f1(i); // 调用 jd::f1()，造成无限递归
// }

// void f2(jc::A t) {
//   f2(t); // 通过 t 的类型 jc::A 看到 jc，通过 jc 看到 jc::f2()
//          // 因为 jd::f2() 也可见，此处产生二义性调用错误
// }

// void f3(jc::B t) {
//   f3(t); // 通过 t 的类型 jc::B 看到 jc，但 jc 中无 jc::f3()
//          // 此处调用 jd::f3()，造成无限递归
// }

// } // namespace jd

// // * ADL
// // 是通过实参查找，对于函数模板，查找前无法先得知其为函数，也就无法确定实参，因此不会使用
// // ADL

// namespace je {

// class A {};

// template <typename> void f(A *) {}

// } // namespace je

// void g(je::A *p) {
//   f<int>(p); // 错误，不知道 f<int> 是函数，所以不知道 p 是实参，不会用 ADL
// }

// int main() {}

*/
