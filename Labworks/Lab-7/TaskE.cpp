#include <iostream>
#include <vector>

constexpr double kMinDest = -1.;

struct Exchange {
  int src;
  int dest;
  double rate;
  double comm;
};

bool JonWeekMoneys(const int n, const std::vector<Exchange>& edges,
                   const int initial_valuta, const double initial_money) {
  std::vector d(n, kMinDest);
  d[initial_valuta - 1] = initial_money;

  for (int i = 0; i < n - 1; i++) {
    for (const auto& e : edges) {
      if (d[e.src] > 0 && d[e.dest] < (d[e.src] - e.comm) * e.rate) {
        d[e.dest] = (d[e.src] - e.comm) * e.rate;
      }
    }
  }

  for (const auto& e : edges) {
    if (d[e.src] > 0 && d[e.dest] < (d[e.src] - e.comm) * e.rate) {
      return true;
    }
  }

  return false;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m, s;
  double v;
  std::cin >> n >> m >> s >> v;

  std::vector<Exchange> edges;
  edges.reserve(m);
  for (int i = 0; i < m; i++) {
    int a, b;
    double rab, cab, rba, cba;
    std::cin >> a >> b >> rab >> cab >> rba >> cba;
    edges.push_back({a - 1, b - 1, rab, cab});
    edges.push_back({b - 1, a - 1, rba, cba});
  }

  const auto result = JonWeekMoneys(n, edges, s, v);
  std::cout << (result ? "YES" : "NO") << std::endl;
}