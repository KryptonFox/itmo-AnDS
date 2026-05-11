#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

constexpr int kInf = 1e9;

struct Edge {
  int from;
  int to;
  int cap;
  int flow;
};

void AddEdge(std::vector<Edge>& edges, std::vector<std::vector<int>>& adj,
             int from, int to, int cap, bool is_bidirectional = false) {
  adj[from].push_back(edges.size());
  edges.push_back({from, to, cap, 0});

  adj[to].push_back(edges.size());
  edges.push_back({to, from, is_bidirectional ? cap : 0, 0});
}

int EdmondsKarp(int n, int s, int t, std::vector<Edge>& edges,
                const std::vector<std::vector<int>>& adj) {
  int flow = 0;
  std::vector<int> parent(n);

  while (true) {
    std::fill(parent.begin(), parent.end(), -1);
    std::queue<std::pair<int, int>> q;

    q.push({s, kInf});
    parent[s] = -2;

    int pushed_flow = 0;

    while (!q.empty()) {
      auto [v, current_flow] = q.front();
      q.pop();

      if (v == t) {
        pushed_flow = current_flow;
        break;
      }

      for (int edge_idx : adj[v]) {
        const Edge& edge = edges[edge_idx];
        if (parent[edge.to] == -1 && edge.cap - edge.flow > 0) {
          parent[edge.to] = edge_idx;
          q.push({edge.to, std::min(current_flow, edge.cap - edge.flow)});
        }
      }
    }

    if (pushed_flow == 0) {
      break;
    }

    flow += pushed_flow;

    int curr = t;
    while (curr != s) {
      int edge_idx = parent[curr];
      edges[edge_idx].flow += pushed_flow;
      edges[edge_idx ^ 1].flow -= pushed_flow;
      curr = edges[edge_idx].from;
    }
  }

  return flow;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m, w, b, g;
  std::cin >> n >> m >> w >> b >> g;

  std::vector<std::string> grid(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> grid[i];
  }

  int source = 0;
  int sink = n * m + 1;
  int total_nodes = sink + 1;

  std::vector<Edge> edges;
  std::vector<std::vector<int>> adj(total_nodes);

  auto get_node_id = [&](int r, int c) { return r * m + c + 1; };

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      int u = get_node_id(i, j);

      if (grid[i][j] == 'B') {
        AddEdge(edges, adj, source, u, w, false);
      } else {
        AddEdge(edges, adj, u, sink, b, false);
      }

      if (j + 1 < m) {
        int v = get_node_id(i, j + 1);
        AddEdge(edges, adj, u, v, g, true);
      }
      if (i + 1 < n) {
        int v = get_node_id(i + 1, j);
        AddEdge(edges, adj, u, v, g, true);
      }
    }
  }

  std::cout << EdmondsKarp(total_nodes, source, sink, edges, adj);
}