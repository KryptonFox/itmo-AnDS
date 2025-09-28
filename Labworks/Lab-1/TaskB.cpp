#include <iostream>

int abs(int a) {
  if (a < 0) {
    return -a;
  } else {
    return a;
  }
}

int main() {
  int n;
  std::cin >> n;

  int darkstores_distance[n];

  for (int i = 0; i < n; i++) {
    std::cin >> darkstores_distance[i];
  }

  int x;
  std::cin >> x;

  int min_delta = 10000;
  int delta, nearest_darkstore;

  for (int i = 0; i < n; i++) {
    delta = abs(x - darkstores_distance[i]);
    if (delta < min_delta) {
      min_delta = delta;
      nearest_darkstore = darkstores_distance[i];
    }
  }

  std::cout << nearest_darkstore;
}