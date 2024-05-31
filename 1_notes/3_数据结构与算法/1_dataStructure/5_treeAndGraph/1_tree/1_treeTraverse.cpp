#include <iostream>
#include <queue>

using namespace std;

// 树节点的定义
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// 先序遍历
void preorderTraversal(TreeNode *root) {
  if (root == nullptr) {
    return;
  }
  cout << root->val << " ";
  preorderTraversal(root->left);
  preorderTraversal(root->right);
}

// 中序遍历
void inorderTraversal(TreeNode *root) {
  if (root == nullptr) {
    return;
  }
  inorderTraversal(root->left);
  cout << root->val << " ";
  inorderTraversal(root->right);
}

// 后序遍历
void postorderTraversal(TreeNode *root) {
  if (root == nullptr) {
    return;
  }
  postorderTraversal(root->left);
  postorderTraversal(root->right);
  cout << root->val << " ";
}

// 层序遍历
void levelOrderTraversal(TreeNode *root) {
  if (root == nullptr) {
    return;
  }
  queue<TreeNode *> q;
  q.push(root);
  while (!q.empty()) {
    TreeNode *node = q.front();
    q.pop();
    cout << node->val << " ";
    if (node->left != nullptr) {
      q.push(node->left);
    }
    if (node->right != nullptr) {
      q.push(node->right);
    }
  }
}

int main() {

  // 创建一个示例树
  //     1
  //    / \
  //   2   3
  //  / \ / \
  // 4  5 6  7
  TreeNode *root = new TreeNode(1);
  root->left = new TreeNode(2);
  root->right = new TreeNode(3);
  root->left->left = new TreeNode(4);
  root->left->right = new TreeNode(5);
  root->right->left = new TreeNode(6);
  root->right->right = new TreeNode(7);

  // 先序遍历
  // 1 2 4 5 3 6 7
  cout << "Preorder traversal: ";
  preorderTraversal(root);
  cout << endl;

  // 中序遍历
  // 4 2 5 1 6 3 7
  cout << "Inorder traversal: ";
  inorderTraversal(root);
  cout << endl;

  // 后序遍历
  // 4 5 2 6 7 3 1
  cout << "Postorder traversal: ";
  postorderTraversal(root);
  cout << endl;

  // 层序遍历
  // 1 2 3 4 5 6 7
  cout << "Level order traversal: ";
  levelOrderTraversal(root);
  cout << endl;

  return 0;
}