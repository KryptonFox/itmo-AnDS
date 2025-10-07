/*
!-STILL IN PROGRESS-!
TIME ISSUE :(
*/

#include <bits/stdc++.h>

#include <cstdint>
#include <iostream>

// беззнаковое 32-битное число
uint32_t cur = 0;

/// Генератор 24-битного числа
uint32_t nextRand24(uint32_t a, uint32_t b) {
  cur = cur * a + b;  // вычисляется с переполнениями по модулю 2^32
  return cur >> 8;    // число от 0 до 2^24 - 1
}

/// Генератор 32-битного числа на основе двух 24-битных
uint32_t nextRand32(uint32_t a, uint32_t b) {
  uint32_t x = nextRand24(a, b);
  uint32_t y = nextRand24(a, b);
  return (x << 8) ^ y;  // число от 0 до 2^32 - 1
}

// Сортируем по байтам
uint32_t Key(uint32_t n, uint32_t k) { return (n >> k * 8) & 0xFF; }

const int kCountArrLen = 256;

void CountSort(uint32_t* arr, uint32_t* sorted, uint32_t n, uint32_t k) {
  uint32_t c[kCountArrLen];
  for (int i = 0; i < kCountArrLen; i++) {
    c[i] = 0;
  };

  for (int i = 0; i < n; i++) {
    c[Key(arr[i], k)]++;
  }

  for (int i = 1; i < kCountArrLen; i++) {
    c[i] += c[i - 1];
  };

  for (int i = n - 1; i >= 0; i--) {
    uint32_t d = Key(arr[i], k);
    sorted[c[d] - 1] = arr[i];
    --c[d];
  }
}

void RadixSort(uint32_t* arr, uint32_t* sorted, uint32_t n, int k) {
  for (int i = 0; i < k; i++) {
    CountSort(arr, sorted, n, i);
    for (int i = 0; i < n; i++) {
      arr[i] = sorted[i];
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  uint32_t n, a, b;
  std::cin >> t >> n >> a >> b;

  uint32_t arr[n];
  uint32_t sorted[n];
  uint64_t sum;

  while (t--) {
    sum = 0;
    for (uint32_t i = 0; i < n; i++) {
      arr[i] = nextRand32(a, b);  // генерируем i-й элемент
    }

    RadixSort(arr, sorted, n, 4);

    for (int i = 0; i < n; i++) {
      sum += static_cast<uint64_t>(sorted[i]) * (i + 1);
    };

    std::cout << sum << "\n";
  }
}