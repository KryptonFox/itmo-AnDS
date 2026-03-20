#include <algorithm>
#include <iostream>
#include <vector>

constexpr int64_t kMaxDist = 2e18;

struct Edge {
  int src;
  int dest;
  int64_t dist;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector<Edge> edges;
  edges.reserve(n);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int d;
      std::cin >> d;
      if (d > 0) {
        edges.push_back({i, j, d});
      }
    }
  }

  std::vector dist(n, std::vector(n, kMaxDist));
  for (const auto& e : edges) {
    dist[e.src][e.dest] = e.dist;
  }
  for (int i = 0; i < n; i++) {
    dist[i][i] = 0;
  }

  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (dist[i][j] > dist[i][k] + dist[k][j]) {
          dist[i][j] = dist[i][k] + dist[k][j];
        }
      }
    }
  }

  std::vector eccentricities(n, 0LL);
  for (int i = 0; i < n; i++) {
    eccentricities[i] = *std::max_element(dist[i].begin(), dist[i].end());
  }
  std::cout << *std::max_element(eccentricities.begin(), eccentricities.end()) << std::endl;
  std::cout << *std::min_element(eccentricities.begin(), eccentricities.end()) << std::endl;
}