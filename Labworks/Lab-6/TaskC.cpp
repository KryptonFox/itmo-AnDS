#include <iostream>
#include <vector>

using Graph = std::vector<std::vector<int>>;

enum EColor {
  kWhite,
  kGray,
  kBlack,
};

void FindCyclesWithDfs(const int u, Graph& graph, std::vector<EColor>& colors,
                       bool& found, const int prev) {
  colors[u] = kGray;
  for (const auto& v : graph[u]) {
    switch (colors[v]) {
      case kWhite:
        FindCyclesWithDfs(v, graph, colors, found, u);
        break;
      case kGray:
        if (v != prev) {
          found = v != prev;
          return;
        }
      default:
        break;
    }
    if (found) {
      return;
    }
  }
  colors[u] = kBlack;
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

  auto colors = std::vector(n, kWhite);
  bool found = false;

  for (int i = 0; i < n; ++i) {
    if (colors[i] == kBlack) {
      continue;
    }
    FindCyclesWithDfs(i, graph, colors, found, -1);
    if (found) {
      std::cout << "YES" << std::endl;
      return 0;
    }
  }

  std::cout << "NO" << std::endl;
}