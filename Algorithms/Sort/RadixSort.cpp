#include <iostream>

const int kMaxKey = 9;
const int kCountArrLen = kMaxKey + 1;

int Pow(int n, int power) {
  int r = 1;
  for (int i = 0; i < power; i++) r *= n;
  return r;
}

int Digit(int n, int k) { return (n / Pow(10, k)) % 10; }

int* CountSort(int* arr, int n, int k) {
  int c[kCountArrLen];
  for (int i = 0; i < kCountArrLen; i++) {
    c[i] = 0;
  };

  for (int i = 0; i < n; i++) {
    c[Digit(arr[i], k)]++;
  }

  for (int i = 1; i < kCountArrLen; i++) {
    c[i] += c[i - 1];
  };

  int* sorted = new int[n];
  for (int i = n - 1; i >= 0; i--) {
    int d = Digit(arr[i], k);
    sorted[c[d] - 1] = arr[i];
    --c[d];
  }

  return sorted;
}

int* RadixSort(int* arr, int n, int k) {
  int* t;
  for (int i = 0; i < k; i++) {
    t = CountSort(arr, n, i);
    delete[] arr;
    arr = t;
  }
  return arr;
}

int main() {
  int n;
  std::cin >> n;

  int* arr = new int[n];
  for (int i = 0; i < n; i++) std::cin >> arr[i];

  int* sorted = RadixSort(arr, n, 3);

  for (int i = 0; i < n; i++) std::cout << sorted[i] << " ";

  delete[] sorted;
}