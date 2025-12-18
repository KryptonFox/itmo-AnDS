#include <iostream>
#include <cstdint>


bool CanPlaceNodes(const int64_t* positions, int n, int k, int64_t dist) {
  int count = 1;
  int64_t last = positions[0];

  for (int i = 1; i < n; ++i) {
    if (positions[i] - last >= dist) {
      ++count;
      last = positions[i];
      if (count >= k) return true;
    }
  }
  return count >= k;
}

int64_t MaxMinDistance(int64_t* positions, int n, int k) {
  int64_t left = 0;
  int64_t right = positions[n - 1] - positions[0];
  int64_t answer = 0;

  while (left <= right) {
    int64_t mid = left + (right - left) / 2;
    if (CanPlaceNodes(positions, n, k, mid)) {
      answer = mid;
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  return answer;
}

int main() {
  int n, k;
  std::cin >> n >> k;

  int64_t* positions = new int64_t[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> positions[i];
  }

  int64_t result = MaxMinDistance(positions, n, k);
  std::cout << result;

  delete[] positions;
}
