#include <bits/stdc++.h>

#include <cstdint>
#include <cstdlib>
using namespace std;

uint32_t cur = 0;  // беззнаковое 32-битное число

// Генератор 24-битного числа
uint32_t nextRand24(uint32_t a, uint32_t b) {
  cur = cur * a + b;  // вычисляется с переполнениями по модулю 2^32
  return cur >> 8;    // число от 0 до 2^24 - 1
}

// Генератор 32-битного числа на основе двух 24-битных
uint32_t nextRand32(uint32_t a, uint32_t b) {
  uint32_t x = nextRand24(a, b);
  uint32_t y = nextRand24(a, b);
  return (x << 8) ^ y;  // число от 0 до 2^32 - 1
}

void Swap(uint32_t* a, uint32_t* b) {
  uint32_t t = *a;
  *a = *b;
  *b = t;
}

uint32_t Median(uint32_t& a, uint32_t& b, uint32_t& c) {
  if ((a >= b && a <= c) || (a > c && a < b)) return a;
  if ((b >= a && b <= c) || (b > c && b < a)) return b;
  return c;
}

int Partition(uint32_t* arr, uint32_t left, uint32_t right) {
  uint32_t pivot = Median(arr[left], arr[(left + right) / 2], arr[right]);
  uint32_t i = left;
  uint32_t j = right;

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

uint32_t QuickSelect(uint32_t* arr, uint32_t k, uint32_t left, uint32_t right) {
  if (left >= right) return arr[left];
  uint32_t q = Partition(arr, left, right);

  if (k <= q) {
    return QuickSelect(arr, k, left, q);
  } else {
    return QuickSelect(arr, k, q + 1, right);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  uint32_t n, a, b;
  cin >> n >> a >> b;

  uint32_t arr[n];

  for (uint32_t i = 0; i < n; i++) {
    arr[i] = nextRand32(a, b);  // генерируем i-й элемент
  }

  uint32_t median;
  if (n % 2) {
    median = QuickSelect(arr, n / 2, 0, n - 1);
  } else {
    median = (static_cast<uint64_t>(QuickSelect(arr, n / 2, 0, n - 1)) +
              QuickSelect(arr, n / 2 - 1, 0, n - 1)) /
             2;
  }

  uint64_t min_sum_dist = 0;
  for (int i = 0; i < n; i++) {
    min_sum_dist += arr[i] > median ? arr[i] - median : median - arr[i];
  }

  std::cout << min_sum_dist;
}