/*
 * @Date: 2019-12-29 16:12:35
 * @Author: creedowl
 * @Description: Huffman encode and decode
 */
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

typedef unsigned int bin;

class HT {
public:
  int weight;
  char data{'\0'};
  HT *lchild, *rchild;

  HT() = default;

  HT(int weight, char data, HT *lchild = nullptr, HT *rchild = nullptr)
      : weight(weight), data(data), lchild(lchild), rchild(rchild) {}
};

void destroy(HT *root) {
  if (root == nullptr) return;
  destroy(root->lchild);
  destroy(root->rchild);
  delete root;
}

// show encoding, header is char, ascii, frequence and code
void show(HT *root, vector<int> &fre, string pos = "") {
  if (root->lchild->data != '\0')
    cout << root->lchild->data << " " << int(root->lchild->data) << " "
         << fre[root->lchild->data] << " " << pos << "0 " << endl;
  if (root->rchild->data != '\0')
    cout << root->rchild->data << " " << int(root->rchild->data) << " "
         << fre[root->rchild->data] << " " << pos << "1 " << endl;
  if (root->lchild->data == '\0') show(root->lchild, fre, pos + "0");
  if (root->rchild->data == '\0') show(root->rchild, fre, pos + "1");
}

// encode from a huffman tree
void encode(HT *root, vector<string> &codes, string code = "") {
  if (root->lchild->data != '\0') codes[root->lchild->data] = code + "0";
  if (root->rchild->data != '\0') codes[root->rchild->data] = code + "1";
  if (root->lchild->data == '\0') encode(root->lchild, codes, code + "0");
  if (root->rchild->data == '\0') encode(root->rchild, codes, code + "1");
}

// build a huffman tree
HT *build(vector<int> &freq, vector<string> &codes) {
  auto cmp = [](const HT *a, const HT *b) -> bool {
    return a->weight > b->weight;
  };
  priority_queue<HT *, vector<HT *>, decltype(cmp)> q(cmp);
  int weight;
  char data;
  for (size_t i = 0; i < freq.size(); i++) {
    if (freq[i] == 0) continue;
    weight = freq[i];
    data = char(i);
    q.push(new HT{weight, data});
  }

  // char(7) is used to indicate the end of a file
  q.push(new HT{0, char(7)});

  HT *n1, *n2, *new_node;
  while (true) {
    n1 = q.top();
    q.pop();
    /* if n1 is the last element in the queue,
     * the building of the huffman tree is over
     */
    if (q.empty()) {
      encode(n1, codes);
      break;
    }
    n2 = q.top();
    q.pop();
    new_node = new HT{n1->weight + n2->weight, '\0', n1, n2};
    q.push(new_node);
  }
  return n1;
}

// save the encoded file
void saveToFile(string sourceFileName, string encodeFileName,
                vector<string> &codes) {
  fstream sourceFile(sourceFileName);
  fstream encodeFile(encodeFileName, ios::out | ios::binary);
  // save 8 bit every time
  char buffer{0}, ch;
  int pos{8};
  // the end of the file
  bool flag = false;
  while (true) {
    if (flag) break;
    if (sourceFile.eof()) {
      flag = true;
      // char(7) means the end of encoded file
      ch = char(7);
    } else
      ch = sourceFile.get();
    for (auto &i : codes[ch]) {
      if (i == '1')
        // set bit in pos to 1
        buffer |= 1 << (pos - 1);
      else
        // set bit in pos to 0
        buffer &= ~(1 << (pos - 1));
      if (--pos < 1) {
        // write 8 bits to file
        encodeFile.write(reinterpret_cast<char *>(&buffer), sizeof(buffer));
        pos = 8;
      }
    }
  }
  // make sure all bits are written to file
  if (pos != 8)
    encodeFile.write(reinterpret_cast<char *>(&buffer), sizeof(buffer));
  sourceFile.close();
  encodeFile.close();
}

// decode from an encoded file according to the give huffman tree
void decodeFromFile(string encodeFileName, string decodeFileName, HT *root) {
  fstream encodeFile(encodeFileName, ios::in | ios::binary);
  fstream decodeFile(decodeFileName, ios::out);
  // read 8 bits every time
  char buffer;
  HT *node{root};
  bool flag = false;
  while (!encodeFile.eof()) {
    if (flag) break;
    encodeFile.read(reinterpret_cast<char *>(&buffer), sizeof(buffer));
    for (size_t i = 8; i >= 1; i--) {
      if (buffer >> (i - 1) & 1)
        node = node->rchild;
      else
        node = node->lchild;
      // reach the end of encoded file
      if (node->data == char(7)) {
        flag = true;
        break;
      }
      // find the char to the code
      if (node->data != '\0') {
        cout << node->data;
        decodeFile << node->data;
        node = root;
      }
    }
    if (encodeFile.eof()) break;
  }
  encodeFile.close();
  decodeFile.close();
}

// save the frequence of every char to file
void saveCode(string codeFileName, vector<int> &freq) {
  fstream codeFile(codeFileName, ios::out);
  for (size_t i = 0; i < freq.size(); i++) {
    if (freq[i] == 0) continue;
    codeFile << i << ' ' << freq[i] << endl;
  }
  codeFile.close();
}

// load frequence of every char and build a tree
HT *loadCode(string codeFileName, vector<string> &codes) {
  fstream codeFile(codeFileName, ios::in);
  int ch, fre;
  vector<int> freq(128);
  while (!codeFile.eof()) {
    codeFile >> ch >> fre;
    freq[ch] = fre;
    if (codeFile.eof()) break;
  }
  codeFile.close();
  return build(freq, codes);
}

// count each char's frequence
void count(vector<int> &freq, string fileName) {
  fstream file(fileName);
  char ch;
  while (!file.eof()) {
    ch = file.get();
    if (file.eof()) break;
    freq[ch]++;
  }
  file.close();
}

int main() {
  vector<int> freq(128);
  vector<string> codes(128);
  const string SOURCEFILE = "source.txt";
  const string ENCODEFILE = "encode.dat";
  const string DECODEFILE = "decode.txt";
  const string CODEFILE = "code.txt";
  count(freq, SOURCEFILE);
  HT *root = build(freq, codes);
  show(root, freq);
  saveToFile(SOURCEFILE, ENCODEFILE, codes);
  saveCode(CODEFILE, freq);
  vector<string> codes2(128);
  HT *r = loadCode(CODEFILE, codes2);
  decodeFromFile(ENCODEFILE, DECODEFILE, r);
  destroy(root);
  destroy(r);
}
