#include <iostream>

int main() {
  int n;
  std::cin >> n;

  int drones_id[n];

  for (int i = 0; i < n; i++) {
    std::cin >> drones_id[i];
  }

  int for_revision[2] = {2000000001, 2000000002};

  for (int i = 0; i < n; i++) {
    if (drones_id[i] < for_revision[1]) {
      if (drones_id[i] <= for_revision[0]) {
        for_revision[1] = for_revision[0];
        for_revision[0] = drones_id[i];
      } else {
        for_revision[1] = drones_id[i];
      }
    }
  }

  std::cout << for_revision[0] << " " << for_revision[1];
}