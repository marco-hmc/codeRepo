#include <iostream>
#include <list>
#include <unordered_map>

class LRUCache {
private:
  int capacity;
  std::list<int> cacheList;
  std::unordered_map<int, std::list<int>::iterator> cacheMap;

public:
  LRUCache(int capacity) { this->capacity = capacity; }

  int get(int key) {
    if (cacheMap.find(key) == cacheMap.end()) {
      return -1;
    }

    // Move the accessed key to the front of the cache list
    cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);

    return *cacheMap[key];
  }

  void put(int key, int value) {
    if (cacheMap.find(key) != cacheMap.end()) {
      // Key already exists, update its value and move it to the front
      cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
      *cacheMap[key] = value;
    } else {
      if (cacheList.size() == capacity) {
        // Cache is full, remove the least recently used key
        int leastRecent = cacheList.back();
        cacheList.pop_back();
        cacheMap.erase(leastRecent);
      }

      // Insert the new key-value pair at the front of the cache list
      cacheList.push_front(value);
      cacheMap[key] = cacheList.begin();
    }
  }
};

int main() {
  // Example usage
  LRUCache cache(2);
  cache.put(1, 1);
  cache.put(2, 2);
  std::cout << cache.get(1) << '\n'; // Output: 1
  cache.put(3, 3);
  std::cout << cache.get(2) << '\n'; // Output: -1
  cache.put(4, 4);
  std::cout << cache.get(1) << '\n'; // Output: -1
  std::cout << cache.get(3) << '\n'; // Output: 3
  std::cout << cache.get(4) << '\n'; // Output: 4

  return 0;
}
