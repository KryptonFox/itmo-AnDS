#include <iomanip>
#include <ios>
#include <iostream>

double Max(double a, double b) { return a > b ? a : b; }

int main() {
  int n, W;
  std::cin >> n >> W;

  int *weight = new int[n + 1];
  double *value = new double[n + 1];
  for (int i = 1; i <= n; ++i) {
    std::cin >> weight[i] >> value[i];
  }

  double **dp = new double *[n + 2];
  double **dp_i = new double *[n + 2];
  for (int i = 0; i <= n + 1; ++i) {
    dp[i] = new double[W + 1];
    dp_i[i] = new double[W + 1];
    for (int j = 0; j <= W; ++j) {
      dp[i][j] = 0.;
      dp_i[i][j] = 0.;
    }
  }

  for (int i = 1; i <= n; ++i) {
    for (int w = 0; w <= W; ++w) {
      dp[i][w] = dp[i - 1][w];
      if (weight[i] <= w) {
        dp[i][w] = Max(dp[i - 1][w], dp[i - 1][w - weight[i]] + value[i]);
      }
    }
  }

  for (int i = n; i > 0; --i) {
    for (int w = 0; w <= W; ++w) {
      dp_i[i][w] = dp_i[i + 1][w];
      if (weight[i] <= w) {
        dp_i[i][w] = Max(dp_i[i + 1][w], dp_i[i + 1][w - weight[i]] + value[i]);
      }
    }
  }

  for (int i = 1; i <= n; ++i) {
    double res = 0;
    for (int w = 0; w <= W; ++w) {
      res = Max(res, dp[i - 1][w] + dp_i[i + 1][W - w]);
    }
    std::cout << std::fixed << std::setprecision(9) << res << "\n";
  }

  delete[] weight;
  delete[] value;
  delete[] dp;
  delete[] dp_i;
}
