#include <iostream>

void Swap(int* a, int* b) {
  int t = *a;
  *a = *b;
  *b = t;
}

int Median(int& a, int& b, int& c) {
  if ((a >= b && a <= c) || (a > c && a < b)) return a;
  if ((b >= a && b <= c) || (b > c && b < a)) return b;
  return c;
}

int Partition(int* arr, int left, int right) {
  int pivot = Median(arr[left], arr[(left + right) / 2], arr[right]);
  int i = left;
  int j = right;

  while (i <= j) {
    while (arr[i] < pivot) i++;
    while (arr[j] > pivot) j--;
    if (i >= j) break;

    Swap(&arr[i], &arr[j]);

    i++;
    j--;
  }

  return j;
}

void QuickSort(int* arr, int left, int right) {
  if (left >= right) return;
  int q = Partition(arr, left, right);

  QuickSort(arr, left, q);
  QuickSort(arr, q + 1, right);
}

int main() {
  int n;
  std::cin >> n;

  int* arr = new int[n];
  for (int i = 0; i < n; i++) std::cin >> arr[i];

  QuickSort(arr, 0, n - 1);

  for (int i = 0; i < n; i++) std::cout << arr[i] << " ";
  delete[] arr;
}