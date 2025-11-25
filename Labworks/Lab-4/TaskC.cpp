#include<iostream>

int Max(int a, int b) { return a > b ? a : b; }

int main() {
    int n;
    std::cin >> n;

    int* a = new int[n + 1];
    for (int i = 1; i <= n;++i) {
        std::cin >> a[i];
    }

    int m;
    std::cin >> m; 

    int* b = new int[m + 1];
    for (int i = 1; i <= m;++i) {
        std::cin >> b[i];
    }

    int** dp = new int*[n + 1];
    for (int i = 0; i <= n; ++i) {
        dp[i] = new int[m + 1];
        for (int j = 0; j <= m; ++j) {
            dp[i][j] = 0;
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (a[i] == b[j]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else {
                dp[i][j] = Max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    std::cout << dp[n][m];

    delete[] a;
    delete[] b;
    for (int i = 0; i <= n; ++i) {
        delete[] dp[i];
    }
    delete[] dp;
}