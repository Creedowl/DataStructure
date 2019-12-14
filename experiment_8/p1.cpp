/*
 * @Date: 2019-12-11 19:42:02
 * @Author: creedowl
 * @Description: Binary Search Tree (BST)
 */
#include <functional>
#include <iomanip>
#include <iostream>

using namespace std;

template <typename T>
class Node {
public:
  T value;
  Node *left{nullptr}, *right{nullptr};

  Node(T value) : value(value) {}
};

template <typename T>
class BinarySearchTree {
private:
  Node<T> *root{nullptr};

  void insert(Node<T> *&root, T value) {
    if (root == nullptr)
      root = new Node<T>(value);
    else if (value == root->value)
      return;
    else if (value < root->value)
      insert(root->left, value);
    else
      insert(root->right, value);
  }

  bool find(Node<T> *root, T value) {
    if (root == nullptr)
      return false;
    else if (value == root->value)
      return true;
    else if (value < root->value)
      return find(root->left, value);
    else
      return find(root->right, value);
  }

  void preorderTraverse(Node<T> *root,
                        const function<void(Node<T> *)> &callback) const {
    if (root == nullptr) return;
    callback(root);
    preorderTraverse(root->left, callback);
    preorderTraverse(root->right, callback);
  }

  void inorderTraverse(Node<T> *root,
                       const function<void(Node<T> *)> &callback) const {
    if (root == nullptr) return;
    inorderTraverse(root->left, callback);
    callback(root);
    inorderTraverse(root->right, callback);
  }

  void postorderTraverse(Node<T> *root,
                         const function<void(Node<T> *)> &callback) const {
    if (root == nullptr) return;
    postorderTraverse(root->left, callback);
    postorderTraverse(root->right, callback);
    callback(root);
  }

public:
  ~BinarySearchTree() {
    postorderTraverse([](Node<T> *root) { delete root; });
  }

  inline void insert(T value) { insert(this->root, value); }

  void remove(T value) {
    if (this->root == nullptr) return;
    Node<T> *temp{nullptr}, *pre{nullptr}, **cur{&this->root};
    // find the target node
    while (*cur) {
      // found
      if (value == (*cur)->value) {
        // node is leaf
        if ((*cur)->left == nullptr and (*cur)->right == nullptr) {
          delete *cur;
          *cur = nullptr;
        } else if ((*cur)->left == nullptr) {
          // node only has a child
          temp = *cur;
          *cur = temp->right;
          delete temp;
        } else if ((*cur)->right == nullptr) {
          temp = *cur;
          *cur = temp->left;
          delete temp;
        } else {
          // node has two child
          pre = *cur;
          temp = (*cur)->left;
          // find the left child's rightmost node
          while (temp->right) {
            pre = temp;
            temp = temp->right;
          }
          (*cur)->value = temp->value;
          if (pre == *cur)
            pre->left = temp->left;
          else
            pre->right = temp->left;
          delete temp;
        }
        break;
      } else if (value < (*cur)->value)
        cur = &(*cur)->left;
      else
        cur = &(*cur)->right;
    }
  }

  inline bool find(T value) { return find(this->root, value); }

  void preorderTraverse(const function<void(Node<T> *)> &callback) const {
    preorderTraverse(this->root, callback);
  }

  void inorderTraverse(const function<void(Node<T> *)> &callback) const {
    inorderTraverse(this->root, callback);
  }

  void postorderTraverse(const function<void(Node<T> *)> &callback) const {
    postorderTraverse(this->root, callback);
  }
};

int main() {
  BinarySearchTree<int> bst_int{};
  bst_int.insert(9);
  bst_int.insert(7);
  bst_int.insert(8);
  bst_int.insert(2);
  bst_int.insert(1);
  bst_int.insert(3);
  bst_int.insert(5);
  bst_int.insert(4);
  bst_int.insert(12);
  bst_int.insert(10);
  bst_int.insert(11);
  bst_int.insert(0);
  cout << boolalpha << bst_int.find(8) << endl;
  bst_int.inorderTraverse([](Node<int> *root) { cout << root->value << " "; });
  cout << endl;
  bst_int.remove(9);
  cout << boolalpha << bst_int.find(9) << endl;
  bst_int.remove(7);
  bst_int.remove(12);
  bst_int.inorderTraverse([](Node<int> *root) { cout << root->value << " "; });
  cout << endl;
}
