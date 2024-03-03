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
    vector<vector<int>> levelorderTraversal(TreeNode* root){
        // 左中右
        queue<TreeNode*> q;
        if(root == nullptr) return{};
        q.push(root);
        vector<vector<int>> ret;
        while(!q.empty()){
            int n = q.size();
            vector<int> v;
            for (int i = 0; i < n; i++) {
                TreeNode* tmp = q.front();
                q.pop();
                v.push_back(tmp->val);
                if(tmp->left)
                    q.push(tmp->left);
                if(tmp->right)
                    q.push(tmp->right);
            }
            ret.push_back(v);
        }
        return ret;
    }
};

int main() {
    return 0;
}