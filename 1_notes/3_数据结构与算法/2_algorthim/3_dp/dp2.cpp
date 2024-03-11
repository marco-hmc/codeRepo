#include <iostream>
#include <vector>

using namespace std;

int knapsack(int capacity, vector<int> &weights, vector<int> &values) {
  int n = weights.size();
  vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= capacity; j++) {
      if (weights[i - 1] <= j) {
        dp[i][j] =
            max(dp[i - 1][j], dp[i - 1][j - weights[i - 1]] + values[i - 1]);
      } else {
        dp[i][j] = dp[i - 1][j];
      }
    }
  }

  return dp[n][capacity];
}

int main() {
  int capacity = 10;
  vector<int> weights = {2, 3, 4, 5};
  vector<int> values = {3, 4, 5, 6};

  int max_value = knapsack(capacity, weights, values);
  cout << "The maximum value that can be obtained is: " << max_value << endl;

  return 0;
}
