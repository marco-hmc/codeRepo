#include <algorithm>
#include <functional>
#include <iostream>
#include <ostream>
#include <vector>

/*
    纯粹的函数编程一定是不会修改状态变量，一定是单参数的；没有副作用；
*/
namespace ProcedureOrientedProgramming {

    void task() {
        std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        std::vector<int> filtered_numbers;
        for (int i = 0; i < numbers.size(); i++) {
            if (numbers[i] % 2 == 0 && numbers[i] > 5) {
                filtered_numbers.push_back(numbers[i]);
                std::cout << numbers[i] << " ";
            }
        }

        std::cout << "Filtered numbers: ";
        for (int x : filtered_numbers) {
            std::cout << x << " ";
        }
        std::cout << std::endl;
    }
}  // namespace ProcedureOrientedProgramming

namespace FunctionalProgramming {

    auto make_filter(std::function<bool(int)> predicate) {
        return [predicate](const std::vector<int>& vec) {
            std::vector<int> result;
            std::copy_if(vec.begin(), vec.end(), std::back_inserter(result),
                         predicate);
            return result;
        };
    }

    void task() {
        std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        auto is_even = [](int x) { return x % 2 == 0; };
        auto is_greater_than_5 = [](int x) { return x > 5; };

        auto composite_filter =
            [is_even, is_greater_than_5](const std::vector<int>& vec) {
                std::vector<int> result;
                std::copy_if(vec.begin(), vec.end(), std::back_inserter(result),
                             [is_even, is_greater_than_5](int x) {
                                 return is_even(x) && is_greater_than_5(x);
                             });
                return result;
            };

        std::vector<int> filtered_numbers = composite_filter(numbers);

        std::cout << "Filtered numbers: ";
        for (int x : filtered_numbers) {
            std::cout << x << " ";
        }
        std::cout << std::endl;
    }
}  // namespace FunctionalProgramming

namespace PureFunctionalProgramming {

    /*
        在实际开发编程中，make_multiplier 和 make_filter 不要看成是新的代码。因为这些实现，完全是和业务解耦的。
        业务是要求给定一个数组，输出满足条件A和条件B的数据。在业务的task()实现中可以看到，只是给出了条件A和条件B的实现。
        相对比原来的面向过程的实现，这里的实现更加灵活，更加容易维护。
        当添加新的条件C时，只需要接着组合即可，而不需要修改原来的代码。优雅地提供了屎山拉屎的方式。
        而且利于并行化，因为这里的函数是纯函数，没有副作用，没有状态，可以并行执行。也就是说，在make_filter()中，可以并行执行，不会有数据竞争。
        std::copy_if()就是提供std::execution::par，可以并行执行的。
    */

    auto make_filter(std::function<bool(int)> predicate) {
        return [predicate](const std::vector<int>& vec) {
            std::vector<int> result;
            std::copy_if(vec.begin(), vec.end(), std::back_inserter(result),
                         predicate);
            return result;
        };
    }

    // 定义一个高阶函数，接受两个谓词函数，并返回一个新的谓词函数
    auto make_composite_filter(std::function<bool(int)> predicate1) {
        return [predicate1](std::function<bool(int)> predicate2) {
            return [predicate1, predicate2](int x) {
                return predicate1(x) && predicate2(x);
            };
        };
    }

    void task() {
        std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        auto is_even = [](int x) { return x % 2 == 0; };
        auto is_greater_than_5 = [](int x) { return x > 5; };
        auto is_less_than_10 = [](int x) { return x < 10; };

        auto composite_filter =
            make_composite_filter(is_greater_than_5)(is_even);

        {
            // original
            std::vector<int> filtered_numbers =
                make_filter(composite_filter)(numbers);

            std::cout << "Filtered numbers: ";
            for (int x : filtered_numbers) {
                std::cout << x << " ";
            }
            std::cout << std::endl;
        }

        {
            // new
            auto composite_filter2 =
                make_composite_filter(composite_filter)(is_less_than_10);
            std::vector<int> filtered_numbers =
                make_filter(composite_filter)(numbers);
            std::cout << "Filtered numbers: ";
            for (int x : filtered_numbers) {
                std::cout << x << " ";
            }
            std::cout << std::endl;
        }
    }
}  // namespace PureFunctionalProgramming

namespace ModernFunctionalProgramming {
    /*
        现代c++进一步提升，提供了ranges，可以更加优雅地实现函数式编程。
    */

    // void task() {
    //     const std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    //     auto is_even = [](int x) { return x % 2 == 0; };
    //     auto is_greater_than_5 = [](int x) { return x > 5; };
    //     auto is_less_than_10 = [](int x) { return x < 10; };

    //     auto result1 = numbers | std::views::filter(is_greater_than_5) |
    //                    std::views::filter(is_even);

    //     std::cout << "Filtered numbers (greater than 5 and even): ";
    //     for (int x : result1) {
    //         std::cout << x << " ";
    //     }
    //     std::cout << std::endl;

    //     auto result2 = result1 | std::views::filter(is_less_than_10);

    //     std::cout
    //         << "Filtered numbers (greater than 5, even, and less than 10): ";
    //     for (int x : result2) {
    //         std::cout << x << " ";
    //     }
    //     std::cout << std::endl;
    // }
}  // namespace ModernFunctionalProgramming

int main() {
    ProcedureOrientedProgramming::task();
    FunctionalProgramming::task();
    PureFunctionalProgramming::task();
    // ModernFunctionalProgramming::task();

    return 0;
}