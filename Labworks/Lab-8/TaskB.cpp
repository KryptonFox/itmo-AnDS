#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

constexpr long long kInf = 1e18;

struct Edge {
  int to;
  int cap;
  long long cost;
  int id;
  int rev;
};

struct FlowResult {
  long long max_weight;
  std::vector<int> matching_edges;
};

void AddEdge(std::vector<std::vector<Edge>>& adj, int u, int v, int cap,
             long long cost, int id) {
  adj[u].push_back({v, cap, cost, id, static_cast<int>(adj[v].size())});
  adj[v].push_back({u, 0, -cost, -1, static_cast<int>(adj[u].size()) - 1});
}

void InitializePotentials(int n, int m, const std::vector<int>& weight_l,
                          const std::vector<int>& weight_r, int source,
                          int sink, const std::vector<std::vector<Edge>>& adj,
                          std::vector<long long>& pot) {
  int num_nodes = adj.size();
  std::vector<long long> dist(num_nodes, kInf);
  dist[source] = 0;

  for (int iter = 0; iter < num_nodes - 1; ++iter) {
    bool updated = false;
    for (int u = 0; u < num_nodes; ++u) {
      if (dist[u] == kInf) continue;
      for (const Edge& e : adj[u]) {
        if (e.cap > 0 && dist[u] + e.cost < dist[e.to]) {
          dist[e.to] = dist[u] + e.cost;
          updated = true;
        }
      }
    }
    if (!updated) break;
  }
  pot = dist;
}

FlowResult CalculateMinCostMaxFlow(int n, std::vector<std::vector<Edge>>& adj,
                                   std::vector<long long>& pot, int source,
                                   int sink, int num_nodes) {
  long long max_total_weight = 0;

  std::vector<long long> dist(num_nodes);
  std::vector<int> parent_node(num_nodes);
  std::vector<int> parent_edge(num_nodes);

  while (true) {
    std::fill(dist.begin(), dist.end(), kInf);
    std::fill(parent_node.begin(), parent_node.end(), -1);
    std::fill(parent_edge.begin(), parent_edge.end(), -1);

    using QueueItem = std::pair<long long, int>;
    std::priority_queue<QueueItem, std::vector<QueueItem>,
                        std::greater<QueueItem>> pq;

    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
      auto [d, u] = pq.top();
      pq.pop();

      if (d != dist[u]) continue;
      if (u == sink) break;

      for (size_t i = 0; i < adj[u].size(); ++i) {
        const Edge& e = adj[u][i];
        if (e.cap > 0) {
          long long reduced_cost = e.cost + pot[u] - pot[e.to];
          if (dist[u] + reduced_cost < dist[e.to]) {
            dist[e.to] = dist[u] + reduced_cost;
            parent_node[e.to] = u;
            parent_edge[e.to] = i;
            pq.push({dist[e.to], e.to});
          }
        }
      }
    }

    if (dist[sink] == kInf) break;

    for (int v = 0; v < num_nodes; ++v) {
      if (dist[v] < kInf) pot[v] += dist[v];
    }

    if (pot[sink] >= 0) break;

    int curr = sink;
    while (curr != source) {
      int p = parent_node[curr];
      int idx = parent_edge[curr];
      int rev_idx = adj[p][idx].rev;

      adj[p][idx].cap -= 1;
      adj[curr][rev_idx].cap += 1;
      curr = p;
    }

    max_total_weight += -pot[sink];
  }

  std::vector<int> matching_edges;
  for (int i = 1; i <= n; ++i) {
    for (const Edge& e : adj[i]) {
      if (e.id != -1 && e.cap == 0) {
        matching_edges.push_back(e.id);
      }
    }
  }

  return {max_total_weight, matching_edges};
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m, e;
  std::cin >> n >> m >> e;

  std::vector<int> weight_l(n + 1);
  for (int i = 1; i <= n; ++i) {
    std::cin >> weight_l[i];
  }

  std::vector<int> weight_r(m + 1);
  for (int i = 1; i <= m; ++i) {
    std::cin >> weight_r[i];
  }

  int num_nodes = n + m + 2;
  int source = 0;
  int sink = n + m + 1;

  std::vector<std::vector<Edge>> adj(num_nodes);

  for (int i = 1; i <= n; ++i) {
    AddEdge(adj, source, i, 1, -weight_l[i], -1);
  }
  for (int j = 1; j <= m; ++j) {
    AddEdge(adj, n + j, sink, 1, -weight_r[j], -1);
  }
  for (int i = 1; i <= e; ++i) {
    int u, v;
    std::cin >> u >> v;
    AddEdge(adj, u, n + v, 1, 0, i);
  }

  std::vector<long long> pot(num_nodes, kInf);
  InitializePotentials(n, m, weight_l, weight_r, source, sink, adj, pot);

  FlowResult result = CalculateMinCostMaxFlow(n, adj, pot, source, sink,
                                              num_nodes);

  std::cout << result.max_weight << std::endl;
  std::cout << result.matching_edges.size() << std::endl;
  for (size_t i = 0; i < result.matching_edges.size(); ++i) {
    std::cout << result.matching_edges[i] << (
      i + 1 == result.matching_edges.size() ? "" : " ");
  }
  std::cout << std::endl;
}