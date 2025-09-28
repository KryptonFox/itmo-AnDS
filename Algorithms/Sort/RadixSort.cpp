#include <iostream>

const int kMaxKey = 9;
const int kCountArrLen = kMaxKey + 1;

int Key(int n, int k) { return k > 0 ? (n / (10 * k)) % 10 : n % 10; }

int* CountSort(int* arr, int n, int k) {
  int* c = new int[kCountArrLen];
  for (int i = 0; i < kCountArrLen; i++) c[i] = 0;

  for (int i = 0; i < n; i++) {
    c[Key(arr[i], k)] += 1;
  }

  for (int i = 1; i < kCountArrLen; i++) c[i] += c[i - 1];

  int* sorted = new int[n + 1];
  for (int i = n - 1; i >= 0; i--) {
    sorted[c[Key(arr[i], k)]] = arr[i];
    --c[Key(arr[i], k)];
  }

  return sorted + 1;
}

int* RadixSort(int* arr, int n, int k) {
  for (int i = k; i > 0; i--) {
    arr = CountSort(arr, n, k - i);
    for (int i = 0; i < n; i++) std::cout << arr[i] << " ";
    std::cout << std::endl;
  }
  return arr;
}

int main() {
  int n;
  std::cin >> n;

  int* arr = new int[n];
  for (int i = 0; i < n; i++) std::cin >> arr[i];

  int* sorted = RadixSort(arr, n, 5);

  for (int i = 0; i < n; i++) std::cout << sorted[i] << " ";
}