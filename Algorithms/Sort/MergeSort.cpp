#include <iostream>

void Merge(int* arr, int left, int mid, int right) {
  int it1 = 0;
  int it2 = 0;

  int* result = new int[right - left];

  while ((left + it1 < mid) && (mid + it2 < right)) {
    if (arr[left + it1] <= arr[mid + it2]) {
      result[it1 + it2] = arr[left + it1];
      it1++;
    } else {
      result[it1 + it2] = arr[mid + it2];
      it2++;
    }
  }

  while (left + it1 < mid) {
    result[it1 + it2] = arr[left + it1];
    it1++;
  }

  while (mid + it2 < right) {
    result[it1 + it2] = arr[mid + it2];
    it2++;
  }

  for (int i = 0; i < right - left; i++) {
    arr[left + i] = result[i];
  }

  delete[] result;
}

void MergeSort(int* arr, int left, int right) {
  if (left + 1 >= right) return;
  int mid = (left + right) / 2;

  MergeSort(arr, left, mid);
  MergeSort(arr, mid, right);
  Merge(arr, left, mid, right);
}

int main() {
  int n;
  std::cin >> n;

  int* arr = new int[n];
  for (int i = 0; i < n; i++) std::cin >> arr[i];

  MergeSort(arr, 0, n);

  for (int i = 0; i < n; i++) std::cout << arr[i] << " ";
  delete[] arr;
}