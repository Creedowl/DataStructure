/*
 * @Date: 2020-01-03 20:19:56
 * @Author: creedowl
 * @Description: 朋友圈
 */
#include <iostream>

using namespace std;

int uni[30001], total[30001];
int n, m;

int find(int x) { return uni[x] == x ? x : uni[x] = find(uni[x]); }

void unite(int x, int y) { uni[find(x)] = find(uni[y]); }

int main() {
  cin >> n >> m;
  for (size_t i = 0; i <= n; i++) uni[i] = i;
  int x, y, p;
  for (size_t i = 0; i < m; i++) {
    cin >> x >> p;
    for (size_t j = 1; j < x; j++) {
      cin >> y;
      unite(y, p);
    }
  }
  int ma{-1};
  for (size_t i = 1; i <= n; i++) total[find(i)]++;
  for (size_t i = 1; i <= n; i++) ma = max(ma, total[i]);
  cout << ma << endl;
}
