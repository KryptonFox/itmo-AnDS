#include <iostream>

int main() {
  int n, m, k;

  std::cin >> n >> m >> k;

  // input matrix A
  int demand_matrix[n][m];

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      std::cin >> demand_matrix[i][j];
    }
  }

  // input matrix B
  int route_matrix[m][k];

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < k; j++) {
      std::cin >> route_matrix[i][j];
    }
  }

  // multiply matrix
  int shipment_plan_matrix[n][k];

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < k; j++) {
      shipment_plan_matrix[i][j] = 0;
      for (int l = 0; l < m; l++) {
        shipment_plan_matrix[i][j] += demand_matrix[i][l] * route_matrix[l][j];
      }
    }
  }

  // output
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < k - 1; j++) {
      std::cout << shipment_plan_matrix[i][j] << " ";
    }
    std::cout << shipment_plan_matrix[i][k - 1] << "\n";
  }
}