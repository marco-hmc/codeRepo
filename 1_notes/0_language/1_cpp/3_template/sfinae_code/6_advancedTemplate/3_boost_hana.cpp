#include <boost/hana.hpp>
#include <iostream>

namespace hana = boost::hana;

int main() {
    auto t = hana::make_tuple(1, 2.5, "hello");

    hana::for_each(t, [](auto x) { std::cout << x << std::endl; });

    return 0;
}