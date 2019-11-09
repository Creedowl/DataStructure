/*
 * @Date: 2019-11-02 16:02:51
 * @Author: creedowl
 * @Description: binary tree using c++
 */
#include <cmath>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>

using std::function;
using std::string;

template <typename X>
class Node {
private:
  X data;
  Node *l_child{nullptr}, *r_child{nullptr};

public:
  template <typename T>
  friend class BinaryTree;
  Node() = default;
  Node(X e, Node *l_child = nullptr, Node *r_child = nullptr)
      : data(e), l_child(l_child), r_child(r_child) {}
  ~Node(){};

  X getData() { return this->data; }

  void setData(X value) { this->data = value; }

  Node<X> *getLeftChild() { return this->l_child; }

  Node<X> *getRightChild() { return this->r_child; }
};

template <typename T>
class BinaryTree {
private:
  Node<T> *root{nullptr};
  int depth{0}, nodeNum{0};

  // DEPRECATED
  void preorderTraverse(Node<T> *root,
                        const function<void(Node<T> *)> &callback) const {
    if (root == nullptr) return;
    callback(root);
    preorderTraverse(root->l_child, callback);
    preorderTraverse(root->r_child, callback);
  }

  // DEPRECATED
  void inorderTraverse(Node<T> *root,
                       const function<void(Node<T> *)> &callback) const {
    if (root == nullptr) return;
    inorderTraverse(root->l_child, callback);
    callback(root);
    inorderTraverse(root->r_child, callback);
  }

  // DEPRECATED
  void postorderTraverse(Node<T> *root,
                         const function<void(Node<T> *)> &callback) const {
    if (root == nullptr) return;
    postorderTraverse(root->l_child, callback);
    postorderTraverse(root->r_child, callback);
    callback(root);
  }

public:
  BinaryTree() = default;
  ~BinaryTree() {
    postorderTraverse([](Node<T> *node) -> void { delete node; });
  }

  /*
   * create a binary tree from the given string,
   * use the second attribute to seperate
   */
  void create(std::vector<T> data, T blank) {
    std::queue<Node<T> **> s{{&this->root}};
    Node<T> **root{nullptr};
    int count{0};
    for (auto item : data) {
      if (s.empty()) return;
      root = s.front();
      s.pop();
      count++;
      if (item == blank) continue;
      *root = new Node<T>{item};
      this->nodeNum++;
      s.push(&(*root)->l_child);
      s.push(&(*root)->r_child);
    }
    this->depth = ceil(log(count + 1) / log(2));
  }

  int getDepth() { return this->depth; }

  int getNodeNum() { return this->nodeNum; }

  bool empty() { return this->depth == 0; }

  Node<T> *getRoot() { return this->root; }

  Node<T> *getParent(Node<T> *node) {
    Node<T> *parent{nullptr};
    preorderTraverse([&](Node<T> *n) -> void {
      if (n->getLeftChild() == node or n->getRightChild() == node) parent = n;
    });
    return parent;
  }

  Node<T> *getLeftSibling(Node<T> *node) {
    Node<T> *leftSibling{nullptr};
    preorderTraverse([&](Node<T> *n) -> void {
      if (n->getRightChild() == node) leftSibling = n->getLeftChild();
    });
    return leftSibling;
  }

  Node<T> *getRightSibling(Node<T> *node) {
    Node<T> *rightSibling{nullptr};
    preorderTraverse([&](Node<T> *n) -> void {
      if (n->getLeftChild() == node) rightSibling = n->getLeftChild();
    });
    return rightSibling;
  }

  void insertChild(Node<T> *pos, int lr, BinaryTree<T> &node) {
    if (lr == 0) {
      node.getRoot()->r_child = pos->l_child;
      pos->l_child = node.getRoot();
    } else {
      node.getRoot()->r_child = pos->r_child;
      pos->r_child = node.getRoot();
    }
    this->depth += node.depth - 1;
    this->nodeNum += node.nodeNum;
    node.root = nullptr;
    node.~BinaryTree();
  }

  inline int calcDepth(Node<T> *node) {
    if (node == nullptr) return 0;
    return std::max(calcDepth(node->getLeftChild()),
                    calcDepth(node->getRightChild())) + 1;
  }

  void deleteChild(Node<T> *pos, int lr) {
    Node<T> *root{nullptr};
    int count{0};
    if (lr == 0) {
      root = pos->l_child;
      pos->l_child = nullptr;
    } else {
      root = pos->r_child;
      pos->r_child = nullptr;
    }
    postorderTraverse(root, [&](Node<T> *node) -> void {
      delete node;
      count++;
    });
    this->nodeNum -= count;
    this->depth = calcDepth(this->root);
  }

  // p3
  void deleteElemAndChild(T value) {
    Node<T> *root{nullptr};
    std::queue<Node<T> *> q{{this->root}};
    while (!q.empty()) {
      root = q.front();
      q.pop();
      if (root->l_child and root->l_child->getData() == value) {
        deleteChild(root, 0);
        root->l_child = nullptr;
      }
      if (root->l_child and root->r_child->getData() == value) {
        deleteChild(root, 1);
        root->r_child = nullptr;
      }
      if (root->l_child != nullptr) q.push(root->l_child);
      if (root->r_child != nullptr) q.push(root->r_child);
    }
  }

  // get a value to a node
  T value(Node<T> *node) { return node->getData(); }

  // assign a value to a node
  void assign(Node<T> *node, T value) { node->setData(value); }

  // DEPRECATED
  void preorderTraverse_recursive(
      const function<void(Node<T> *)> &callback) const {
    preorderTraverse(this->root, callback);
  }

  void preorderTraverse(const function<void(Node<T> *)> &callback) const {
    std::stack<Node<T> *> s{{this->root}};
    Node<T> *node{nullptr};
    while (!s.empty()) {
      node = s.top();
      s.pop();
      callback(node);
      if (node->r_child) s.push(node->r_child);
      if (node->l_child) s.push(node->l_child);
    }
  }

  // DEPRECATED
  void inorderTraverse_recursive(
      const function<void(Node<T> *)> &callback) const {
    inorderTraverse(this->root, callback);
  }

  void inorderTraverse(const function<void(Node<T> *)> &callback) const {
    std::stack<std::pair<Node<T> *, bool>> s{
        {std::make_pair(this->root, false)}};
    Node<T> *node{nullptr};
    bool visited{false};
    while (!s.empty()) {
      node = s.top().first;
      visited = s.top().second;
      if (!visited and node->l_child) {
        s.top().second = true;
        s.push(std::make_pair(node->l_child, false));
      } else {
        s.pop();
        callback(node);
        if (node->r_child) {
          s.push(std::make_pair(node->r_child, false));
        }
      }
    }
  }

  // DEPRECATED
  void postorderTraverse_recursive(
      const function<void(Node<T> *)> &callback) const {
    postorderTraverse(this->root, callback);
  }

  void postorderTraverse(const function<void(Node<T> *)> &callback) const {
    if (!this->root) return;
    std::stack<std::pair<Node<T> *, std::pair<bool, bool>>> s{
        {std::make_pair(this->root, std::make_pair(false, false))}};
    Node<T> *node{nullptr};
    bool l_visited{false}, r_visited{false};
    while (!s.empty()) {
      node = s.top().first;
      l_visited = s.top().second.first;
      r_visited = s.top().second.second;
      if (!l_visited and node->l_child) {
        s.top().second.first = true;
        s.push(std::make_pair(node->l_child, std::make_pair(false, false)));
      } else if (!r_visited and node->r_child) {
        s.top().second.second = true;
        s.push(std::make_pair(node->r_child, std::make_pair(false, false)));
      } else {
        s.pop();
        callback(node);
      }
    }
  }

  void levelOrderTraverse(const function<void(Node<T> *)> &callback) const {
    Node<T> *root{nullptr};
    std::queue<Node<T> *> q{{this->root}};
    while (!q.empty()) {
      root = q.front();
      q.pop();
      callback(root);
      if (root->l_child != nullptr) q.push(root->l_child);
      if (root->r_child != nullptr) q.push(root->r_child);
    }
  }

  // check if it's a complete binary tree
  bool isCompleteBiTree() {
    if (this->root == nullptr) return true;
    bool leaf = false;
    Node<T> *node{nullptr};
    std::queue<Node<T> *> q{{this->root}};
    while (!q.empty()) {
      node = q.front();
      q.pop();
      if (node->l_child == nullptr and node->r_child != nullptr) return false;
      if (leaf and (node->l_child != nullptr or node->r_child != nullptr))
        return false;
      if (node->l_child) q.push(node->l_child);
      if (node->r_child)
        q.push(node->r_child);
      else
        leaf = true;
    }
    return true;
  }
};

int main() {
  BinaryTree<int> biTree, b2;
  // biTree.create({1, 2, 3, 4, 5, 6, -1, 7, -1, -1, 8, -1, 20}, -1);
  // b2.create({9, 10, -1, 11}, -1);
  b2.create({1, 2, 3, -1, 4}, -1);
  // biTree.insertChild(biTree.getRoot()->getLeftChild()->getRightChild(), 1,
  // b2);
  auto show = [](Node<int> *n) -> void { std::cout << n->getData() << " "; };
  b2.levelOrderTraverse(show);
  std::cout << std::endl;
  // b2.deleteElemAndChild(3);
  // b2.levelOrderTraverse(show);
  // std::cout << std::endl;
  std::cout << b2.isCompleteBiTree() << std::endl;
  // biTree.preorderTraverse(show);
  // std::cout << std::endl;
  // biTree.inorderTraverse(show);
  // std::cout << std::endl;
  // biTree.postorderTraverse(show);
  // std::cout << std::endl;
  // biTree.postorderTraverse_recursive(show);
  // std::cout << std::endl;
  // std::cout << biTree.getDepth() << std::endl;
  // std::cout << biTree.getNodeNum() << std::endl;
  // biTree.deleteChild(biTree.getRoot()->getLeftChild()->getRightChild(), 1);
  // biTree.postorderTraverse(show);
  // std::cout << std::endl;
  // std::cout << biTree.getDepth() << std::endl;
  // std::cout << biTree.getNodeNum() << std::endl;
  // biTree.deleteChild
  // auto node = biTree.getRoot()->getLeftChild()->getRightChild();
  // std::cout << biTree.getParent(node)->getData() << std::endl;
  // std::cout << biTree.getLeftSibling(node)->getData() << std::endl;
  // biTree.create("123456_7#");
  // BinaryTree<char> biTree;
  // biTree.create({'a', 'b', 'c', '2', '_', '_', 'e', '_', 'f'}, '_');
}
