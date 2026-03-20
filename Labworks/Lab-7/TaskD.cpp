#include <iostream>
#include <queue>
#include <variant>
#include <vector>

constexpr int64_t kMinDest = -9e18;

struct Edge {
  int src;
  int dest;
  int64_t dist;
};

std::variant<bool, std::vector<int64_t>> MaxBellmanFord(
    const int n, const std::vector<Edge>& edges) {
  std::vector d(n, kMinDest);
  d[0] = 0;

  for (int i = 0; i < n - 1; i++) {
    for (const auto& [src, dest, dist] : edges) {
      if (d[src] > kMinDest && d[dest] < d[src] + dist) {
        d[dest] = d[src] + dist;
      }
    }
  }

  std::queue<int> bfs_q;
  std::vector visited(n, false);
  for (const auto& e : edges) {
    if (d[e.src] > kMinDest && d[e.dest] < d[e.src] + e.dist) {
      if (!visited[e.dest]) {
        bfs_q.push(e.dest);
        visited[e.dest] = true;
      }
    }
  }

  if (bfs_q.empty()) {
    return d;
  }

  std::vector<std::vector<int>> adj_list(n);
  for (const auto& e : edges) {
    adj_list[e.src].push_back(e.dest);
  }

  while (!bfs_q.empty()) {
    const int u = bfs_q.front();
    bfs_q.pop();
    if (u == n - 1) {
      return true;
    }
    for (int v : adj_list[u]) {
      if (visited[v]) continue;
      visited[v] = true;
      bfs_q.push(v);
    }
  }

  return d;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  std::vector<Edge> edges;
  edges.reserve(m);
  for (int i = 0; i < m; i++) {
    int a, b;
    int64_t w;
    std::cin >> a >> b >> w;
    edges.push_back({a - 1, b - 1, w});
  }

  const auto result = MaxBellmanFord(n, edges);

  if (std::holds_alternative<bool>(result)) {
    std::cout << ":)" << std::endl;
    return 0;
  }

  const auto res_dist = std::get<std::vector<int64_t>>(result);
  if (res_dist[n - 1] <= kMinDest) {
    std::cout << ":(" << std::endl;
    return 0;
  }
  std::cout << res_dist[n - 1] << std::endl;
}