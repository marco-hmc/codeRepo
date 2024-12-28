#include <boost/spirit/include/qi.hpp>
#include <iostream>

int main() {
    using namespace boost::spirit::qi;

    std::string input = "42";
    int result;

    if (parse(input.begin(), input.end(), int_, result)) {
        std::cout << "Parsed successfully: " << result
                  << std::endl;  // 输出: Parsed successfully: 42
    } else {
        std::cout << "Parse failed!" << std::endl;
    }

    return 0;
}