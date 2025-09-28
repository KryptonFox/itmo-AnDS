#include <iostream>

const int MAX_RATING = 100;

int main() {
  int n;
  std::cin >> n;

  int ratings[n];
  for (int i = 0; i < n; i++) {
    std::cin >> ratings[i];
  }

  /*
  Индекс числа n в отсорт. массиве = сумма кол-в чисел от 1 до n
  т.к. если есть несколько возможных позиций — выбераем самую правую
  */
  int count[MAX_RATING + 1];
  for (int i = 0; i <= MAX_RATING; i++) {
    count[i] = 0;
  }

  int index = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 1; j <= ratings[i]; j++) index += count[j];
    std::cout << index << " ";
    index = 0;
    count[ratings[i]]++;
  }
}