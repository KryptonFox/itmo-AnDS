#include <algorithm>
#include <iostream>

int main() {
  int n;
  std::cin >> n;

  int *a = new int[n];
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  int *max_s = new int[n + 2];
  max_s[0] = 0;
  max_s[1] = 0;

  int i = 0;

  while (i < n) {
    max_s[i + 2] = a[i] + std::max(max_s[i + 1], max_s[i]);
    ++i;
  }

  std::cout << max_s[i + 1];

  delete[] a;
  delete[] max_s;
}
