/*
 * @Date: 2019-12-29 00:12:18
 * @Author: creedowl
 * @Description: csp (2017-9-2)
 */
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct cmp {
  bool operator()(pair<bool, int> p1, pair<bool, int> p2) {
    if (p2.first) return false;
    if (!p1.first and !p2.first) return p1.second > p2.second;
    return true;
  };
};

priority_queue<pair<bool, int>, vector<pair<bool, int>>, cmp> ti[10101];

int n, k;

int keys[1001];

int main() {
  auto fp = freopen("p3.in", "r", stdin);

  cin >> n >> k;
  int w, s, c;
  int total_time = 0;

  for (size_t i = 0; i < k; i++) {
    cin >> w >> s >> c;
    ti[s].push(make_pair(true, w));
    ti[s + c].push(make_pair(false, w));
    total_time = max(total_time, s + c);
  }

  for (size_t i = 1; i <= n; i++) keys[i] = i;

  for (size_t i = 1; i <= total_time; i++) {
    if (ti[i].size() == 0) continue;
    while (ti[i].size() != 0) {
      auto pi = ti[i].top();
      ti[i].pop();
      if (pi.first) {
        for (size_t j = 1; j <= n; j++) {
          if (keys[j] == pi.second) {
            keys[j] = -1;
            break;
          }
        }
      } else {
        for (size_t j = 1; j <= n; j++) {
          if (keys[j] == -1) {
            keys[j] = pi.second;
            break;
          }
        }
      }
    }
  }

  for (size_t i = 1; i <= n; i++) cout << keys[i] << " ";
  cout << endl;

  fclose(fp);
}
