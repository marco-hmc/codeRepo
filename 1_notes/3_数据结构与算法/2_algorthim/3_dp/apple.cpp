//  分苹果

// 题目描述:把m个同样的苹果放在n个同样的盘子里,允许有的盘子空着不放,问共有多少种不同的分法?
// 5,1,1和1,5,1 是同一种分法

// 思路:$dp[n][m]$为$n$个盘子$m$个苹果总摆放数,$dp[i][j]$为$i$个盘子$j$个苹果的摆放数,则有

//  如果$i>j$则,必有一个以上是空盘,其摆放方式相当于将$m$个苹果放入$i-1$个盘子,所以
//  $dp[i][j]  = dp[i-1][j]$
//     * 如果$i\le j$则,有两种情况:
//     * 如果有一个以上空盘,$dp[i][j] = dp[i-1][j]$;
//     * 若每个盘子都摆有一个苹果,摆放数为相当于将剩余$j-i$个苹果摆放到$i$个盘子中
//     * 摆放总数为上面两种情况的和:$dp[i][j] = dp[i-1][j] + dp[i][j-i]$

// * 边界条件,只有一个苹果或0个苹果时,摆放数为1

#include <iostream>
#include <vector>

int putApples(int n, int m) {
  if (n < 0 || m < 0)
    return 0;
  std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));

  for (int i = 0; i <= n; i++)
    dp[i][0] = dp[i][1] = 1;

  for (int i = 1; i <= n; i++) {
    for (int j = 2; j <= m; j++) {
      dp[i][j] = dp[i - 1][j];
      if (j >= i)
        dp[i][j] += dp[i][j - i];
    }
  }
  return dp[n][m];
}

int main() {
  int n = 3; // Number of plates
  int m = 5; // Number of apples

  int result = putApples(n, m);
  std::cout << "Number of different ways to distribute " << m
            << " apples among " << n << " plates: " << result << std::endl;

  return 0;
}
