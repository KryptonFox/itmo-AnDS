#include <algorithm>
#include <iostream>
#include <vector>

struct Edge {
  int to;
  int capacity;
  int flow;
  int reverse_edge_index;
};

void AddEdge(int from, int to, int capacity,
             std::vector<std::vector<Edge>>& adjacency_list) {
  Edge forward = {to, capacity, 0, static_cast<int>(adjacency_list[to].size())};
  Edge backward = {from, 0, 0, static_cast<int>(adjacency_list[from].size())};
  adjacency_list[from].push_back(forward);
  adjacency_list[to].push_back(backward);
}

int FordFulkerson(int current_node, int sink, int flow_to_push,
                       std::vector<std::vector<Edge>>& adjacency_list,
                       std::vector<bool>& visited) {
  if (current_node == sink) return flow_to_push;
  visited[current_node] = true;

  for (auto& edge : adjacency_list[current_node]) {
    int residual_capacity = edge.capacity - edge.flow;
    if (!visited[edge.to] && residual_capacity > 0) {
      int pushed = FordFulkerson(
          edge.to, sink, std::min(flow_to_push, residual_capacity),
          adjacency_list, visited);

      if (pushed > 0) {
        edge.flow += pushed;
        int reverse_idx = edge.reverse_edge_index;
        adjacency_list[edge.to][reverse_idx].flow -= pushed;
        return pushed;
      }
    }
  }
  return 0;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int num_teams;
  std::cin >> num_teams;

  std::vector<int> current_wins(num_teams);
  for (int i = 0; i < num_teams; ++i) std::cin >> current_wins[i];

  std::vector<int> remaining_total(num_teams);
  for (int i = 0; i < num_teams; ++i) std::cin >> remaining_total[i];

  std::vector<std::vector<int>> match_matrix(
      num_teams, std::vector<int>(num_teams));
  for (int i = 0; i < num_teams; ++i) {
    for (int j = 0; j < num_teams; ++j) {
      std::cin >> match_matrix[i][j];
    }
  }

  int aurora_limit = current_wins[0] + remaining_total[0];

  for (int i = 1; i < num_teams; ++i) {
    if (current_wins[i] > aurora_limit) {
      std::cout << "NO" << std::endl;
      return 0;
    }
  }

  int source = 0;
  int sink = 1;
  int next_free_node = num_teams + 2;
  std::vector<std::vector<Edge>> adj(num_teams * num_teams + num_teams + 2);
  int total_needed_flow = 0;

  for (int i = 1; i < num_teams; ++i) {
    for (int j = i + 1; j < num_teams; ++j) {
      if (match_matrix[i][j] > 0) {
        int games = match_matrix[i][j];
        int match_node = next_free_node++;
        total_needed_flow += games;

        AddEdge(source, match_node, games, adj);
        AddEdge(match_node, i + 2, games, adj);
        AddEdge(match_node, j + 2, games, adj);
      }
    }
    int safety_buffer = aurora_limit - current_wins[i];
    AddEdge(i + 2, sink, safety_buffer, adj);
  }

  int max_flow = 0;
  while (true) {
    std::vector<bool> visited(next_free_node, false);
    int pushed = FordFulkerson(source, sink, 1e9, adj, visited);
    if (pushed == 0) break;
    max_flow += pushed;
  }

  if (max_flow == total_needed_flow) {
    std::cout << "YES" << std::endl;
  } else {
    std::cout << "NO" << std::endl;
  }
}