#include <algorithm>
#include <iostream>
#include <list>
#include <vector>

// 简化的哈希函数,仅用于演示
size_t simpleHash(const std::string &key) {
  size_t hash = 0;
  for (char c : key) {
    hash = hash * 31 + c;
  }
  return hash;
}

// 键-值对
template <typename K, typename V> struct KeyValuePair {
  K key;
  V value;
};

// 哈希映射类
template <typename K, typename V, typename Hash = std::hash<K>> class HashMap {
private:
  std::vector<std::list<KeyValuePair<K, V>>> buckets;
  Hash hashFunction;

public:
  // 构造函数,指定桶的数量
  explicit HashMap(size_t bucketCount = 10) : buckets(bucketCount) {}

  // 插入键值对
  void insert(const K &key, const V &value) {
    size_t index = hashFunction(key) % buckets.size();
    auto &bucket = buckets[index];

    // 检查是否已经存在相同的键,如果是,则替换值
    auto it = std::find_if(
        bucket.begin(), bucket.end(),
        [&](const KeyValuePair<K, V> &pair) { return pair.key == key; });

    if (it != bucket.end()) {
      it->value = value;
    } else {
      bucket.push_back({key, value});
    }
  }

  // 查找键对应的值
  bool find(const K &key, V &value) const {
    size_t index = hashFunction(key) % buckets.size();
    const auto &bucket = buckets[index];

    auto it = std::find_if(
        bucket.begin(), bucket.end(),
        [&](const KeyValuePair<K, V> &pair) { return pair.key == key; });

    if (it != bucket.end()) {
      value = it->value;
      return true;
    }

    return false;
  }

  // 删除键值对
  void remove(const K &key) {
    size_t index = hashFunction(key) % buckets.size();
    auto &bucket = buckets[index];

    bucket.remove_if(
        [&](const KeyValuePair<K, V> &pair) { return pair.key == key; });
  }
};

int main() {
  HashMap<std::string, int> myMap;

  myMap.insert("one", 1);
  myMap.insert("two", 2);
  myMap.insert("three", 3);

  int value;

  if (myMap.find("two", value)) {
    std::cout << "Value for key 'two': " << value << std::endl;
  } else {
    std::cout << "Key 'two' not found." << std::endl;
  }

  myMap.remove("two");

  if (myMap.find("two", value)) {
    std::cout << "Value for key 'two': " << value << std::endl;
  } else {
    std::cout << "Key 'two' not found." << std::endl;
  }

  return 0;
}
