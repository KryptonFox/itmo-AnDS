#include <cstring>
#include <iostream>

struct Elem {
  int value;
  bool deleted = false;
};

void Swap(Elem *&a, Elem *&b) {
  Elem *t = a;
  a = b;
  b = t;
}

bool CompareMin(Elem *a, Elem *b) { return a->value < b->value; }
bool CompareMax(Elem *a, Elem *b) { return a->value > b->value; }

void SiftUp(int i, Elem *heap[], int &heap_size,
            bool (*cmp)(Elem *a, Elem *b)) {
  while (cmp(heap[i], heap[(i - 1) / 2])) {
    Swap(heap[i], heap[(i - 1) / 2]);
    i = (i - 1) / 2;
  }
}

void SiftDown(int i, Elem *heap[], int &heap_size,
              bool (*cmp)(Elem *a, Elem *b)) {
  int left;
  int right;
  int j;

  while (2 * i + 1 < heap_size) {
    left = j = 2 * i + 1;
    right = 2 * i + 2;
    if (right < heap_size && cmp(heap[right], heap[left])) {
      j = right;
    }
    if (cmp(heap[i], heap[j]))
      break;
    Swap(heap[i], heap[j]);
    i = j;
  }
}

int Extract(Elem *heap[], int &heap_size, bool (*cmp)(Elem *a, Elem *b)) {
  Elem *min = heap[0];
  Swap(heap[0], heap[--heap_size]);
  SiftDown(0, heap, heap_size, cmp);

  if (min->deleted) {
    delete min;
    return Extract(heap, heap_size, cmp);
  }
  min->deleted = true;

  return min->value;
}

void Insert(Elem *key, Elem *heap[], int &heap_size,
            bool (*cmp)(Elem *a, Elem *b)) {
  heap[heap_size++] = key;
  SiftUp(heap_size - 1, heap, heap_size, cmp);
}

void BuildHeap(Elem *heap[], int &heap_size, bool (*cmp)(Elem *a, Elem *b)) {
  for (int i = (heap_size - 1) / 2; i >= 0; i--) {
    SiftDown(i, heap, heap_size, cmp);
  }
}

int ParseInsertNumber(const char *s) {
  char buf[100];
  int i = 0;
  s += 7;
  while (*s != ')') {
    buf[i++] = *s;
    ++s;
  }
  buf[i] = '\0';
  return std::stoi(buf);
}

int main() {
  int q;
  std::cin >> q;

  Elem **min_heap = new Elem *[q + 1];
  Elem **max_heap = new Elem *[q + 1];

  int min_heap_size = 0;
  int max_heap_size = 0;

  char command[200];

  Elem *n;
  while (q--) {
    std::cin >> command;
    if (strcmp(command, "GetMin") == 0) {
      std::cout << Extract(min_heap, min_heap_size, CompareMin) << std::endl;
    } else if (strcmp(command, "GetMax") == 0) {
      std::cout << Extract(max_heap, max_heap_size, CompareMax) << std::endl;
    } else if (strncmp(command, "Insert", 6) == 0) {
      n = new Elem{ParseInsertNumber(command)};
      Insert(n, min_heap, min_heap_size, CompareMin);
      Insert(n, max_heap, max_heap_size, CompareMax);
    }
  }

  delete[] min_heap;
  delete[] max_heap;
}
