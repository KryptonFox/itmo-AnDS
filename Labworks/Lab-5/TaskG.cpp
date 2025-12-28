#include <algorithm>
#include <iostream>
#include <string>

struct Node {
  int data;
  int height;
  Node *left;
  Node *right;
};

class AvlTree {
public:
  ~AvlTree() { Clear(root_); }

  void Insert(int x) {
    if (!Exists(x)) {
      root_ = Insert(root_, x);
    }
  }

  void Delete(int x) {
    if (Exists(x)) {
      root_ = Delete(root_, x);
    }
  }

  bool Exists(int x) const {
    Node *curr = root_;
    while (curr) {
      if (curr->data == x)
        return true;
      curr = (x < curr->data) ? curr->left : curr->right;
    }
    return false;
  }

  void Next(int x) const {
    Node *curr = root_;
    Node *successor = nullptr;
    while (curr) {
      if (curr->data > x) {
        successor = curr;
        curr = curr->left;
      } else {
        curr = curr->right;
      }
    }
    if (successor)
      std::cout << successor->data << "\n";
    else
      std::cout << "none\n";
  }

  void Prev(int x) const {
    Node *curr = root_;
    Node *predecessor = nullptr;
    while (curr) {
      if (curr->data < x) {
        predecessor = curr;
        curr = curr->right;
      } else {
        curr = curr->left;
      }
    }
    if (predecessor)
      std::cout << predecessor->data << "\n";
    else
      std::cout << "none\n";
  }

private:
  Node *root_ = nullptr;

  int GetHeight(Node *n) const { return n ? n->height : 0; }

  int GetBalance(Node *n) const {
    return n ? GetHeight(n->left) - GetHeight(n->right) : 0;
  }

  void UpdateHeight(Node *n) {
    if (n) {
      n->height = 1 + std::max(GetHeight(n->left), GetHeight(n->right));
    }
  }

  Node *RotateRight(Node *p) {
    Node *q = p->left;
    p->left = q->right;
    q->right = p;
    UpdateHeight(p);
    UpdateHeight(q);
    return q;
  }

  Node *RotateLeft(Node *p) {
    Node *q = p->right;
    p->right = q->left;
    q->left = p;
    UpdateHeight(p);
    UpdateHeight(q);
    return q;
  }

  Node *Balance(Node *n) {
    UpdateHeight(n);
    int balance = GetBalance(n);

    if (balance > 1) {
      if (GetBalance(n->left) < 0)
        n->left = RotateLeft(n->left);
      return RotateRight(n);
    }
    if (balance < -1) {
      if (GetBalance(n->right) > 0)
        n->right = RotateRight(n->right);
      return RotateLeft(n);
    }
    return n;
  }

  Node *Insert(Node *n, int x) {
    if (!n)
      return new Node{x, 1, nullptr, nullptr};
    if (x < n->data)
      n->left = Insert(n->left, x);
    else
      n->right = Insert(n->right, x);
    return Balance(n);
  }

  Node *FindMin(Node *n) { return n->left ? FindMin(n->left) : n; }

  Node *DeleteMin(Node *n) {
    if (!n->left) {
      return n->right;
    };
    n->left = DeleteMin(n->left);
    return Balance(n);
  }

  Node *Delete(Node *n, int x) {
    if (!n) {
      return nullptr;
    };
    if (x < n->data) {
      n->left = Delete(n->left, x);
    } else if (x > n->data) {
      n->right = Delete(n->right, x);
    } else {
      Node *l = n->left;
      Node *r = n->right;
      delete n;

      if (!r) {
        return l;
      }
      Node *min = FindMin(r);
      min->right = DeleteMin(r);
      min->left = l;
      return Balance(min);
    }
    return Balance(n);
  }

  void Clear(Node *n) {
    if (!n) {
      return;
    }
    Clear(n->left);
    Clear(n->right);
    delete n;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  AvlTree tree;
  std::string cmd;
  int x;

  while (std::cin >> cmd >> x) {
    if (cmd == "insert")
      tree.Insert(x);
    else if (cmd == "delete")
      tree.Delete(x);
    else if (cmd == "exists")
      std::cout << (tree.Exists(x) ? "true\n" : "false\n");
    else if (cmd == "next")
      tree.Next(x);
    else if (cmd == "prev")
      tree.Prev(x);
  }

  return 0;
}
