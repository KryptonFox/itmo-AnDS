#include <iostream>
#include <vector>

bool Kuhn(
    int left_node,
    const std::vector<std::vector<int>>& adjacency_list,
    std::vector<int>& matching_right_to_left,
    std::vector<bool>& visited) {
  if (visited[left_node]) return false;
  visited[left_node] = true;

  for (int right_node : adjacency_list[left_node]) {
    int current_match = matching_right_to_left[right_node];
    if (current_match == -1 ||
        Kuhn(current_match, adjacency_list,
             matching_right_to_left, visited)) {
      matching_right_to_left[right_node] = left_node;
      return true;
    }
  }
  return false;
}

void MarkAsLosing(
    int node,
    const std::vector<std::vector<int>>& adjacency_list,
    const std::vector<int>& matching,
    std::vector<bool>& is_losing) {
  if (is_losing[node]) return;
  is_losing[node] = true;

  for (int neighbor : adjacency_list[node]) {
    int matched_node = matching[neighbor];
    if (matched_node != -1) {
      MarkAsLosing(matched_node, adjacency_list,
                   matching, is_losing);
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int num_left, num_right, num_edges;
  std::cin >> num_left >> num_right >> num_edges;

  std::vector<std::vector<int>> adj_left(num_left);
  std::vector<std::vector<int>> adj_right(num_right);

  for (int i = 0; i < num_edges; ++i) {
    int u, v;
    std::cin >> u >> v;
    adj_left[u - 1].push_back(v - 1);
    adj_right[v - 1].push_back(u - 1);
  }

  std::vector<int> match_left_to_right(num_left, -1);
  std::vector<int> match_right_to_left(num_right, -1);

  for (int i = 0; i < num_left; ++i) {
    std::vector<bool> visited(num_left, false);
    Kuhn(i, adj_left, match_right_to_left, visited);
  }

  for (int j = 0; j < num_right; ++j) {
    match_left_to_right[match_right_to_left[j]] = j;
  }

  std::vector<bool> is_p_position_left(num_left, false);
  std::vector<bool> is_p_position_right(num_right, false);

  for (int i = 0; i < num_left; ++i) {
    if (match_left_to_right[i] == -1) {
      MarkAsLosing(i, adj_left, match_right_to_left, is_p_position_left);
    }
  }

  for (int j = 0; j < num_right; ++j) {
    if (match_right_to_left[j] == -1) {
      MarkAsLosing(j, adj_right, match_left_to_right, is_p_position_right);
    }
  }

  for (int i = 0; i < num_left; ++i) {
    std::cout << (is_p_position_left[i] ? 'P' : 'N');
  }
  std::cout << std::endl;
  for (int j = 0; j < num_right; ++j) {
    std::cout << (is_p_position_right[j] ? 'P' : 'N');
  }
  std::cout << std::endl;
}