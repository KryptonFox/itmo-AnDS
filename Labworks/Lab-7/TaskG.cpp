#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int64_t h;
  int64_t a, b, c;
  std::cin >> h >> a >> b >> c;

  h -= 1;

  if (a > b) std::swap(a, b);
  if (a > c) std::swap(a, c);

  std::vector<int64_t> dist(a, 2e18);
  std::priority_queue<std::pair<int64_t, int>,
                      std::vector<std::pair<int64_t, int>>,
                      std::greater<>> pq;

  dist[0] = 0;
  pq.push({0, 0});

  while (!pq.empty()) {
    auto [d, u] = pq.top();
    pq.pop();

    if (d > dist[u]) continue;

    int v1 = (u + b) % a;
    if (dist[v1] > d + b) {
      dist[v1] = d + b;
      pq.push({dist[v1], v1});
    }

    int v2 = (u + c) % a;
    if (dist[v2] > d + c) {
      dist[v2] = d + c;
      pq.push({dist[v2], v2});
    }
  }

  int64_t ans = 0;
  for (int i = 0; i < a; ++i) {
    if (dist[i] <= h) {
      ans += (h - dist[i]) / a + 1;
    }
  }

  std::cout << ans << std::endl;
}