#include <cstdint>
#include <iostream>

struct Core {
  int cost;
  int free_at;
};

void Swap(Core &a, Core &b) {
  Core t = a;
  a = b;
  b = t;
}

bool ComapareCost(Core &a, Core &b) { return a.cost < b.cost; }
bool ComapareFreeAt(Core &a, Core &b) { return a.free_at < b.free_at; }

void SiftUp(int i, Core heap[], int &heap_size, bool (*cmp)(Core &a, Core &b)) {
  while (cmp(heap[i], heap[(i - 1) / 2])) {
    Swap(heap[i], heap[(i - 1) / 2]);
    i = (i - 1) / 2;
  }
}

void SiftDown(int i, Core heap[], int &heap_size,
              bool (*cmp)(Core &a, Core &b)) {
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

Core ExtractMin(Core heap[], int &heap_size, bool (*cmp)(Core &a, Core &b)) {
  Core min = heap[0];
  Swap(heap[0], heap[--heap_size]);
  SiftDown(0, heap, heap_size, cmp);
  return min;
}

void Insert(Core key, Core heap[], int &heap_size,
            bool (*cmp)(Core &a, Core &b)) {
  heap[heap_size] = key;
  SiftUp(heap_size, heap, heap_size, cmp);
  ++heap_size;
}

void BuildHeap(Core heap[], int &heap_size, bool (*cmp)(Core &a, Core &b)) {
  for (int i = (heap_size - 1) / 2; i >= 0; i--) {
    SiftDown(i, heap, heap_size, cmp);
  }
}

int main() {
  int n, m;
  std::cin >> n >> m;

  Core *free_cores = new Core[n];
  Core *busy_cores = new Core[n];

  int free_cores_heap_size = n;
  int busy_cores_heap_size = 0;

  int a;
  for (int i = 0; i < n; ++i) {
    std::cin >> a;
    free_cores[i] = Core{a};
  }

  BuildHeap(free_cores, free_cores_heap_size, ComapareCost);

  uint64_t t, f;
  uint64_t sum = 0;
  for (int j = 0; j < m; ++j) {
    std::cin >> t >> f;

    while (busy_cores_heap_size && busy_cores[0].free_at <= t) {
      Insert(ExtractMin(busy_cores, busy_cores_heap_size, ComapareFreeAt),
             free_cores, free_cores_heap_size, ComapareCost);
    }

    if (!free_cores_heap_size)
      continue;
    Core core = ExtractMin(free_cores, free_cores_heap_size, ComapareCost);

    sum += core.cost * f;
    core.free_at = t + f;

    Insert(core, busy_cores, busy_cores_heap_size, ComapareFreeAt);
  }

  std::cout << sum << std::endl;
}
