#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

const long long kInf = 1e15;

struct Edge {
  int to;
  long long capacity;
  long long flow;
  size_t rev;
};

void AddEdge(int from, int to, long long capacity,
             std::vector<std::vector<Edge>>& adj) {
  adj[from].push_back({to, capacity, 0, adj[to].size()});
  adj[to].push_back({from, 0, 0, adj[from].size() - 1});
}

bool Bfs(int s, int t, const std::vector<std::vector<Edge>>& adj,
         std::vector<int>& parent_node, std::vector<int>& parent_edge) {
  std::fill(parent_node.begin(), parent_node.end(), -1);
  std::queue<int> q;

  q.push(s);
  parent_node[s] = s;

  while (!q.empty()) {
    int v = q.front();
    q.pop();

    for (int i = 0; i < static_cast<int>(adj[v].size()); ++i) {
      const Edge& edge = adj[v][i];
      if (parent_node[edge.to] == -1 && edge.capacity - edge.flow > 0) {
        parent_node[edge.to] = v;
        parent_edge[edge.to] = i;
        if (edge.to == t) return true;
        q.push(edge.to);
      }
    }
  }
  return false;
}

long long MaxFlow(int s, int t, std::vector<std::vector<Edge>>& adj) {
  long long flow = 0;
  int num_nodes = adj.size();
  std::vector<int> parent_node(num_nodes);
  std::vector<int> parent_edge(num_nodes);

  while (Bfs(s, t, adj, parent_node, parent_edge)) {
    long long path_flow = kInf;

    for (int v = t; v != s; v = parent_node[v]) {
      int u = parent_node[v];
      int edge_idx = parent_edge[v];
      path_flow = std::min(path_flow,
                           adj[u][edge_idx].capacity - adj[u][edge_idx].flow);
    }

    for (int v = t; v != s; v = parent_node[v]) {
      int u = parent_node[v];
      int edge_idx = parent_edge[v];
      int rev_idx = adj[u][edge_idx].rev;

      adj[u][edge_idx].flow += path_flow;
      adj[v][rev_idx].flow -= path_flow;
    }
    flow += path_flow;
  }
  return flow;
}

int main() {
  int n, m, p;
  std::cin >> n >> m >> p;

  int source = 0;
  int sink = n + m + p + 1;
  std::vector<std::vector<Edge>> adj(sink + 1);

  long long total_potential_profit = 0;

  for (int i = 1; i <= n; ++i) {
    long long value;
    int num_modules;
    std::cin >> value >> num_modules;
    total_potential_profit += value;
    AddEdge(source, i, value, adj);

    for (int j = 0; j < num_modules; ++j) {
      int module_idx;
      std::cin >> module_idx;
      AddEdge(i, n + module_idx, kInf, adj);
    }
  }

  std::vector<long long> costs(m + 1);
  for (int i = 1; i <= m; ++i) {
    std::cin >> costs[i];
    AddEdge(n + i, sink, costs[i], adj);
  }

  for (int i = 1; i <= p; ++i) {
    int a, b;
    long long discount_price;
    std::cin >> a >> b >> discount_price;

    long long savings = costs[a] + costs[b] - discount_price;
    if (savings > 0) {
      total_potential_profit += savings;
      int case_node = n + m + i;
      AddEdge(source, case_node, savings, adj);
      AddEdge(case_node, n + a, kInf, adj);
      AddEdge(case_node, n + b, kInf, adj);
    }
  }

  std::cout << total_potential_profit - MaxFlow(source, sink, adj) << std::endl;
}