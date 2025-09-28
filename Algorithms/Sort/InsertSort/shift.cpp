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
  int key, j;
  for (int i = 1; i < n; i++) {
    key = arr[i];
    j = i - 1;
    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = key;
  }

  // output
  for (int i = 0; i < n; i++) {
    std::cout << arr[i] << " ";
  }
}