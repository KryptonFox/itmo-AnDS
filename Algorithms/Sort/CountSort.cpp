#include <iostream>

const int kMaxKey = 10;
const int kCountArrLen = kMaxKey + 1;

int* CountSort(int* arr, int n) {
  int* c = new int[kCountArrLen];
  for (int i = 0; i < kCountArrLen; i++) c[i] = 0;

  for (int i = 0; i < n; i++) {
    c[arr[i]] += 1;
  }

  for (int i = 1; i < kCountArrLen; i++) c[i] += c[i - 1];

  int* sorted = new int[n + 1];
  for (int i = n - 1; i >= 0; i--) {
    sorted[c[arr[i]]] = arr[i];
    --c[arr[i]];
  }

  return sorted + 1;
}

int main() {
  int n;
  std::cin >> n;

  int* arr = new int[n];
  for (int i = 0; i < n; i++) std::cin >> arr[i];

  int* sorted = CountSort(arr, n);

  for (int i = 0; i < n; i++) std::cout << sorted[i] << " ";
}