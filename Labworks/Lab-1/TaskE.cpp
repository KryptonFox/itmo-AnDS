#include <iostream>

int main() {
  int n;
  std::cin >> n;

  // input
  int schedule[n];
  for (int i = 0; i < n; i++) {
    std::cin >> schedule[i];
  }

  // schedule shift
  int new_schedule[n];
  new_schedule[0] = schedule[n - 1];
  for (int i = 1; i < n; i++) {
    new_schedule[i] = schedule[i - 1];
  }

  // output
  for (int i = 0; i < n - 1; i++) {
    std::cout << new_schedule[i] << " ";
  }
  std::cout << new_schedule[n - 1];
}