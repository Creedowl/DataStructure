/*
 * @Date: 2019-12-11 11:35:43
 * @Author: creedowl
 * @Description: e7p4 (csp)
 */
#include <algorithm>
#include <iostream>

using namespace std;

struct Arc {
  int from{0}, to{0}, weight{0};
} arcs[100001];

// Disjoint-set
int uni[1001];
int n, m;

int find(int x) { return uni[x] == x ? x : uni[x] = find(uni[x]); }

void unite(int x, int y) { uni[find(x)] = find(uni[y]); }

int main() {
  cin >> n >> m;
  for (size_t i = 0; i <= n; i++) uni[i] = i;
  for (size_t i = 0; i < m; i++) {
    cin >> arcs[i].from >> arcs[i].to >> arcs[i].weight;
  }
  sort(arcs, arcs + m, [](Arc a, Arc b) { return a.weight < b.weight; });
  int sum{0};
  // Kruskal
  for (size_t i = 0; i < m; i++) {
    if (find(arcs[i].from) != find(arcs[i].to)) {
      unite(arcs[i].from, arcs[i].to);
      sum += arcs[i].weight;
    }
  }
  cout << sum << endl;
}
