#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // Check if any of the numbers are even
    bool anyEven = std::any_of(numbers.begin(), numbers.end(),
                               [](int i) { return i % 2 == 0; });

    if (anyEven) {
        std::cout << "There is at least one even number in the list."
                  << std::endl;
    } else {
        std::cout << "There are no even numbers in the list." << std::endl;
    }

    return 0;
}