#include <functional>
#include <iostream>
#include <map>
#include <string>


// Hash function for consistent hashing
typedef std::function<size_t(const std::string &)> HashFunction;

// Consistent Hashing class
class ConsistentHashing {
public:
  ConsistentHashing(const HashFunction &hashFunction)
      : hashFunction(hashFunction) {}

  // Add a node to the hash ring
  void addNode(const std::string &node) {
    size_t hash = hashFunction(node);
    ring[hash] = node;
  }

  // Remove a node from the hash ring
  void removeNode(const std::string &node) {
    size_t hash = hashFunction(node);
    ring.erase(hash);
  }

  // Get the node responsible for a given key
  std::string getNode(const std::string &key) {
    size_t hash = hashFunction(key);
    auto it = ring.lower_bound(hash);
    if (it == ring.end()) {
      it = ring.begin();
    }
    return it->second;
  }

private:
  std::map<size_t, std::string> ring;
  HashFunction hashFunction;
};

// Example usage
int main() {
  // Define a hash function
  HashFunction hashFunction = std::hash<std::string>();

  // Create a ConsistentHashing object
  ConsistentHashing ch(hashFunction);

  // Add nodes to the hash ring
  ch.addNode("Node1");
  ch.addNode("Node2");
  ch.addNode("Node3");

  // Get the node responsible for a given key
  std::string key = "Key1";
  std::string node = ch.getNode(key);
  std::cout << "Node responsible for key " << key << ": " << node << std::endl;

  return 0;
}