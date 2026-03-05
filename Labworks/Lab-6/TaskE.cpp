#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using Graph = std::vector<std::vector<int>>;

void FirstDfs(const int u, Graph& graph, std::vector<bool>& visited,
              std::stack<int>& ord) {
  visited[u] = true;
  for (const auto& v : graph[u]) {
    if (!visited[v]) {
      FirstDfs(v, graph, visited, ord);
    }
  }
  ord.push(u);
}

void SecondDfs(const int u, Graph& graph, std::vector<bool>& in_component,
               std::vector<int>& component) {
  in_component[u] = true;
  for (const auto& v : graph[u]) {
    if (!in_component[v]) {
      SecondDfs(v, graph, in_component, component);
    }
  }
  component.push_back(u);
}

int main() {
  int n, m, q;
  std::cin >> n >> m >> q;

  auto graph = std::vector<std::vector<int>>(n);
  auto inverted_graph = std::vector<std::vector<int>>(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    std::cin >> u >> v;
    graph[u - 1].push_back(v - 1);
    inverted_graph[v - 1].push_back(u - 1);
  }

  auto visited = std::vector<bool>(n, false);
  auto ord = std::stack<int>();
  for (int i = 0; i < n; i++) {
    if (!visited[i]) {
      FirstDfs(i, inverted_graph, visited, ord);
    }
  }

  auto in_component = std::vector<bool>(n, false);
  auto components = std::vector<std::vector<int>>();

  while (!ord.empty()) {
    if (!in_component[ord.top()]) {
      auto component = std::vector<int>();
      SecondDfs(ord.top(), graph, in_component, component);
      components.push_back(component);
    }
    ord.pop();
  }

  for (int i = 0; i < q; i++) {
    int u, v;
    std::cin >> u >> v;
    bool found = false;
    for (const auto& component: components) {
      if (std::count(component.begin(), component.end(), u - 1) && std::count(component.begin(), component.end(), v - 1)) {
        std::cout << "YES" << std::endl;
        found = true;
        break;
      }
    }
    if (!found) {
      std::cout << "NO" << std::endl;
    }
  }
}
