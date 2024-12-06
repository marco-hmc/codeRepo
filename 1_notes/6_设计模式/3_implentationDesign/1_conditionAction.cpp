#include <functional>
#include <vector>

struct ConditionAction {
    std::function<bool(int)> condition;
    std::function<void()> action;
};

int main() {
    std::vector<int> data = {1, 2, 3, 4, 5};

    std::vector<ConditionAction> conditions = {
        {[](int x) { return x % 2 == 0; }, []() { /* do something */ }},
        {[](int x) { return x % 3 == 0; }, []() { /* do something else */ }},
        // 更多的条件和操作...
    };

    for (int x : data) {
        for (const auto &ca : conditions) {
            if (ca.condition(x)) {
                ca.action();
                break;
            }
        }
    }

    return 0;
}