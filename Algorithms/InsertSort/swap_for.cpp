#include <iostream>

int main() {
  int n;
  std::cin >> n;

  // input
  int arr[n];
  for (int i = 0; i < n; i++) {
    std::cin >> arr[i];
  }

  // sort
  int swap, j;
  for (int i = 1; i < n; i++) {
    for (j = i; j > 0 && arr[j] < arr[j - 1]; j--) {
      // swap
      swap = arr[j];
      arr[j] = arr[j - 1];
      arr[j - 1] = swap;
    }
  }

  // output
  for (int i = 0; i < n; i++) {
    std::cout << arr[i] << " ";
  }
}