#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits>
#include <vector>

struct Point {
  int x;
  int y;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector<Point> points(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> points[i].x >> points[i].y;
  }

  std::vector min_dist_sq(n, std::numeric_limits<int>::max());
  std::vector in_mst(n, false);
  double total_weight = 0.0;

  min_dist_sq[0] = 0;

  for (int i = 0; i < n; ++i) {
    int v = -1;
    for (int j = 0; j < n; ++j) {
      if (!in_mst[j] && (v == -1 || min_dist_sq[j] < min_dist_sq[v])) {
        v = j;
      }
    }

    in_mst[v] = true;
    total_weight += std::sqrt(min_dist_sq[v]);

    for (int j = 0; j < n; ++j) {
      if (!in_mst[j]) {
        int dx = points[v].x - points[j].x;
        int dy = points[v].y - points[j].y;
        int dist_sq = dx * dx + dy * dy;
        if (dist_sq < min_dist_sq[j]) {
          min_dist_sq[j] = dist_sq;
        }
      }
    }
  }

  std::cout << std::fixed << total_weight << std::endl;
}