// 字典结构（Dictionary Structure）
// 字典结构（或映射结构）在元编程中常常用来表示键值对。
// 可以通过模板元编程实现类似于哈希表的结构，或者通过递归模板和类型萃取构造静态的字典结构。

#include <iostream>
#include <string>

namespace dict_meta {
    template <typename Key, typename Value>
    struct pair {
        Key key;
        Value value;
    };

    template <typename... Pairs>
    struct dictionary;

    template <typename Key, typename Value, typename... Rest>
    struct dictionary<pair<Key, Value>, Rest...> {
        pair<Key, Value> first;
        dictionary<Rest...> rest;

        Value& operator[](const Key& key) {
            if (first.key == key) {
                return first.value;
            }
            return rest[key];  // 递归查找
        }
    };

    template <>
    struct dictionary<> {};  // 终止递归
}  // namespace dict_meta

int main() {
    dict_meta::dictionary<dict_meta::pair<int, std::string>,
                          dict_meta::pair<double, std::string>>
        dict = {{1, "one"}, {{2.0, "two"}}};

    std::cout << "Key 1: " << dict[1] << std::endl;
    std::cout << "Key 2.0: " << dict[2.0] << std::endl;

    return 0;
}