/*
 * @Date: 2019-11-25 14:03:23
 * @Author: creedowl
 * @Description: huffman tree
 */
#include <iostream>
#include <queue>
// #include <vector>

using namespace std;

// Huffman tree
class HT {
public:
  int weight;
  string data;
  HT *lchild, *rchild;

  HT() = default;

  HT(int weight, string data, HT *lchild = nullptr, HT *rchild = nullptr)
      : weight(weight), data(data), lchild(lchild), rchild(rchild) {}
};

void destroy(HT *root) {
  if (root == nullptr) return;
  destroy(root->lchild);
  destroy(root->rchild);
  delete root;
}

void show(HT *root, string pos = "") {
  if (root->lchild->data != "")
    cout << pos << "0 " << root->lchild->data << endl;
  if (root->rchild->data != "")
    cout << pos << "1 " << root->rchild->data << endl;
  if (root->lchild->data == "") show(root->lchild, pos + "0");
  if (root->rchild->data == "") show(root->rchild, pos + "1");
}

int main() {
  int n;
  cin >> n;
  auto cmp = [](const HT *a, const HT *b) -> bool {
    return a->weight > b->weight;
  };
  priority_queue<HT *, vector<HT *>, decltype(cmp)> q(cmp);
  int weight;
  string data;
  for (size_t i = 0; i < n; i++) {
    cin >> weight >> data;
    q.push(new HT{weight, data});
  }

  HT *n1, *n2, *new_node;
  while (true) {
    n1 = q.top();
    q.pop();
    /* if n1 is the last element in the queue,
     * the building of the huffman tree is over
     */
    if (q.empty()) {
      show(n1);
      destroy(n1);
      break;
    }
    n2 = q.top();
    q.pop();
    new_node = new HT{n1->weight + n2->weight, "", n1, n2};
    q.push(new_node);
  }
}
