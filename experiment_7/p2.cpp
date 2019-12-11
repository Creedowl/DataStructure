/*
 * @Date: 2019-12-02 17:03:38
 * @Author: creedowl
 * @Description: Dijkstra
 */
#include <iostream>
#include <limits>
#include <stack>
#include <vector>

using namespace std;

typedef struct {
  bool finished{false};
  int from{0}, weight{0};
} Node;

int MAX_INT = numeric_limits<int>::max();

int nodes, edges, head;

void Dijkstra(vector<vector<int>> &graph) {
  vector<Node> dis(nodes);
  for (size_t i = 0; i < nodes; i++) {
    dis[i].from = head;
    dis[i].finished = false;
    dis[i].weight = graph[head][i];
  }
  dis[head].finished = true;
  int min_weight, cur;
  for (size_t i = 0; i < nodes - 1; i++) {
    min_weight = MAX_INT;
    cur = -1;
    for (size_t j = 0; j < nodes; j++) {
      if (!dis[j].finished and dis[j].weight < min_weight) {
        min_weight = dis[j].weight;
        cur = j;
      }
    }
    if (cur == -1) break;
    dis[cur].finished = true;
    for (size_t j = 0; j < nodes; j++) {
      if (graph[cur][j] == MAX_INT) continue;
      if (dis[cur].weight + graph[cur][j] < dis[j].weight) {
        dis[j].weight = dis[cur].weight + graph[cur][j];
        dis[j].from = cur;
      }
    }
  }
  stack<int> chain;
  for (size_t i = 0; i < nodes; i++) {
    if (i == head) continue;
    if (dis[i].weight == MAX_INT) {
      cout << "no route from " << head << " to " << i << endl;
      continue;
    }
    cout << head << " to " << i << ": " << head << " ";
    int temp = dis[i].from;
    chain.push(i);
    while (temp != head) {
      chain.push(temp);
      temp = dis[temp].from;
    }
    while (!chain.empty()) {
      cout << chain.top() << " ";
      chain.pop();
    }
    cout << "total weight: " << dis[i].weight << endl;
  }
}

int main() {
  cin >> nodes >> edges >> head;
  vector<vector<int>> graph(nodes, vector<int>(nodes, MAX_INT));
  int n1, n2, value;
  for (size_t i = 0; i < edges; i++) {
    cin >> n1 >> n2 >> value;
    graph[n1][n2] = value;
  }
  Dijkstra(graph);
}
