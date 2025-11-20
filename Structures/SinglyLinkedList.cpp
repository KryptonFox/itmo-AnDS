#include <cstddef>
#include <functional>
#include <iostream>
#include <optional>

template <typename T> class Node {
public:
  Node(T value, Node<T> *next = nullptr) : value(value), next_(next) {};

  void SetNext(Node<T> *next) { next_ = next; }
  Node<T> *GetNext() const { return next_; };

  T value;

private:
  Node<T> *next_;
};

template <typename T> class LinkedList {
  template <typename U>
  friend std::ostream &operator<<(std::ostream &os, LinkedList<U> &list);

public:
  ~LinkedList() {
    Node<T> *cur = head_;
    Node<T> *next;
    while (cur != nullptr) {
      next = cur->GetNext();
      delete cur;
      cur = next;
    };
  };

  void PushFront(T value) {
    Node<T> *new_node = new Node<T>{value, head_};
    head_ = new_node;
    if (tail_ == nullptr) {
      tail_ = new_node;
    }
  }

  void PushBack(T value) {
    if (tail_ == nullptr) {
      return PushFront(value);
    }
    Node<T> *new_node = new Node{value};
    tail_->SetNext(new_node);
    tail_ = new_node;
  };

  void PopFront() {
    Node<T> *to_delete = head_;
    if (to_delete == nullptr) {
      return;
    }

    head_ = head_->GetNext();
    delete to_delete;
  };

  void Delete(size_t index) {
    int i = 0;
    Node<T> *prev = head_;
    for (int i = 0; i < index - 1; ++i) {
      prev = prev->GetNext();
      if (prev->GetNext() == nullptr) {
        throw -1;
      }
    };

    Node<T> *to_delete = prev->GetNext();
    prev->SetNext(prev->GetNext()->GetNext());
  };

  std::optional<T> Find(std::function<bool(const T &)> predicate) const {
    Node<T> *cur = head_;
    while (cur != nullptr) {
      if (predicate(cur->value)) {
        return cur->value;
      }
      cur = cur->GetNext();
    };
    return {};
  };

  T &operator[](size_t index) const {
    Node<T> *cur = head_;
    for (int i = 0; i < index; ++i) {
      cur = cur->GetNext();
      if (cur == nullptr) {
        throw -1;
      }
    };
    return cur->value;
  };

  bool IsEmpty() const { return head_ == nullptr; }

  T &First() const {
    if (IsEmpty()) {
      throw -1;
    }
    return head_->value;
  }

  T &Last() const {
    if (IsEmpty()) {
      throw -1;
    }
    return tail_->value;
  }

private:
  Node<T> *head_ = nullptr;
  Node<T> *tail_ = nullptr;
};

template <typename T>
std::ostream &operator<<(std::ostream &os, LinkedList<T> &list) {
  Node<T> *cur = list.head_;
  while (cur != nullptr) {
    os << cur->value << " ";
    cur = cur->GetNext();
  };
  return os;
}

int main() {
  LinkedList<int> list;

  list.PushBack(1);
  list.PushBack(2);

  list.PopFront();

  list.PushFront(12);
  list.PushFront(11);
  list.PushFront(10);

  auto finded = list.Find([](int a) { return a % 2 == 0; });

  if (finded.has_value()) {
    std::cout << finded.value() << std::endl;
  }

  std::cout << list.First() << " " << list.Last() << std::endl;

  std::cout << list << std::endl;
}
