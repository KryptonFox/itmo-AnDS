#include <iostream>

int main() {
  char tags[101];

  for (int i = 0; i < 100; i++) {
    tags[i] = 0;
  }

  std::cin >> tags;

  char max_priority_tag = 0;

  for (int i = 0; i < 100; i++) {
    if (tags[i] > max_priority_tag) {
      max_priority_tag = tags[i];
    }
  }

  std::cout << max_priority_tag;
}