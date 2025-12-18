#include <ios>
#include <iostream>

struct Node {
  int value;
  Node *next;
  Node *prev;
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
    Node *new_node = new Node{value};
    if (head_ == nullptr) {
      head_ = new_node;
      tail_ = new_node;
      return;
    }
    new_node->next = head_;
    head_->prev = new_node;
    head_ = new_node;
  };

  void Push(int value) {
    Node *new_node = new Node{value};
    if (tail_ == nullptr) {
      head_ = new_node;
      tail_ = new_node;
      return;
    }
    new_node->prev = tail_;
    tail_->next = new_node;
    tail_ = new_node;
  };

  int PopBack() {
    int value = tail_->value;

    Node *to_delete = tail_;
    tail_ = tail_->prev;
    delete to_delete;

    if (tail_ == nullptr) {
      head_ = nullptr;
    } else {
      tail_->next = nullptr;
    }

    return value;
  };

  int Pop() {
    int value = head_->value;

    Node *to_delete = head_;
    head_ = head_->next;
    delete to_delete;

    if (head_ == nullptr) {
      tail_ = nullptr;
    } else {
      head_->prev = nullptr;
    }

    return value;
  };

  int Peek() { return head_->value; }
  int Peek() { return tail_->value; }

  void Print() {
    Node *cur = head_;
    while (cur != nullptr) {
      std::cout << cur->value << " ";
      cur = cur->next;
    }
  }

private:
  Node *head_ = nullptr;
  Node *tail_ = nullptr;
};

int main() {
  // std::ios::sync_with_stdio(false);
  // std::cin.tie(nullptr);

  int n, k;
  std::cin >> n >> k;

  Stack deck;

  int a;
  for (int i = 0; i < n; ++i) {
    std::cin >> a;
    deck.Push(a);
  }

  int x, y;
  for (int i = 0; i < k; ++i) {
    x = deck.Peek();
    y = deck.Peek();
    if (x < y) {
      deck.Pop();
      deck.Push((x + y) % (1 << 30));
    } else {
      deck.PopBack();
      deck.Push((y - x) + (1 << 30));
    }
  }
  deck.Print();
}
