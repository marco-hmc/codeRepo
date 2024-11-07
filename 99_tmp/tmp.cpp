#include <deque>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>

int main() {
    std::istream_iterator<int> it_cin{std::cin};
    std::istream_iterator<int> end_cin;

    std::deque<int> v;
    std::copy(it_cin, end_cin, std::back_inserter(v));

    std::istringstream sstr{"123 456 789"};

    auto deque_middle(std::next(std::begin(v), static_cast<int>(v.size()) / 2));

    std::copy(std::istream_iterator<int>{sstr}, {},
              std::inserter(v, deque_middle));

    std::initializer_list<int> il2{-1, -2, -3};
    std::copy(std::begin(il2), std::end(il2), std::front_inserter(v));

    std::copy(std::begin(v), std::end(v),
              std::ostream_iterator<int>{std::cout, ", "});
    std::cout << '\n';
}