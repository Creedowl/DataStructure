/*
 * @Date: 2019-11-11 21:24:37
 * @Author: creedowl
 * @Description: graph adt using cpp
 */
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using std::vector;

class Graph {
private:
  // node nums and edge num
  int nodes{0}, edges{0};
  // each node's value
  vector<int> vexs;
  // relation
  vector<vector<int>> graph;

public:
  Graph() = default;

  Graph(int nodes, int edges) : nodes(nodes), edges(edges) {
    this->vexs.resize(nodes);
    this->graph.resize(nodes);
    for (size_t i = 0; i < nodes; i++) this->graph[i].resize(nodes);
  }

  ~Graph() {}

  void create() {
    for (size_t i = 0; i < nodes; i++) std::cin >> vexs[i];
    int n1, n2, weight;
    for (size_t i = 0; i < edges; i++) {
      std::cin >> n1 >> n2 >> weight;
      this->graph[n1][n2] = weight;
      this->graph[n2][n1] = weight;
    }
  }

  void clear() {
    this->graph.clear();
    this->nodes = 0;
  }

  // return node's index
  int locateVex(int value) {
    for (size_t i = 0; i < this->nodes; i++) {
      if (this->vexs[i] == value) return i;
    }
    return -1;
  }

  // return node's value
  int getVex(int node) {
    if (node >= 0 and node < this->nodes) return this->vexs[node];
    return -1;
  }

  // set node's value
  void setVex(int node, int value) {
    if (node >= 0 and node < this->nodes) this->vexs[node] = value;
  }

  int firstAdjVex(int node) {
    if (node >= 0 and node < this->nodes) {
      for (size_t i = 0; i < this->nodes; i++) {
        if (this->graph[node][i] != 0) return i;
      }
    }
    return -1;
  }

  int nextAdjVex(int node, int pre) {
    if (node >= 0 and node < this->nodes) {
      for (size_t i = pre + 1; i < this->nodes; i++) {
        if (this->graph[node][i] != 0) return i;
      }
    }
    return -1;
  }

  void insertVex(int v, vector<std::pair<int, int>> relations) {
    this->nodes++;
    this->edges += relations.size();
    this->vexs.push_back(v);
    this->graph.resize(this->nodes);
    for (auto row : this->graph) row.resize(this->nodes);
    for (size_t i = 0; i < this->nodes; i++) this->graph[i].resize(this->nodes);
    for (auto const &pair : relations) {
      this->graph[this->nodes - 1][pair.first] = pair.second;
      this->graph[pair.first][this->nodes - 1] = pair.second;
    }
  }

  void deleteVex(int node) {
    int count{0};
    for (size_t i = 0; i < this->nodes; i++)
      if (this->graph[node][i] != 0) count++;
    this->edges -= count;
    this->nodes--;
    this->graph.erase(this->graph.begin() + node);
    for (auto &row : this->graph) {
      row.erase(row.begin() + node);
    }
  }

  void insertArc(int n1, int n2, int weight) {
    this->edges++;
    this->graph[n1][n2] = weight;
    this->graph[n2][n1] = weight;
  }

  void deleteArc(int n1, int n2) {
    this->edges--;
    this->graph[n1][n2] = 0;
    this->graph[n2][n1] = 0;
  }

  void DFS(int node, const std::function<bool(int)> &visit) {
    vector<bool> visited(this->nodes, false);
    std::stack<int> s;
    s.push(node);
    int cur{-1};
    while (!s.empty()) {
      cur = s.top();
      s.pop();
      if (visited[cur]) continue;
      visited[cur] = true;
      if (!visit(cur)) return;
      for (size_t i = 0; i < this->nodes; i++) {
        if (this->graph[cur][i] != 0) s.push(i);
      }
    }
  }

  void BFS(int node, const std::function<bool(int)> &visit) {
    vector<bool> visited(this->nodes, false);
    std::queue<int> q;
    q.push(node);
    int cur{-1};
    while (!q.empty()) {
      cur = q.front();
      q.pop();
      if (visited[cur]) continue;
      visited[cur] = true;
      if (!visit(cur)) return;
      for (size_t i = 0; i < this->nodes; i++) {
        if (this->graph[cur][i] != 0) q.push(i);
      }
    }
  }

  void show() {
    for (auto const &i : this->graph) {
      for (auto const &j : i) std::cout << j << " ";
      std::cout << std::endl;
    }
  }
};

int main() {
  Graph g{6, 6};
  g.create();
  g.show();
  // std::cout << g.getVex(3) << std::endl;
  // std::cout << g.locateVex(4) << std::endl;
  // std::cout << g.nextAdjVex(2, 2) << std::endl;
  // g.insertVex(4, {{0, 1}, {2, 3}});
  // g.deleteVex(2);
  // g.insertArc(0, 2, 9);
  auto visit = [](int node) -> bool {
    std::cout << node << " ";
    return true;
  };
  g.DFS(1, visit);
  // g.BFS(1, visit);
  std::cout << std::endl;
  // g.show();
  g.clear();
}
