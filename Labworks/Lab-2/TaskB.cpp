/*
!-STILL IN PROGRESS-!
*/
#include <iostream>

void Swap(int* a, int* b) {
  int t = *a;
  *a = *b;
  *b = t;
}

int Partition(int* arr, int left, int right) {
  int pivot = arr[(left + right) / 2];
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

  int listen[100000];

  for (int i = 0; i < n; i++) {
    std::cin >> listen[i];
  }

  QuickSort(listen, 0, n - 1);

  for (int i = 0; i < n; i++) {
    std::cout << listen[i] << " ";
  }
}