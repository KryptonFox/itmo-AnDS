#include <iostream>

struct Node {
  int value;
  Node *next;
};

class Stack {
public:
  ~Stack() {
    Node *cur = head_;
    Node *next;
    while (cur != nullptr) {
      next = cur->next;
      delete cur;
      cur = next;
    };
  };

  void Push(int value) {
    ++size;
    Node *new_node = new Node{value};
    if (head_ == nullptr) {
      head_ = new_node;
      tail_ = new_node;
      return;
    }
    new_node->next = head_;
    head_ = new_node;
  };

  int Pop() {
    --size;
    int value = head_->value;

    Node *to_delete = head_;
    head_ = head_->next;
    delete to_delete;

    if (head_ == nullptr) {
      tail_ = nullptr;
    }

    return value;
  };

  int Peek() { return head_->value; }

  int size = 0;

private:
  Node *head_ = nullptr;
  Node *tail_ = nullptr;
};

int main() {
  int k;
  std::cin >> k;

  std::string origin_key;
  std::cin >> origin_key;
  int n = origin_key.size();

  Stack stack;
  for (int i = 0; i < n; i++) {
    while (stack.size && stack.Peek() < (origin_key[i] - '0') &&
           (stack.size + n - i) > k) {
      stack.Pop();
    }
    if (stack.size < k) {
      stack.Push(origin_key[i] - '0');
    }
  }

  Stack reversed;
  while (stack.size) {
    reversed.Push(stack.Pop());
  }
  while (reversed.size) {
    std::cout << reversed.Pop();
  }
  return 0;
}