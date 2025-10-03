#include <bits/stdc++.h>

#include <cstdint>
#include <iostream>

void MergeAndCountInversions(uint32_t* arr, uint64_t& inv_count, int left,
                             int mid, int right) {
  int it1 = 0;
  int it2 = 0;

  uint32_t* result = new uint32_t[right - left];

  while ((left + it1 < mid) && (mid + it2 < right)) {
    if (arr[left + it1] <= arr[mid + it2]) {
      result[it1 + it2] = arr[left + it1];
      it1++;
    } else {
      inv_count += mid - left - it1;
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

void MergeSortAndCountInversions(uint32_t* arr, uint64_t& inv_count, int left,
                                 int right) {
  if (left + 1 >= right) return;
  int mid = (left + right) / 2;

  MergeSortAndCountInversions(arr, inv_count, left, mid);
  MergeSortAndCountInversions(arr, inv_count, mid, right);
  MergeAndCountInversions(arr, inv_count, left, mid, right);
}

const int MAXN = 1'000'000;  // максимум n по условию
uint32_t arr[MAXN];

uint32_t cur = 0;  // текущее значение генератора

// Генератор 24-битных чисел по условию задачи
uint32_t nextRand24(uint32_t a, uint32_t b) {
  // 32-битные переполнения (uint32_t автоматически усекает до 2^32)
  cur = cur * a + b;
  return cur >> 8;  // берём старшие 24 бита (сдвиг вправо на 8)
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  uint32_t n, m, a, b;
  std::cin >> n >> m >> a >> b;

  // Генерируем n элементов
  for (uint32_t i = 0; i < n; i++) {
    // получаем 24-битное значение по модулю m
    uint32_t x = nextRand24(a, b) % m;
    arr[i] = x;  // записываем в массив
  }

  uint64_t inv_count = 0;

  MergeSortAndCountInversions(arr, inv_count, 0, n);

  std::cout << inv_count;
}