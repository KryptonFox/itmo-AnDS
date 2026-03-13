#include <iostream>
#include <limits>
#include <queue>
#include <stack>
#include <vector>

struct Vertex {
  int index;
  int dist;
  bool operator>(const Vertex& e) const { return dist > e.dist; }
};

using WeightedGraph = std::vector<std::vector<Vertex>>;

void Dijkstra(int source, int destination, WeightedGraph& graph) {
  std::priority_queue<Vertex, std::vector<Vertex>, std::greater<Vertex>> pq;
  auto dist = std::vector(graph.size(), std::numeric_limits<int>::max());
  auto used = std::vector(graph.size(), false);
  auto parents = std::vector(graph.size(), -1);

  pq.push({source, 0});
  dist[source] = 0;

  while (!pq.empty()) {
    Vertex v = pq.top();
    pq.pop();
    if (used[v.index]) {
      continue;
    }
    used[v.index] = true;
    for (auto u : graph[v.index]) {
      if (dist[v.index] + u.dist < dist[u.index]) {
        dist[u.index] = dist[v.index] + u.dist;
        parents[u.index] = v.index;
        pq.push({u.index, dist[u.index]});
      }
    }
  }
  if (dist[destination] == std::numeric_limits<int>::max()) {
    std::cout << -1 << std::endl;
  }
  std::cout << dist[destination] << std::endl;

  auto path = std::stack<int>();
  int parent = destination;
  while (parent != source) {
    path.push(parent);
    parent = parents[parent];
  };
  path.push(parent);

  while (!path.empty()) {
    std::cout << path.top() + 1 << " ";
    path.pop();
  }
}

int main() {
  int n, m;
  std::cin >> n >> m;

  int s, f;
  std::cin >> s >> f;

  auto graph = WeightedGraph(n);
  for (int i = 0; i < m; i++) {
    int b, e, w;
    std::cin >> b >> e >> w;
    graph[e - 1].push_back({b - 1, w});
    graph[b - 1].push_back({e - 1, w});
  }

  Dijkstra(s - 1, f - 1, graph);
}