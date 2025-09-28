#include <iostream>

bool CompareAndCount(int &a, int &b, int &count) {
  count++;
  return a < b;
}

int main() {
  int n;
  std::cin >> n;

  int likes[n];
  for (int i = 0; i < n; i++) {
    std::cin >> likes[i];
  }

  int j, key, count = 0;
  for (int i = 1; i < n; i++) {
    j = i - 1;
    key = likes[i];
    while (j >= 0 && CompareAndCount(key, likes[j], count)) {
      likes[j + 1] = likes[j];
      j--;
    }
    likes[j + 1] = key;
  }

  std::cout << count;
}