#include <iostream>

void Swap(int& a, int& b) {
  int t = a;
  a = b;
  b = t;
}

void SiftUp(int i, int heap[], int& heap_size) {
  while (heap[i] > heap[(i - 1) / 2]) {
    Swap(heap[i], heap[(i - 1) / 2]);
    i = (i - 1) / 2;
  }
}

void SiftDown(int i, int heap[], int& heap_size) {
  int left;
  int right;
  int j;

  while (2 * i + 1 < heap_size) {
    left = j = 2 * i + 1;
    right = 2 * i + 2;
    if (right < heap_size && heap[right] > heap[left]) {
      j = right;
    }
    if (heap[i] >= heap[j]) break;
    Swap(heap[i], heap[j]);
    i = j;
  }
}

void BuildHeap(int heap[], int& heap_size) {
  for (int i = (heap_size - 1) / 2; i >= 0; i--) {
    SiftDown(i, heap, heap_size);
  }
}

void HeapSort(int i, int heap[], int& heap_size) {
  BuildHeap(heap, heap_size);
  while (heap_size > 0) {
    Swap(heap[0], heap[heap_size - 1]);
    SiftDown(0, heap, --heap_size);
  }
}

int main() {
  int n;
  std::cin >> n;

  int heap_size = n;
  int* heap = new int[heap_size];
  for (int i = 0; i < heap_size; i++) std::cin >> heap[i];

  HeapSort(0, heap, heap_size);

  for (int i = 0; i < n; i++) std::cout << heap[i] << " ";
  delete[] heap;
}