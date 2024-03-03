#include <bits/stdc++.h>
using namespace std;

struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val) : val(val), left(nullptr), right(nullptr){}
    TreeNode(int val, TreeNode*left, TreeNode*right) : val(val), left(left), right(right){}
};

class Solution{
public:
    vector<int> inorderTraversal(TreeNode* root){
        // 左中右
        vector<int> ret;
        stack<TreeNode*> st;
        TreeNode* cur = root;
        while (cur != nullptr || !st.empty()) {
            if(cur != nullptr){
                st.push(cur);
                cur = cur->left;
            }else{
                cur = st.top();
                st.pop();
                ret.push_back(cur->val);
                cur = cur->right;
            }
        }
        return ret;
    }
};

int main() {
    return 0;
}