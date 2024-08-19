namespace jc {

extern int x; // 1

int f(int x) { // 2
  if (x < 0) {
    int x = 1; // 3
    f(x);      // 使用 3
  }
  return x + ::x; // 分别使用 2、1
}

} // namespace jc

namespace jc {

struct A {};
struct B {};
void f1(int) {}
void f2(A) {}

} // namespace jc

namespace jd {

void f1(int i) {
  f1(i); // 调用 jd::f1()，造成无限递归
}

void f2(jc::A t) {
  f2(t); // 通过 t 的类型 jc::A 看到 jc，通过 jc 看到 jc::f2()
         // 因为 jd::f2() 也可见，此处产生二义性调用错误
}

void f3(jc::B t) {
  f3(t); // 通过 t 的类型 jc::B 看到 jc，但 jc 中无 jc::f3()
         // 此处调用 jd::f3()，造成无限递归
}

} // namespace jd

// * ADL
// 是通过实参查找，对于函数模板，查找前无法先得知其为函数，也就无法确定实参，因此不会使用
// ADL

namespace je {

class A {};

template <typename> void f(A *) {}

} // namespace je

void g(je::A *p) {
  f<int>(p); // 错误，不知道 f<int> 是函数，所以不知道 p 是实参，不会用 ADL
}

int main() {}
