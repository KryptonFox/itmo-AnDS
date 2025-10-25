#include <iostream>
#include <ostream>

const int kMaxTime = 65000;
const int kMaxBlocks = 30000;
const int kL = 10 * 60;

struct Block {
  int number;
  int free_at;
};

void Swap(Block &a, Block &b) {
  Block t = a;
  a = b;
  b = t;
}

bool ComapareNumber(Block &a, Block &b) { return a.number < b.number; }
bool ComapareFreeAt(Block &a, Block &b) { return a.free_at < b.free_at; }

void SiftUp(int i, Block heap[], int &heap_size,
            bool (*cmp)(Block &a, Block &b)) {
  while (cmp(heap[i], heap[(i - 1) / 2])) {
    Swap(heap[i], heap[(i - 1) / 2]);
    i = (i - 1) / 2;
  }
}

void SiftDown(int i, Block heap[], int &heap_size,
              bool (*cmp)(Block &a, Block &b)) {
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

Block ExtractMin(Block heap[], int &heap_size,
                 bool (*cmp)(Block &a, Block &b)) {
  Block min = heap[0];
  Swap(heap[0], heap[--heap_size]);
  SiftDown(0, heap, heap_size, cmp);
  return min;
}

void Insert(Block key, Block heap[], int &heap_size,
            bool (*cmp)(Block &a, Block &b)) {
  heap[heap_size++] = key;
  SiftUp(heap_size - 1, heap, heap_size, cmp);
}

void BuildHeap(Block heap[], int &heap_size, bool (*cmp)(Block &a, Block &b)) {
  for (int i = (heap_size - 1) / 2; i >= 0; i--) {
    SiftDown(i, heap, heap_size, cmp);
  }
}

int main() {
  Block *free_blocks = new Block[kMaxBlocks];
  Block *busy_blocks = new Block[kMaxBlocks];

  int free_blocks_heap_size = kMaxBlocks;
  int busy_blocks_heap_size = 0;

  for (int i = 0; i < kMaxBlocks; ++i) {
    free_blocks[i] = Block{i + 1};
  }

  int time;
  char op;
  int block_number;

  while (std::cin >> time) {
    std::cin >> op;

    while (busy_blocks_heap_size && busy_blocks[0].free_at <= time) {
      Insert(ExtractMin(busy_blocks, busy_blocks_heap_size, ComapareFreeAt),
             free_blocks, free_blocks_heap_size, ComapareNumber);
    }

    if (op == '.') {
      std::cin >> block_number;
      bool successful = false;
      for (int i = 0; i < busy_blocks_heap_size; ++i) {
        if (busy_blocks[i].number == block_number) {
          busy_blocks[i].free_at = time + kL;
          SiftDown(i, busy_blocks, busy_blocks_heap_size, ComapareFreeAt);
          successful = true;
          std::cout << '+' << std::endl;
          break;
        }
      }
      if (!successful) {
        std::cout << '-' << std::endl;
      }
    } else if (op == '+') {
      Block block =
          ExtractMin(free_blocks, free_blocks_heap_size, ComapareNumber);
      std::cout << block.number << std::endl;
      block.free_at = time + kL;
      Insert(block, busy_blocks, busy_blocks_heap_size, ComapareFreeAt);
    }
  }

  delete[] free_blocks;
  delete[] busy_blocks;
}
