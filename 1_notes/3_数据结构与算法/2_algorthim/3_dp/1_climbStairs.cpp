#include <iostream>
#include <string>

class Solution {
public:
  int solution_1(int n) {
    int len = fmax(3, n);
    int dp[len + 1];
    dp[0] = 0;
    dp[1] = 1;
    dp[2] = 2;
    for (int i = 3; i < n; i++) {
      dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
  }

  void test() {
    std::cout << "Testing solution " << solution_1(2) << std::endl;
    std::cout << "Testing solution " << solution_1(3) << std::endl;
    std::cout << "Testing solution " << solution_1(4) << std::endl;
  }
};

int main() {
  while (1) {
    std::string str;
    getline(std::cin, str, '\n');
    if (str == "")
      break;
    int n = atoi(str.c_str());
    Solution s;
    s.test();
  }
}