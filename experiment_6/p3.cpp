/*
 * @Date: 2019-11-26 19:30:47
 * @Author: creedowl
 * @Description: child-sibling
 */
#include <iostream>
#include <queue>

using namespace std;

class Node {
public:
  int data{0};
  Node *first_child{nullptr}, *next_sibling{nullptr};

  Node(int data, Node *ch = nullptr, Node *si = nullptr)
      : data(data), first_child(ch), next_sibling(si) {}
};

class Tree {
public:
  Node *root{nullptr};

  /**
   * test case
  1
  3 2 3 4
  2 5 6
  2 7 8
  1 9
  0 0 0 0
  1 10
  1 11
  0
   */
  Tree() {
    int value{0};
    queue<Node *> v;
    // root's value
    cin >> value;
    root = new Node{value};
    v.push(root);
    Node *node{nullptr}, *cur{nullptr}, *pre{nullptr};
    int num{0};
    while (!v.empty()) {
      node = v.front();
      v.pop();
      // children num of each node
      cin >> num;
      pre = nullptr;
      for (size_t i = 0; i < num; i++) {
        // child's value
        cin >> value;
        cur = new Node{value};
        if (pre) pre->next_sibling = cur;
        pre = cur;
        v.push(cur);
        if (i == 0) node->first_child = cur;
      }
    }
  }

  ~Tree() { destroy(this->root); }

  void destroy(Node *n) {
    if (!n) return;
    destroy(n->first_child);
    destroy(n->next_sibling);
    delete n;
  }

  void show() {
    queue<Node *> v1, v2;
    v1.push(this->root);
    Node *cur{nullptr};
    int layer{0};
    // add node's all sibling to a queue
    auto add = [](queue<Node *> &v, Node *n) -> void {
      while (n) {
        v.push(n);
        n = n->next_sibling;
      }
    };
    while (!v1.empty() || !v2.empty()) {
      if (!v1.empty()) {
        cout << layer << " ";
        while (!v1.empty()) {
          cur = v1.front();
          v1.pop();
          add(v2, cur->first_child);
          cout << cur->data << " ";
        }
        cout << endl;
        layer++;
      }
      if (!v2.empty()) {
        cout << layer << " ";
        while (!v2.empty()) {
          cur = v2.front();
          v2.pop();
          add(v1, cur->first_child);
          cout << cur->data << " ";
        }
        cout << endl;
        layer++;
      }
    }
  }
};

int main() {
  Tree t{};
  t.show();
}
