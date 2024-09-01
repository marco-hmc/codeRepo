#include <cstdlib>
#include <cstring>
#include <iostream>

const int MAX_LEVEL = 6;

// Node class for skip list
class Node {
public:
  int value;
  Node **forward;

  Node(int level, int value) {
    this->value = value;
    forward = new Node *[level + 1];
    memset(forward, 0, sizeof(Node *) * (level + 1));
  }

  ~Node() { delete[] forward; }
};

// SkipList class
class SkipList {
private:
  Node *header;
  int level;

public:
  SkipList() {
    header = new Node(MAX_LEVEL, 0);
    level = 0;
  }

  ~SkipList() { delete header; }

  // Generate random level for a node
  int randomLevel() {
    int level = 0;
    while (rand() < RAND_MAX / 2 && level < MAX_LEVEL) {
      level++;
    }
    return level;
  }

  // Insert a value into the skip list
  void insert(int value) {
    Node *current = header;
    Node *update[MAX_LEVEL + 1];
    memset(update, 0, sizeof(Node *) * (MAX_LEVEL + 1));

    // Find the right position to insert
    for (int i = level; i >= 0; i--) {
      while (current->forward[i] != nullptr &&
             current->forward[i]->value < value) {
        current = current->forward[i];
      }
      update[i] = current;
    }

    current = current->forward[0];

    // If the value already exists, return
    if (current == nullptr || current->value != value) {
      int newLevel = randomLevel();

      // If new level is greater than current level, update the update array
      if (newLevel > level) {
        for (int i = level + 1; i <= newLevel; i++) {
          update[i] = header;
        }
        level = newLevel;
      }

      // Create a new node with random level
      Node *newNode = new Node(newLevel, value);

      // Insert the node
      for (int i = 0; i <= newLevel; i++) {
        newNode->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = newNode;
      }
    }
  }

  // Search for a value in the skip list
  bool search(int value) {
    Node *current = header;

    // Traverse the skip list
    for (int i = level; i >= 0; i--) {
      while (current->forward[i] != nullptr &&
             current->forward[i]->value < value) {
        current = current->forward[i];
      }
    }

    current = current->forward[0];

    // If the value is found, return true
    if (current != nullptr && current->value == value) {
      return true;
    }

    // If the value is not found, return false
    return false;
  }

  // Print the skip list
  void print() {
    std::cout << "Skip List:" << '\n';
    for (int i = 0; i <= level; i++) {
      Node *current = header->forward[i];
      std::cout << "Level " << i << ": ";
      while (current != nullptr) {
        std::cout << current->value << " ";
        current = current->forward[i];
      }
      std::cout << '\n';
    }
  }
};

int main() {
  // Create a skip list object
  SkipList skipList;

  // Insert values into the skip list
  skipList.insert(3);
  skipList.insert(6);
  skipList.insert(2);
  skipList.insert(9);
  skipList.insert(1);

  // Print the skip list
  skipList.print();

  // Search for a value in the skip list
  int value = 6;
  if (skipList.search(value)) {
    std::cout << "Value " << value << " found in the skip list." << '\n';
  } else {
    std::cout << "Value " << value << " not found in the skip list." << '\n';
  }

  return 0;
}
