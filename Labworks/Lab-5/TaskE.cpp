#include <iostream>

struct Node {
  int data;
  int size;
  Node *left;
  Node *right;
};

class BinarySearchTree {
public:
  ~BinarySearchTree() { Clear(root_); }

  void Insert(int x) {
    if (!Contains(root_, x)) {
      root_ = Insert(root_, x);
    }
  }

  int GetKth(int k) const { return FindKth(root_, k); }

private:
  Node *root_ = nullptr;

  int GetSize(Node *node) const { return node ? node->size : 0; }

  void UpdateSize(Node *node) {
    if (node) {
      node->size = 1 + GetSize(node->left) + GetSize(node->right);
    }
  }

  Node *Insert(Node *node, int x) {
    if (node == nullptr) {
      return new Node{x, 1, nullptr, nullptr};
    }

    if (x < node->data) {
      node->left = Insert(node->left, x);
    } else if (x > node->data) {
      node->right = Insert(node->right, x);
    }

    UpdateSize(node);
    return node;
  }

  bool Contains(Node *node, int x) const {
    while (node) {
      if (node->data == x)
        return true;
      node = (x < node->data) ? node->left : node->right;
    }
    return false;
  }

  int FindKth(Node *node, int k) const {
    int left_size = GetSize(node->left);

    if (k <= left_size) {
      return FindKth(node->left, k);
    }
    if (k == left_size + 1) {
      return node->data;
    }
    return FindKth(node->right, k - left_size - 1);
  }

  void Clear(Node *node) {
    if (!node)
      return;
    Clear(node->left);
    Clear(node->right);
    delete node;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  BinarySearchTree router;
  char type;
  int val;

  while (std::cin >> type >> val) {
    if (type == '+') {
      router.Insert(val);
    } else if (type == '?') {
      std::cout << router.GetKth(val) << "\n";
    }
  }
}
