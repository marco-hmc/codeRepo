// N个骰子出现和为m的概率
#include <cmath>
#include <iostream>
#include <vector>

double probability(int N, int m) {
  std::vector<std::vector<int>> dp(N + 1, std::vector<int>(6 * N + 1, 0));

  // 初始化dp数组
  for (int i = 1; i <= 6; i++) {
    dp[1][i] = 1;
  }

  // 计算dp数组的其他值
  for (int i = 2; i <= N; i++) {
    for (int j = i; j <= 6 * i; j++) {
      for (int k = 1; k <= 6; k++) {
        if (j - k >= i - 1) {
          dp[i][j] += dp[i - 1][j - k];
        }
      }
    }
  }

  // 计算概率
  double total = pow(6, N);
  double p = dp[N][m] / total;

  return p;
}

int main() {
  int N, m;
  std::cout << "请输入骰子的个数N:";
  std::cin >> N;
  std::cout << "请输入和的值m:";
  std::cin >> m;

  double p = probability(N, m);
  std::cout << "N个骰子出现和为m的概率为:" << p << std::endl;

  return 0;
}
