class Solution {
public:
  int strStr(string target, string pattern) {
    if (pattern.empty())
      return 0;
    if (target.size() < pattern.size())
      return -1;
    vector<int> next(pattern.size(), 0);
    findNext(pattern, next);
    int i = 0, j = 0, tlen = target.size(), plen = pattern.size();
    while (i < tlen && j < plen) {
      if (j == -1 || target[i] == pattern[j]) {
        i++;
        j++;
      } else {
        j = next[j];
      }
    }
    if (j >= plen) {
      return i - plen;
    }
    return -1;
  }

  void findNext(string &str, vector<int> &next) {
    next[0] = -1;
    int i = 0, k = -1;
    int len = str.size();
    while (i < len - 1) {
      if (k == -1 || str[i] == str[k]) {
        i++;
        k++;
        if (str[i] != str[k]) {
          next[i] = k;
        } else {
          next[i] = next[k];
        }
      } else {
        k = next[k];
      }
    }
  }
};
