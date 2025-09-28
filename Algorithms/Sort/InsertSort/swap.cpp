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
    j = i;
    while (j > 0 && arr[j] < arr[j - 1]) {
      // swap
      swap = arr[j];
      arr[j] = arr[j - 1];
      arr[j - 1] = swap;

      j--;
    }
  }

  // output
  for (int i = 0; i < n; i++) {
    std::cout << arr[i] << " ";
  }
}