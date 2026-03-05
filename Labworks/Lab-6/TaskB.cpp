#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <vector>

using Graph = std::vector<std::vector<int>>;

std::vector<int> Bfs(const Graph& graph, int k) {
  auto d = std::vector(graph.size(), INT_MAX);
  auto res = std::vector<int>();
  d[0] = 0;

  std::queue<int> q;
  q.push(0);

  while (!q.empty()) {
    const int u = q.front();
    q.pop();
    for (const int v : graph[u]) {
      if (d[v] == INT_MAX) {
        d[v] = d[u] + 1;
        if (d[v] == k) {
          res.push_back(v);
        } else {
          q.push(v);
        }
      }
    }
  }
  return res;
}

int main() {
  int n;
  std::cin >> n;

  int m, k;
  std::cin >> m >> k;

  auto graph = std::vector<std::vector<int>>(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    std::cin >> u >> v;
    graph[u - 1].push_back(v - 1);
    graph[v - 1].push_back(u - 1);
  }

  auto res = Bfs(graph, k);

  if (res.empty()) {
    std::cout << "NO" << std::endl;
  } else {
    std::sort(res.begin(), res.end());
    for (const auto& u : res) {
      std::cout << u + 1 << std::endl;
    }
  };
}