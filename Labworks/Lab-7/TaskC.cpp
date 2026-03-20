#include <iostream>
#include <vector>
#include <queue>

constexpr int64_t kMinDest = 2e18;
constexpr int64_t kInLimbo = -9e18;

struct Edge {
  int src;
  int dest;
  int64_t dist;
};

struct Result {
  std::vector<int64_t> distances;
  std::vector<bool> in_limbo;
};

Result BellmanFordWithLimboSearch(const int source, const int n, const std::vector<Edge>& edges) {
  std::vector d(n, kMinDest);
  std::vector in_limbo(n, false);

  d[source - 1] = 0;

  for (int i = 0; i < n - 1; i++) {
    for (const auto& e : edges) {
      if (d[e.src] < kMinDest && d[e.dest] > d[e.src] + e.dist) {
        d[e.dest] = d[e.src] + e.dist;
      }
    }
  }

  std::vector<std::vector<int>> adj_list(n);
  std::queue<int> bfs_q;
  for (const auto& e : edges) {
    adj_list[e.src].push_back(e.dest);
    if (d[e.src] < kMinDest && d[e.dest] > d[e.src] + e.dist) {
      if (!in_limbo[e.dest]) {
        in_limbo[e.dest] = true;
        bfs_q.push(e.dest);
      }
    }
  }

  while (!bfs_q.empty()) {
    int u = bfs_q.front();
    bfs_q.pop();
    for (int v : adj_list[u]) {
      if (!in_limbo[v]) {
        in_limbo[v] = true;
        bfs_q.push(v);
      }
    }
  }

  return {d, in_limbo};
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m, s;
  std::cin >> n >> m >> s;

  std::vector<Edge> edges;
  edges.reserve(m);

  for (int i = 0; i < m; i++) {
    int a, b;
    int64_t w;
    std::cin >> a >> b >> w;
    edges.push_back({a - 1, b - 1, w});
  }

  const auto [distances, in_limbo] = BellmanFordWithLimboSearch(s, n, edges);

  for (int i = 0; i < n; i++) {
    if (in_limbo[i]) {
      std::cout << '-' << "\n";
    } else if (distances[i] >= kMinDest) {
      std::cout << '*' << "\n";
    } else {
      std::cout << distances[i] << "\n";
    }
  }
}