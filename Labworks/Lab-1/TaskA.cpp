#include <iostream>

int main() {
  int n;
  std::cin >> n;

  int arr[n];

  for (int i = 0; i < n; i++) {
    std::cin >> arr[i];
  }

  int peak_count = 0;

  for (int i = 1; i < n - 1; i++) {
    if (arr[i] > arr[i - 1] && arr[i] > arr[i + 1]) {
      peak_count++;
    }
  }

  std::cout << peak_count;
}
