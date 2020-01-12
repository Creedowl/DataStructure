/*
 * @Date: 2020-01-07 11:29:33
 * @Author: creedowl
 * @Description: csp (201709-3)
 */
#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Node {
public:
  map<string, string> str;
  map<string, Node *> obj;
};

void build(string &json, int &i, Node *root) {
  bool isKey{true};
  string key{""}, value{""};
  for (; i < json.size() - 1; i++) {
    if (json[i] == '}') return;
    if (json[i] == ' ' or json[i] == ':' or json[i] == ',') continue;
    if (json[i] == '"' and isKey) {
      isKey = false;
      i++;
      while (json[i] != '"') {
        if (json[i] == '\\' and json[i - 1] != '\\') {
          i++;
          continue;
        }
        key += json[i];
        i++;
      }
    } else if (json[i] == '"' and !isKey) {
      isKey = true;
      i++;
      while (json[i] != '"' or json[i - 1] == '\\') {
        if (json[i] == '\\' and json[i - 1] != '\\') {
          i++;
          continue;
        }
        value += json[i];
        i++;
      }
      root->str.emplace(key, value);
      key.clear();
      value.clear();
    } else if (json[i] == '{') {
      Node *obj = new Node{};
      build(json, ++i, obj);
      root->obj.emplace(key, obj);
      isKey = true;
      key.clear();
    }
  }
}

int find(Node *root, string s) {
  if (s.find('.') == string::npos) {
    if (root->str.count(s) != 0) {
      cout << "STRING"
           << " " << root->str[s] << endl;
      return 0;
    } else if (root->obj.count(s) != 0) {
      cout << "OBJECT" << endl;
      return 1;
    } else {
      cout << "NOTEXIST" << endl;
      return 2;
    }
  } else {
    int begin{0}, pos = s.find('.');
    string sub = s.substr(0, pos);
    if (root->obj.count(sub) == 0) {
      cout << "NOTEXIST" << endl;
      return 2;
    } else {
      find(root->obj[sub], s.substr(pos + 1, s.size() - pos));
      return 1;
    }
  }
}

int main() {
  int n, m;
  Node root{};
  cin >> n >> m >> ws;
  string line, json;
  for (size_t i = 0; i < n; i++) {
    getline(cin, line);
    json += line;
  }
  // Node *cur{&root};
  int pos{1};
  build(json, pos, &root);
  string s;
  for (size_t i = 0; i < m; i++) {
    cin >> s;
    find(&root, s);
  }
}
