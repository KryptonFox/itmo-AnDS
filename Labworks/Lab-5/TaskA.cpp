#include <ios>
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

  void PushFront(int value) {
    Node *new_node = new Node{value};
    if (tail_ == nullptr) {
      head_ = new_node;
      tail_ = new_node;
      return;
    }
    tail_->next = new_node;
    tail_ = new_node;
  };

  int PopFront() {
    int value = head_->value;

    Node *to_delete = head_;
    head_ = head_->next;
    delete to_delete;

    if (head_ == nullptr) {
      tail_ = nullptr;
    }

    return value;
  };

private:
  Node *head_ = nullptr;
  Node *tail_ = nullptr;
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  Stack queue;

  char op;
  int x;
  for (int i = 0; i < n; ++i) {
    std::cin >> op;
    if (op == '+') {
      std::cin >> x;
      queue.PushFront(x);
    } else if (op == '-') {
      std::cout << queue.PopFront() << '\n';
    }
  }
}
