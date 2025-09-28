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
  int mem, j;
  for (int i = 1; i < n; i++) {
    mem = arr[i];
    for (j = i; j >= 0; j--) {
      if (j > 0 && mem < arr[j - 1]) {
        arr[j] = arr[j - 1];
      } else {
        arr[j] = mem;
        break;
      }
      // if (j == 0 || mem > arr[j - 1])
      // {
      //     arr[j] = mem;
      //     break;
      // }
      // arr[j] = arr[j - 1];
    }
  }

  // output
  for (int i = 0; i < n; i++) {
    std::cout << arr[i] << " ";
  }
}