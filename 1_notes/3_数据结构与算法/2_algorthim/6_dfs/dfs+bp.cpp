// ## [括号生成](https://leetcode-cn.com/problems/generate-parentheses/)

// * 题目描述:数字 `n`
// 代表生成括号的对数,请你设计一个函数,用于能够生成所有可能的并且 **有效的**
// 括号组合

// * 解题思路:如果左括号数量不大于
// n,我们可以放一个左括号.如果**右括号数量小于左括号的数量,我们可以放一个右括号**

// * 代码实现

//   ```c++
//   vector<string> generateParenthesis(int n) {
//       if(n <= 0)
//           return {};
//       vector<string> ret;
//       string tmp = string("");
//       dfs(ret, tmp, n, n);
//       return ret;
//   }

//   void dfs(vector<string> & ret, string &str, int open, int close)
//   {
//       if(open ==0 && close ==0) {
//           ret.push_back(str);
//           return;
//       }
//       if(open > 0) {
//           str.push_back('(');
//           dfs(ret, str, open-1, close);
//           str.pop_back();
//       }
//       if(close > open) {
//           str.push_back(')');
//           dfs(ret, str, open, close - 1);
//           str.pop_back();
//       }
//   }
//   ```