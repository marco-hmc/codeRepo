#include <iostream>
#include <vector>

// B+树的节点结构
struct Node {
    std::vector<int> keys;
    std::vector<Node*> children;
};

// B+树的类
class BPlusTree {
private:
    Node* root;

public:
    BPlusTree() {
        root = nullptr;
    }

    void insert(int key) {
        if (root == nullptr) {
            root = new Node();
            root->keys.push_back(key);
        }
        else {
            insertHelper(root, key);
        }
    }

    void insertHelper(Node* node, int key) {
        if (node->children.empty()) {
            // 叶子节点，直接插入
            insertKey(node, key);
        }
        else {
            // 非叶子节点，找到合适的子节点递归插入
            int index = findChildIndex(node, key);
            insertHelper(node->children[index], key);
        }
    }

    void insertKey(Node* node, int key) {
        // 在合适的位置插入键值
        int index = 0;
        while (index < node->keys.size() && node->keys[index] < key) {
            index++;
        }
        node->keys.insert(node->keys.begin() + index, key);
    }

    int findChildIndex(Node* node, int key) {
        // 找到合适的子节点索引
        int index = 0;
        while (index < node->keys.size() && node->keys[index] <= key) {
            index++;
        }
        return index;
    }

    int search(int key) {
        if (root == nullptr) {
            return -1;
        }
        else {
            return searchHelper(root, key);
        }
    }

    int searchHelper(Node* node, int key) {
        if (node->children.empty()) {
            // 叶子节点，线性查找键值
            for (int i = 0; i < node->keys.size(); i++) {
                if (node->keys[i] == key) {
                    return key;
                }
            }
            return -1;
        }
        else {
            // 非叶子节点，找到合适的子节点递归查找
            int index = findChildIndex(node, key);
            return searchHelper(node->children[index], key);
        }
    }

    void remove(int key) {
        if (root == nullptr) {
            return;
        }
        else {
            removeHelper(root, key);
        }
    }

    void removeHelper(Node* node, int key) {
        if (node->children.empty()) {
            // 叶子节点，直接删除键值
            removeKey(node, key);
        }
        else {
            // 非叶子节点，找到合适的子节点递归删除
            int index = findChildIndex(node, key);
            removeHelper(node->children[index], key);
        }
    }

    void removeKey(Node* node, int key) {
        // 在节点中删除键值
        int index = 0;
        while (index < node->keys.size() && node->keys[index] != key) {
            index++;
        }
        if (index < node->keys.size()) {
            node->keys.erase(node->keys.begin() + index);
        }
    }
};

int main() {
    BPlusTree tree;

    // 插入示例数据
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);

    // 查找示例数据
    int result = tree.search(20);
    if (result != -1) {
        std::cout << "Found: " << result << std::endl;
    }
    else {
        std::cout << "Not found" << std::endl;
    }

    // 删除示例数据
    tree.remove(20);

    return 0;
}
