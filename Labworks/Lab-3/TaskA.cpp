#include <iostream>

bool IsCorrectInvariantMaxHeap(int heap[], int& heap_size) {
  bool is_correct_invariant = true;
  for (int i = 0; i < heap_size / 2; i++) {
    if (heap[i] > heap[2 * i + 1]) {
      is_correct_invariant = false;
      break;
    }
    if (2 * i + 2 < heap_size && heap[i] > heap[2 * i + 2]) {
      is_correct_invariant = false;
      break;
    }
  }

  return is_correct_invariant;
}

int main() {
  int n;
  std::cin >> n;

  int heap_size = n;
  int* heap = new int[n];
  for (int i = 0; i < n; i++) std::cin >> heap[i];

  bool is_correct_invariant = IsCorrectInvariantMaxHeap(heap, heap_size);

  delete[] heap;

  std::cout << (is_correct_invariant ? "YES" : "NO");
}