#include <iostream>
#include <string>
#include <vector>

using namespace std;

void dfs(vector<string> &ret, string &str, int open, int close) {
  if (open == 0 && close == 0) {
    ret.push_back(str);
    return;
  }
  if (open > 0) {
    str.push_back('(');
    dfs(ret, str, open - 1, close);
    str.pop_back();
  }
  if (close > open) {
    str.push_back(')');
    dfs(ret, str, open, close - 1);
    str.pop_back();
  }
}

vector<string> generateParenthesis(int n) {
  if (n <= 0)
    return {};
  vector<string> ret;
  string tmp = string("");
  dfs(ret, tmp, n, n);
  return ret;
}

int main() {
  int n = 3; // Replace with desired value
  vector<string> result = generateParenthesis(n);
  for (const string &str : result) {
    cout << str << endl;
  }
  return 0;
}