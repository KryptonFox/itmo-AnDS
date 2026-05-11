#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

struct Point {
  long long x, y;
};

struct Edge {
  int u, v;
};

struct MstEdge {
  int u, v;
  double cost;
  bool operator<(const MstEdge& other) const { return cost < other.cost; }
};

struct Dsu {
  std::vector<int> parent;
  explicit Dsu(int n) {
    parent.resize(n);
    for (int i = 0; i < n; ++i) parent[i] = i;
  }
  int find(int i) {
    if (parent[i] == i) return i;
    return parent[i] = find(parent[i]);
  }
  void unite(int i, int j) {
    int root_i = find(i);
    int root_j = find(j);
    if (root_i != root_j) parent[root_i] = root_j;
  }
};

double GetTurnAngle(const Point& u, const Point& v, const Point& w) {
  double ax = static_cast<double>(v.x - u.x);
  double ay = static_cast<double>(v.y - u.y);
  double bx = static_cast<double>(w.x - v.x);
  double by = static_cast<double>(w.y - v.y);

  double ang_a = std::atan2(ay, ax);
  double ang_b = std::atan2(by, bx);

  double diff = ang_b - ang_a;
  while (diff > M_PI) diff -= 2 * M_PI;
  while (diff <= -M_PI) diff += 2 * M_PI;

  return std::abs(diff);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  std::vector<Point> points(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> points[i].x >> points[i].y;
  }

  std::vector<Edge> edges(m);
  std::vector<std::vector<int>> adj(n);
  for (int i = 0; i < m; ++i) {
    std::cin >> edges[i].u >> edges[i].v;
    adj[edges[i].u].push_back(i);
    adj[edges[i].v].push_back(i);
  }

  double total_cost = 0;
  Dsu cycle_dsu(m);

  struct Pairing {
    int e1, e2, e3, e4;
    double w1, w2, w3;
  };
  std::vector<Pairing> deg4_nodes;

  for (int i = 0; i < n; ++i) {
    if (adj[i].size() == 2) {
      int e1 = adj[i][0];
      int e2 = adj[i][1];
      int u = (edges[e1].u == i) ? edges[e1].v : edges[e1].u;
      int w = (edges[e2].u == i) ? edges[e2].v : edges[e2].u;
      total_cost += GetTurnAngle(points[u], points[i], points[w]);
      cycle_dsu.unite(e1, e2);
    } else if (adj[i].size() == 4) {
      int e[4];
      Point neighbors[4];
      for (int k = 0; k < 4; ++k) {
        e[k] = adj[i][k];
        int other = (edges[e[k]].u == i) ? edges[e[k]].v : edges[e[k]].u;
        neighbors[k] = points[other];
      }

      double w1 = GetTurnAngle(neighbors[0], points[i], neighbors[1]) +
                  GetTurnAngle(neighbors[2], points[i], neighbors[3]);
      double w2 = GetTurnAngle(neighbors[0], points[i], neighbors[2]) +
                  GetTurnAngle(neighbors[1], points[i], neighbors[3]);
      double w3 = GetTurnAngle(neighbors[0], points[i], neighbors[3]) +
                  GetTurnAngle(neighbors[1], points[i], neighbors[2]);

      if (w1 <= w2 && w1 <= w3) {
        total_cost += w1;
        cycle_dsu.unite(e[0], e[1]);
        cycle_dsu.unite(e[2], e[3]);
        deg4_nodes.push_back({e[0], e[1], e[2], e[3], w1, w2, w3});
      } else if (w2 <= w1 && w2 <= w3) {
        total_cost += w2;
        cycle_dsu.unite(e[0], e[2]);
        cycle_dsu.unite(e[1], e[3]);
        deg4_nodes.push_back({e[0], e[2], e[1], e[3], w2, w1, w3});
      } else {
        total_cost += w3;
        cycle_dsu.unite(e[0], e[3]);
        cycle_dsu.unite(e[1], e[2]);
        deg4_nodes.push_back({e[0], e[3], e[1], e[2], w3, w1, w2});
      }
    }
  }

  std::vector<MstEdge> mst_pool;
  for (const auto& node : deg4_nodes) {
    int c1 = cycle_dsu.find(node.e1);
    int c2 = cycle_dsu.find(node.e3);
    if (c1 != c2) {
      double min_alt = std::min(node.w2, node.w3) - node.w1;
      mst_pool.push_back({c1, c2, min_alt});
    }
  }

  std::sort(mst_pool.begin(), mst_pool.end());
  Dsu final_dsu(m);
  for (const auto& edge : mst_pool) {
    if (final_dsu.find(edge.u) != final_dsu.find(edge.v)) {
      final_dsu.unite(edge.u, edge.v);
      total_cost += edge.cost;
    }
  }

  std::cout << std::fixed << std::setprecision(6) << total_cost << std::endl;
}