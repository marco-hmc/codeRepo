#include <boost/type_erasure/any.hpp>
#include <iostream>

using namespace boost::type_erasure;

struct X {
    void operator()() const { std::cout << "X called\n"; }
};

struct Y {
    void operator()() const { std::cout << "Y called\n"; }
};

int main() {
    any<X> x = X();
    any<Y> y = Y();

    x();  // 输出: X called
    y();  // 输出: Y called
}