#include <algorithm>
#include <iostream>
#include <vector>

// B+树节点的定义
class BPlusTreeNode {
public:
  bool isLeaf;                           // 是否为叶子节点
  std::vector<int> keys;                 // 节点的关键字
  std::vector<BPlusTreeNode *> children; // 子节点指针

  BPlusTreeNode(bool leaf = false) : isLeaf(leaf) {}
};

// B+树的定义
class BPlusTree {
public:
  BPlusTreeNode *root; // 根节点

  BPlusTree() { root = nullptr; }

  // 插入关键字
  void insert(int key) {
    if (root == nullptr) {
      root = new BPlusTreeNode(true);
      root->keys.push_back(key);
    } else {
      BPlusTreeNode *node = root;
      while (!node->isLeaf) {
        int i = 0;
        while (i < node->keys.size() && key > node->keys[i]) {
          i++;
        }
        node = node->children[i];
      }
      node->keys.push_back(key);
      std::sort(node->keys.begin(), node->keys.end());
    }
  }

  // 遍历B+树
  void traverse() { traverseNode(root); }

private:
  // 遍历节点
  void traverseNode(BPlusTreeNode *node) {
    if (node != nullptr) {
      for (int i = 0; i < node->keys.size(); i++) {
        std::cout << node->keys[i] << " ";
      }
      std::cout << std::endl;

      if (!node->isLeaf) {
        for (int i = 0; i < node->children.size(); i++) {
          traverseNode(node->children[i]);
        }
      }
    }
  }
};

int main() {
  BPlusTree bPlusTree;

  // 插入关键字
  bPlusTree.insert(10);
  bPlusTree.insert(20);
  bPlusTree.insert(5);
  bPlusTree.insert(15);
  bPlusTree.insert(25);

  // 遍历B+树
  bPlusTree.traverse();

  return 0;
}