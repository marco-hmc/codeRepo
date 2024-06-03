#include <iostream>
#include <queue>
#include <stack>

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

// 先序遍历
vector<int> preorderTraversal2(TreeNode *root) {
  vector<int> result;
  stack<TreeNode *> stk;
  if (root != nullptr)
    stk.push(root);

  while (!stk.empty()) {
    TreeNode *node = stk.top();
    stk.pop();

    if (node != nullptr) {
      result.push_back(node->val);
      if (node->right)
        stk.push(node->right);
      if (node->left)
        stk.push(node->left);
    }
  }

  return result;
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

// 中序遍历
vector<int> inorderTraversal2(TreeNode *root) {
  vector<int> result;
  stack<TreeNode *> stk;
  TreeNode *curr = root;

  while (!curr || !stk.empty()) {
    while (!curr) {
      stk.push(curr);
      curr = curr->left;
    }

    curr = stk.top();
    stk.pop();
    result.push_back(curr->val);
    curr = curr->right;
  }

  return result;
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

// 后序遍历
vector<int> postorderTraversal2(TreeNode *root) {
  vector<int> result;
  stack<TreeNode *> stk;
  if (root != nullptr)
    stk.push(root);

  while (!stk.empty()) {
    TreeNode *node = stk.top();
    stk.pop();

    if (node != nullptr) {
      result.insert(result.begin(), node->val);
      if (node->left)
        stk.push(node->left);
      if (node->right)
        stk.push(node->right);
    }
  }
  return result;
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