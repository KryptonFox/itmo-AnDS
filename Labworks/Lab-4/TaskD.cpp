#include <iostream>

int Max(int a, int b) { return a > b ? a : b; }

int main() {
  int W, n;
  std::cin >> W >> n;
  int *dp = new int[W + 1];
  for (int i = 0; i <= W; ++i) {
    dp[i] = 0;
  }

  int *weights = new int[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> weights[i];
  }

  for (int i = 0; i < n; ++i) {
    for (int w = W; w >= 0; --w) {
      if (weights[i] <= w) {
        dp[w] = Max(dp[w], dp[w - weights[i]] + weights[i]);
      }
    }
  }

  std::cout << dp[W];

  delete[] dp;
  delete[] weights;
}
