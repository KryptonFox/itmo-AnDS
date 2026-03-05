#include <iostream>
#include <stack>
#include <vector>

using Graph = std::vector<std::vector<int>>;

void Dfs(const int u, const Graph& graph, std::vector<bool>& visited, std::stack<int>& res) {
  visited[u] = true;
  for (const auto& v : graph[u]) {
    if (!visited[v]) {
      Dfs(v, graph, visited, res);
    }
  }
  res.push(u);
}

std::stack<int> TopSort(const Graph& graph, const int n) {
  auto visited = std::vector(n, false);
  auto res = std::stack<int>();

  for (int i = 0; i < n; ++i) {
    if (!visited[i]) {
      Dfs(i, graph, visited, res);
    }
  }
  return res;
}

int main() {
  int n, m;
  std::cin >> n >> m;

  auto graph = std::vector<std::vector<int>>(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    std::cin >> u >> v;
    graph[u - 1].push_back(v - 1);
  }

  auto res = TopSort(graph, n);

  auto ranks = std::vector<int>(n);
  for (int i = 0; i < n; ++i) {
    const int v = res.top();
    res.pop();
    ranks[v] = i + 1;
  }

  for (const auto& i : ranks) {
    std::cout << i << " ";
  }
}