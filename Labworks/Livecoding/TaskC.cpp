#include <cstring>
#include <iostream>

#define MAX_N 1001
#define MAX_STATES (MAX_N * MAX_N)
#define MAX_DIGITS 256

struct State {
  int rem;
  int sum;
};

struct ParentInfo {
  int prev_rem;
  int prev_sum;
  int digit;
};

ParentInfo g_parent[MAX_N][MAX_N];

int g_visited[MAX_N][MAX_N];
State g_states_current_len[MAX_STATES];
State g_states_next_len[MAX_STATES];

void Reconstruct(int n) {
  char result[MAX_DIGITS];
  int current_rem = 0;
  int current_sum = n;
  int len = 0;

  while (current_sum > 0 && len < MAX_DIGITS - 1) {
    ParentInfo info = g_parent[current_rem][current_sum];

    result[len] = '0' + info.digit;
    len++;

    current_rem = info.prev_rem;
    current_sum = info.prev_sum;
  }

  for (int i = 0; i < len / 2; i++) {
    char temp = result[i];
    result[i] = result[len - 1 - i];
    result[len - 1 - i] = temp;
  }
  result[len] = '\0';

  std::cout << result;
}

void Solve(int n) {
  memset(g_visited, 0, sizeof(g_visited));
  int current_len_count = 0;

  for (int d = 1; d <= 9; ++d) {
    if (d <= n) {
      int rem = d % n;
      int sum = d;

      if (g_visited[rem][sum] == 0) {
        g_visited[rem][sum] = 1;

        g_parent[rem][sum].prev_rem = 0;
        g_parent[rem][sum].prev_sum = 0;
        g_parent[rem][sum].digit = d;

        g_states_current_len[current_len_count].rem = rem;
        g_states_current_len[current_len_count].sum = sum;
        current_len_count++;

        if (rem == 0 && sum == n) {
          std::cout << d;
          return;
        }
      }
    }
  }

  for (int len = 2;; ++len) {
    int next_len_count = 0;

    for (int i = 0; i < current_len_count; ++i) {
      int rem = g_states_current_len[i].rem;
      int sum = g_states_current_len[i].sum;

      for (int d = 0; d <= 9; ++d) {
        int new_sum = sum + d;

        if (new_sum <= n) {
          int new_rem = (rem * 10 + d) % n;

          if (g_visited[new_rem][new_sum] == 0) {
            g_visited[new_rem][new_sum] = 1;

            g_parent[new_rem][new_sum].prev_rem = rem;
            g_parent[new_rem][new_sum].prev_sum = sum;
            g_parent[new_rem][new_sum].digit = d;

            g_states_next_len[next_len_count].rem = new_rem;
            g_states_next_len[next_len_count].sum = new_sum;
            next_len_count++;

            if (new_rem == 0 && new_sum == n) {
              Reconstruct(n);
              return;
            }
          }
        }
      }
    }

    if (next_len_count > 0) {
      memcpy(g_states_current_len, g_states_next_len,
             next_len_count * sizeof(State));
      current_len_count = next_len_count;
    } else {
      break;
    }
  }
}

int main() {
  int n;

  std::cin >> n;
  Solve(n);

  return 0;
}