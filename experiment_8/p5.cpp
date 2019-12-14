/*
 * @Date: 2019-12-13 19:25:03
 * @Author: creedowl
 * @Description: e8p5 (csp)
 */
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<pair<int, int>> num(1001);
int n;

int main() {
  cin >> n;
  int temp;
  for (size_t i = 0; i < n; i++) {
    cin >> temp;
    num[temp].first = temp;
    num[temp].second++;
  }
  sort(num.begin(), num.end(), [](pair<int, int> a, pair<int, int> b) {
    if (a.second == b.second) return a.first < b.first;
    return a.second > b.second;
  });
  for (size_t i = 0; i < n; i++)
    if (num[i].second != 0)
      cout << num[i].first << " " << num[i].second << endl;
}
