#include <iostream>
#include <map>
#include <string>
#include <vector>

// Map 函数
std::vector<std::pair<std::string, int>> map(const std::string& text) {
    std::vector<std::pair<std::string, int>> result;
    std::string word;
    for (char ch : text) {
        if (std::isalpha(ch)) {
            word += std::tolower(ch);
        } else if (!word.empty()) {
            result.emplace_back(word, 1);
            word.clear();
        }
    }
    if (!word.empty()) {
        result.emplace_back(word, 1);
    }
    return result;
}

// Reduce 函数
std::map<std::string, int> reduce(
    const std::vector<std::pair<std::string, int>>& mapped_data) {
    std::map<std::string, int> result;
    for (const auto& pair : mapped_data) {
        result[pair.first] += pair.second;
    }
    return result;
}

int main() {
    std::string text = "Hello world, hello MapReduce!";

    // Map 阶段
    auto mapped_data = map(text);

    // Shuffle 和 Sort 阶段（在这个简单示例中省略）

    // Reduce 阶段
    auto reduced_data = reduce(mapped_data);

    // 输出结果
    for (const auto& pair : reduced_data) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    return 0;
}