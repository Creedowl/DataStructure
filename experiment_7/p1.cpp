/*
 * @Date: 2019-12-02 11:09:22
 * @Author: creedowl
 * @Description: BFS and DFS
 */
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

int nodes, edges;

void DFS(vector<vector<int>> &graph, int root,
         const function<bool(int)> &visit) {
  stack<int> s{{root}};
  vector<bool> visited(nodes, false);
  int cur{-1};
  while (!s.empty()) {
    cur = s.top();
    s.pop();
    if (visited[cur]) continue;
    visited[cur] = true;
    if (!visit(cur)) return;
    for (size_t i = 0; i < nodes; i++) {
      if (graph[cur][i] != 0) s.push(i);
    }
  }
}

void BFS(vector<vector<int>> &graph, int root,
         const function<bool(int)> &visit) {
  queue<int> s{{root}};
  vector<bool> visited(nodes, false);
  int cur{-1};
  while (!s.empty()) {
    cur = s.front();
    s.pop();
    if (visited[cur]) continue;
    visited[cur] = true;
    if (!visit(cur)) return;
    for (size_t i = 0; i < nodes; i++) {
      if (graph[cur][i] != 0) s.push(i);
    }
  }
}

int main() {
  cin >> nodes >> edges;
  vector<vector<int>> graph(nodes, vector<int>(nodes));
  int n1, n2, value;
  for (size_t i = 0; i < edges; i++) {
    cin >> n1 >> n2 >> value;
    graph[n1][n2] = value;
    graph[n2][n1] = value;
  }
  auto visit = [](int n) -> bool {
    cout << n << " ";
    return true;
  };
  DFS(graph, 0, visit);
  cout << endl;
  BFS(graph, 0, visit);
  cout << endl;
}
