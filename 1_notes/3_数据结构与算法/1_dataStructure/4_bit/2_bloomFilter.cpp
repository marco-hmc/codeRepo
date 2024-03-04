#include <bitset>
#include <functional>
#include <iostream>


class BloomFilter {
private:
  std::bitset<1000000> filter;
  std::hash<std::string> hashFunction;

public:
  void insert(const std::string &item) {
    size_t hash = hashFunction(item);
    filter[hash % filter.size()] = true;
  }

  bool contains(const std::string &item) {
    size_t hash = hashFunction(item);
    return filter[hash % filter.size()];
  }
};

int main() {
  BloomFilter filter;

  filter.insert("apple");
  filter.insert("banana");
  filter.insert("orange");

  std::cout << "Contains apple: " << filter.contains("apple") << std::endl;
  std::cout << "Contains grape: " << filter.contains("grape") << std::endl;

  return 0;
}