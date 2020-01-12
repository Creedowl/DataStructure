/*
 * @Date: 2019-12-30 19:57:20
 * @Author: creedowl
 * @Description: Minimum Spanning Tree, include Kruskal and Prim algorithm
 */
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

typedef struct
{
  int from{0}, to{0}, weight{0};
} Arc;

vector<Arc> arcs;
vector<string> nodes;

// Disjoint-set
vector<int> uni;
int n, m;

int find(int x) { return uni[x] == x ? x : uni[x] = find(uni[x]); }

void unite(int x, int y) { uni[find(x)] = find(uni[y]); }

void kruskal()
{
  vector<pair<int, int>> route;
  for (size_t i = 0; i <= n; i++)
    uni[i] = i;
  sort(arcs.begin(), arcs.end(),
       [](Arc a, Arc b) { return a.weight < b.weight; });
  int sum{0};
  for (size_t i = 0; i < m; i++)
  {
    if (find(arcs[i].from) != find(arcs[i].to))
    {
      unite(arcs[i].from, arcs[i].to);
      sum += arcs[i].weight;
      route.push_back(make_pair(arcs[i].from, arcs[i].to));
    }
  }
  cout << "routes are:" << endl;
  for (auto &i : route)
  {
    cout << nodes[i.first] << "->" << nodes[i.second] << endl;
  }
  cout << "total weight: " << sum << endl;
}

void prim()
{
  int sum{0};
  vector<pair<int, int>> route;
  vector<bool> visited(n);
  auto cmp = [](Arc &a, Arc &b) { return a.weight > b.weight; };
  priority_queue<Arc, vector<Arc>, decltype(cmp)> q{cmp};
  visited[0] = true;
  for (auto &i : arcs)
  {
    if (i.from == 0 or i.to == 0)
      q.push(i);
  }
  int from{0}, to{0}, weight{0};
  while (!q.empty())
  {
    from = q.top().from, to = q.top().to, weight = q.top().weight;
    q.pop();
    if (!visited[to] or !visited[from])
    {
      visited[from] = true;
      visited[to] = true;
      sum += weight;
      route.push_back(make_pair(from, to));
      for (auto &i : arcs)
        if ((i.from == to and !visited[i.to]) or
            (i.to == to and !visited[i.from]))
          q.push(i);
    }
  }
  cout << "routes are:" << endl;
  for (auto &i : route)
  {
    cout << nodes[i.first] << "->" << nodes[i.second] << endl;
  }
  cout << "total weight: " << sum << endl;
}

int main()
{
  auto fp = freopen("data.in", "r", stdin);
  cin >> n >> m;
  arcs.resize(m);
  uni.resize(n + 1);
  nodes.resize(n);
  for (size_t i = 0; i < n; i++)
    cin >> nodes[i];
  for (size_t i = 0; i < m; i++)
  {
    cin >> arcs[i].from >> arcs[i].to >> arcs[i].weight;
  }
  kruskal();
  prim();
  fclose(fp);
}
