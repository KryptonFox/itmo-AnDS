#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <tuple>
#include <vector>

/**
 * Структура для хранения информации о пути (для восстановления числа).
 */
struct ParentInfo {
  int prev_remainder;
  int prev_sum;
  int digit;
};

// Функция для восстановления числа из информации о родителях
std::string ReconstructNumber(
    int n, const std::vector<std::vector<ParentInfo>>& parent) {
  std::string result = "";
  int current_rem = 0;
  int current_sum = n;

  while (current_sum > 0) {
    // Получаем информацию о предыдущем шаге
    const ParentInfo& info = parent[current_rem][current_sum];

    // Добавляем цифру в начало результата
    result += std::to_string(info.digit);

    // Переходим к предыдущему состоянию
    current_rem = info.prev_remainder;
    current_sum = info.prev_sum;
  }

  std::reverse(result.begin(), result.end());
  return result;
}

/**
 * Функция Solve с использованием Динамического Программирования (Итеративное
 * Построение). Ищет решение, итерируя по длине числа.
 */
std::string SolveDP(int n) {
  if (n <= 0 || n > 180) {
    return "N/A";
  }

  // Размеры: n остатков [0..n-1] и n+1 сумма [0..n]
  // parent[rem][sum] будет хранить информацию о переходе
  std::vector<std::vector<ParentInfo>> parent(n,
                                              std::vector<ParentInfo>(n + 1));

  // states_current_len: Хранит пары (remainder, sum_so_far), достигнутые на
  // текущем уровне (длине числа) Это заменяет очередь BFS.
  std::vector<std::pair<int, int>> states_current_len;

  // states_next_len: Хранит пары (remainder, sum_so_far) для следующего уровня
  std::vector<std::pair<int, int>> states_next_len;

  // visited[rem][sum] для отслеживания, достигнуто ли состояние
  std::vector<std::vector<bool>> visited(n, std::vector<bool>(n + 1, false));

  // 1. Инициализация (Длина = 1)
  for (int d = 1; d <= 9; ++d) {
    if (d <= n) {
      int rem = d % n;
      int sum = d;

      if (!visited[rem][sum]) {
        visited[rem][sum] = true;
        parent[rem][sum] = {0, 0, d};  // Исходное (фиктивное) состояние (0, 0)
        states_current_len.push_back({rem, sum});

        // Быстрое возвращение для случая, когда решение состоит из одной цифры
        if (rem == 0 && sum == n) {
          return std::to_string(d);
        }
      }
    }
  }

  // 2. Итеративный поиск (Длина = 2, 3, ...)
  // Максимально возможное количество цифр для n=180 составляет 20
  const int max_digits = (n + 8) / 9;

  for (int len = 2; len <= max_digits; ++len) {
    states_next_len.clear();  // Очищаем для нового уровня

    // Перебираем все состояния, достигнутые на предыдущем уровне (len - 1)
    for (const auto& state : states_current_len) {
      int rem = state.first;
      int sum = state.second;

      // Перебираем следующую добавляемую цифру d от 0 до 9
      // (d=0 допускается, так как это не первая цифра)
      for (int d = 0; d <= 9; ++d) {
        int new_sum = sum + d;

        if (new_sum <= n) {
          int new_rem = (rem * 10 + d) % n;

          // Условие BFS/DP: если это состояние уже было достигнуто ранее,
          // мы его пропускаем, так как оно было достигнуто более коротким
          // путем.
          if (!visited[new_rem][new_sum]) {
            visited[new_rem][new_sum] = true;
            parent[new_rem][new_sum] = {rem, sum, d};
            states_next_len.push_back({new_rem, new_sum});

            // Проверка целевого состояния
            if (new_rem == 0 && new_sum == n) {
              return ReconstructNumber(n, parent);
            }
          } else {
            // Важный момент для DP/BFS: если состояние уже посещено,
            // это гарантирует, что оно было посещено кратчайшим путем,
            // поэтому мы не обновляем родителя и не добавляем в очередь.
            // Однако, чтобы найти лексикографически наименьшее число,
            // можно было бы рассмотреть случай, если текущий путь такой же
            // длины, но с меньшей цифрой (d) на последнем шаге. Но в нашем
            // случае (итерация по длине, затем по d=0..9) это уже
            // обрабатывается естественным образом.
          }
        }
      }
    }

    // Переходим на следующий уровень
    states_current_len = states_next_len;

    if (states_current_len.empty()) {
      // Если на следующем уровне не удалось достичь ни одного состояния
      break;
    }
  }

  return "Solution not found.";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n;
  std::cout << "Введите число N: ";
  if (!(std::cin >> n)) {
    return 1;
  }

  if (n <= 0 || n > 180) {
    std::cout << "N должно быть в диапазоне [1, 180].\n";
    return 0;
  }

  std::string result = SolveDP(n);

  std::cout << "Наименьшее число, кратное " << n << " с суммой цифр " << n
            << " (DP):\n";
  std::cout << result << "\n";

  return 0;
}