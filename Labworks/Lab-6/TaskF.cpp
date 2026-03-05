#include <algorithm>
#include <iostream>
#include <vector>

using Graph = std::vector<std::vector<int>>;

void Dfs(const int u, Graph& graph, std::vector<bool>& visited) {
  visited[u] = true;
  for (const auto& v : graph[u]) {
    if (!visited[v]) {
      Dfs(v, graph, visited);
    }
  }
}

int main() {
  int n, m;
  std::cin >> n >> m;

  auto graph = std::vector<std::vector<int>>(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    std::cin >> u >> v;
    graph[u - 1].push_back(v - 1);
    graph[v - 1].push_back(u - 1);
  }

  if (n != m) {
    std::cout << "EUCLID" << std::endl;
    return 0;
  }

  auto visited = std::vector(n, false);

  Dfs(0, graph, visited);
  if (std::find(visited.begin(), visited.end(), false) == visited.end()) {
    std::cout << "ARCHIMEDES" << std::endl;
  } else {
    std::cout << "EUCLID" << std::endl;
  }
}
