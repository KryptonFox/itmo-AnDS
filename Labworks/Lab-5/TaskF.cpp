#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct Node {
  int data;
  Node *left;
  Node *right;
  int width;
  int height;
};

class BinarySearchTree {
public:
  ~BinarySearchTree() { Clear(root_); }

  void Insert(int value) { root_ = Insert(root_, value); }

  void PrintVisualization() {
    if (!root_)
      return;

    ComputeSize(root_);

    std::vector<std::string> canvas(root_->height,
                                    std::string(root_->width, ' '));
    DrawOnCanvas(root_, canvas, 0, 0);

    for (const auto &line : canvas) {
      size_t last = line.find_last_not_of(' ');
      if (last != std::string::npos) {
        std::cout << line.substr(0, last + 1) << "\n";
      } else {
        std::cout << "\n";
      }
    }
  }

private:
  Node *root_ = nullptr;

  Node *Insert(Node *node, int value) {
    if (node == nullptr) {
      return new Node{value, nullptr, nullptr, 0, 0};
    }
    if (value < node->data) {
      node->left = Insert(node->left, value);
    } else if (value > node->data) {
      node->right = Insert(node->right, value);
    }
    return node;
  }

  void ComputeSize(Node *node) {
    if (!node)
      return;
    ComputeSize(node->left);
    ComputeSize(node->right);

    std::string s = std::to_string(node->data);
    int lw = node->left ? node->left->width : 0;
    int rw = node->right ? node->right->width : 0;
    int lh = node->left ? node->left->height : 0;
    int rh = node->right ? node->right->height : 0;

    node->width = lw + static_cast<int>(s.length()) + rw;
    node->height = 1 + std::max(lh, rh);
  }

  void DrawOnCanvas(Node *node, std::vector<std::string> &canvas, int row,
                    int col) {
    if (!node)
      return;

    std::string s = std::to_string(node->data);
    int lw = node->left ? node->left->width : 0;

    for (size_t i = 0; i < s.length(); ++i) {
      canvas[row][col + lw + i] = s[i];
    }

    DrawOnCanvas(node->left, canvas, row + 1, col);
    DrawOnCanvas(node->right, canvas, row + 1,
                 col + lw + static_cast<int>(s.length()));
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

  BinarySearchTree tree;
  int x;
  while (std::cin >> x) {
    tree.Insert(x);
  }

  tree.PrintVisualization();

  return 0;
}
