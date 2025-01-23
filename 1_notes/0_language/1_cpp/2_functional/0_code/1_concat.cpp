#include <functional>
#include <iostream>

// c14标准这么写
// template <typename T>
// auto concat(T t) {
//     return [=](auto ...parameters) {
//         return t(parameters...);
//     };
// }

// template <typename T, typename ...Ts>
// auto concat(T t, Ts ...ts) {
//     return [=](auto ...parameters) {
//         return t(concat(ts...)(parameters...));
//     };
// }

template <typename T, typename... Ts>
auto concat(T t, Ts... ts) {
    if constexpr (sizeof...(ts) > 0) {
        return
            [=](auto... parameters) { return t(concat(ts...)(parameters...)); };
    } else {
        return [=](auto... parameters) { return t(parameters...); };
    }
}

void test_concat() {
    auto twice = [](int i) { return i * 2; };
    auto thrice = [](int i) { return i * 3; };
    auto combined = concat(twice, thrice, std::plus<int>{});

    std::cout << combined(2, 3) << '\n';
}

int main() {
    auto twice = [](int i) { return i * 2; };
    auto thrice = [](int i) { return i * 3; };
    auto combined = concat(twice, thrice, std::plus<int>{});

    std::cout << combined(2, 3) << '\n';
    return 0;
}